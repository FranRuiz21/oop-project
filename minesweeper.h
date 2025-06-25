#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <QSoundEffect>

const int BOARD_SIZE = 10;
const int MINES = 15;

class Minesweeper {
private:
    std::vector<std::vector<bool>> mines;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> flagged;
    int remaining;
    bool firstClick = true;

    QSoundEffect *crashSound;

    void placeMines(int safeX, int safeY);
    int countAdjacentMines(int x, int y) const;

public:
    Minesweeper();
    ~Minesweeper();  // Destructor

    void reset();
    bool reveal(int x, int y);
    void toggleFlag(int x, int y);
    bool isFlagged(int x, int y) const;
    bool isWon() const;
    bool isRevealed(int x, int y) const;
    bool hasMine(int x, int y) const;
    int adjacentMines(int x, int y) const;
};

#endif // MINESWEEPER_H

