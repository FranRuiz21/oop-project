#include "minesweeper.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Minesweeper::Minesweeper() {
    reset();
}

void Minesweeper::reset() {
    mines.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    revealed.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    remaining = BOARD_SIZE * BOARD_SIZE - MINES;
    std::srand(std::time(nullptr));
    placeMines();
}

void Minesweeper::placeMines() {
    int placed = 0;
    while (placed < MINES) {
        int x = std::rand() % BOARD_SIZE;
        int y = std::rand() % BOARD_SIZE;
        if (!mines[x][y]) {
            mines[x][y] = true;
            placed++;
        }
    }
}

int Minesweeper::countAdjacentMines(int x, int y) const {
    int count = 0;
    for (int i = std::max(0, x - 1); i <= std::min(BOARD_SIZE - 1, x + 1); i++) {
        for (int j = std::max(0, y - 1); j <= std::min(BOARD_SIZE - 1, y + 1); j++) {
            if (mines[i][j]) count++;
        }
    }
    return count;
}

bool Minesweeper::reveal(int x, int y) {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || revealed[x][y])
        return false;

    revealed[x][y] = true;

    if (mines[x][y]) return true; // Hit mine

    remaining--;

    if (countAdjacentMines(x, y) == 0) {
        // Reveal neighbors recursively
        for (int i = std::max(0, x - 1); i <= std::min(BOARD_SIZE - 1, x + 1); i++) {
            for (int j = std::max(0, y - 1); j <= std::min(BOARD_SIZE - 1, y + 1); j++) {
                if (!revealed[i][j]) {
                    reveal(i, j);
                }
            }
        }
    }
    return false;
}

bool Minesweeper::isWon() const {
    return remaining == 0;
}

bool Minesweeper::isRevealed(int x, int y) const {
    return revealed[x][y];
}

bool Minesweeper::hasMine(int x, int y) const {
    return mines[x][y];
}

int Minesweeper::adjacentMines(int x, int y) const {
    return countAdjacentMines(x, y);
}
