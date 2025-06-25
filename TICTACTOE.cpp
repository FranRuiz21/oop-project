#include "TicTacToe.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <iostream>

TicTacToe::TicTacToe()
    : board(3, std::vector<char>(3, ' '))
    , currentPlayer('X')
    , moves(0)
{
    // Inicializar música de fondo
    backgroundMusic = new QMediaPlayer();
    backgroundOutput = new QAudioOutput();

    backgroundMusic->setAudioOutput(backgroundOutput);
    backgroundMusic->setSource(QUrl::fromLocalFile("sounds/Door.wav"));
    backgroundMusic->setLoops(QMediaPlayer::Infinite);
    backgroundOutput->setVolume(1.0);
    backgroundMusic->play();
}

TicTacToe::~TicTacToe()
{
    delete backgroundMusic;
    delete backgroundOutput;
}

void TicTacToe::printBoard() const
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j] << (j < 2 ? " | " : "");
        }
        std::cout << "\n" << (i < 2 ? "---------\n" : "");
    }
}

bool TicTacToe::makeMove(int row, int col)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        moves++;
        return true;
    }
    return false;
}

bool TicTacToe::checkWin(char player) const
{
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player)
           || (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool TicTacToe::isDraw() const
{
    return moves >= 9;
}

char TicTacToe::getCurrentPlayer() const
{
    return currentPlayer;
}

void TicTacToe::switchPlayer()
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

