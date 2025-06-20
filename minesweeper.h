#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>

const int BOARD_SIZE = 10;
const int MINES = 15;

class Minesweeper {
private:
    std::vector<std::vector<bool>> mines;
    std::vector<std::vector<bool>> revealed;
    int remaining; // non-mine unrevealed cells
    std::vector<std::vector<bool>> flagged;
    void placeMines(int safeX, int safeY); // nuevo: evita colocar mina en el primer click
    bool firstClick = true;                // bandera para saber si es el primer click

    void placeMines();
    int countAdjacentMines(int x, int y) const;

public:
    Minesweeper();
    void toggleFlag(int x, int y);
    bool isFlagged(int x, int y) const;
    bool reveal(int x, int y);          // Reveal cell, returns true if mine hit
    bool isWon() const;                 // True if all safe cells revealed
    bool isRevealed(int x, int y) const;
    bool hasMine(int x, int y) const;
    int adjacentMines(int x, int y) const;

    void reset();                      // Reset the board for a new game
};

#endif // MINESWEEPER_H
