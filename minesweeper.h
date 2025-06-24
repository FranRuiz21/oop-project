#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>


const int BOARD_SIZE = 10;
const int MINES = 15;

class Minesweeper {
private:
    std::vector<std::vector<bool>> mines;
    std::vector<std::vector<bool>> revealed;
    int remaining;
    std::vector<std::vector<bool>> flagged;
    void placeMines(int safeX, int safeY);
    bool firstClick = true;

    void placeMines();
    int countAdjacentMines(int x, int y) const;

public:
    Minesweeper();
    void toggleFlag(int x, int y);
    bool isFlagged(int x, int y) const;
    bool reveal(int x, int y);
    bool isWon() const;
    bool isRevealed(int x, int y) const;
    bool hasMine(int x, int y) const;
    int adjacentMines(int x, int y) const;

    void reset();
};

#endif // MINESWEEPER_H
