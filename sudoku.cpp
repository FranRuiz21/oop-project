#include "sudoku.h"


Sudoku::Sudoku() {
    srand(time(0));
    board = vector<vector<int>>(SIZE, vector<int>(SIZE, EMPTY));
    fixed = vector<vector<bool>>(SIZE, vector<bool>(SIZE, false));
}

void Sudoku::generatePuzzle(int difficulty) {
    board = vector<vector<int>>(SIZE, vector<int>(SIZE, EMPTY));
    fixed = vector<vector<bool>>(SIZE, vector<bool>(SIZE, false));
    generateSolution();
    removeNumbers(difficulty);
}

bool Sudoku::isValid(int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = row - row % SUBGRID;
    int startCol = col - col % SUBGRID;

    for (int i = 0; i < SUBGRID; i++) {
        for (int j = 0; j < SUBGRID; j++) {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }
    return true;
}

bool Sudoku::solveBoard() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == EMPTY) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isValid(row, col, num)) {
                        board[row][col] = num;
                        if (solveBoard()) return true;
                        board[row][col] = EMPTY;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::generateSolution() {
    fillDiagonalSubgrids();
    solveBoard();
    solution = board;
}

void Sudoku::fillDiagonalSubgrids() {
    for (int box = 0; box < SIZE; box += SUBGRID) {
        fillSubgrid(box, box);
    }
}

void Sudoku::fillSubgrid(int row, int col) {
    int nums[SIZE];
    for (int i = 0; i < SIZE; i++) nums[i] = i + 1;

    for (int i = SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(nums[i], nums[j]);
    }

    int index = 0;
    for (int i = 0; i < SUBGRID; i++) {
        for (int j = 0; j < SUBGRID; j++) {
            board[row + i][col + j] = nums[index++];
        }
    }
}

void Sudoku::removeNumbers(int difficulty) {
    int cellsToRemove = (difficulty == 1) ? 40 : (difficulty == 2) ? 50 : 60;
    vector<pair<int, int>> positions;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            positions.push_back({i, j});
        }
    }

    for (int i = positions.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(positions[i], positions[j]);
    }

    for (int i = 0; i < cellsToRemove; i++) {
        int row = positions[i].first;
        int col = positions[i].second;
        board[row][col] = EMPTY;
        fixed[row][col] = false;
    }

    // Mark fixed cells
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != EMPTY) {
                fixed[i][j] = true;
            }
        }
    }
}

bool Sudoku::isFixed(int row, int col) const {
    return fixed[row][col];
}

bool Sudoku::makeMove(int row, int col, int num) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    if (fixed[row][col]) return false;
    if (num < 1 || num > 9) return false;
    if (!isValid(row, col, num)) return false;
    board[row][col] = num;
    return true;
}

bool Sudoku::isComplete() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == EMPTY) return false;
            int val = board[row][col];
            board[row][col] = EMPTY;
            if (!isValid(row, col, val)) {
                board[row][col] = val;
                return false;
            }
            board[row][col] = val;
        }
    }
    return true;
}

void Sudoku::resetBoard() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (!fixed[row][col]) board[row][col] = EMPTY;
        }
    }
}

int Sudoku::getCell(int row, int col) const {
    return board[row][col];
}

int Sudoku::getSolution(int row, int col) const {
    return solution[row][col];
}
