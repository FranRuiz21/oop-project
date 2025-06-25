#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <iostream>
#include <vector>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
class TicTacToe
{
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    int moves;

public:
    TicTacToe();
     ~TicTacToe();
    QMediaPlayer *backgroundMusic;
    QAudioOutput *backgroundOutput;
    void printBoard() const;
    bool makeMove(int row, int col);
    bool checkWin(char player) const;
    bool isDraw() const;
    char getCurrentPlayer() const;
    void switchPlayer();
};

#endif // TICTACTOE_H
