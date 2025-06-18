#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    int moves;

public:
    TicTacToe();

    void printBoard() const;
    bool makeMove(int row, int col);
    bool checkWin(char player) const;
    bool isDraw() const;
    char getCurrentPlayer() const;
    void switchPlayer();

};

#endif // TICTACTOE_H
