#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 9;
const int SUBGRID = 3;
const int EMPTY = 0;

class Sudoku {
private:
    vector<vector<int> > board;
    vector<vector<int> > solution;
    vector<vector<bool> > fixed;

    bool isValid(int row, int col, int num) {
        for (int x = 0; x < SIZE; x++) {
            if (board[row][x] == num) return false;
        }
        for (int x = 0; x < SIZE; x++) {
            if (board[x][col] == num) return false;
        }
        int startRow = row - row % SUBGRID;
        int startCol = col - col % SUBGRID;
        for (int i = 0; i < SUBGRID; i++) {
            for (int j = 0; j < SUBGRID; j++) {
                if (board[i + startRow][j + startCol] == num) return false;
            }
        }
        return true;
    }

    bool solveBoard() {
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

    void generateSolution() {
        fillDiagonalSubgrids();
        solveBoard();
        solution = board;
    }

    void fillDiagonalSubgrids() {
        for (int box = 0; box < SIZE; box += SUBGRID) {
            fillSubgrid(box, box);
        }
    }

    void fillSubgrid(int row, int col) {
        int nums[SIZE];
        for (int i = 0; i < SIZE; i++) nums[i] = i + 1;
        for (int i = SIZE - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        int index = 0;
        for (int i = 0; i < SUBGRID; i++) {
            for (int j = 0; j < SUBGRID; j++) {
                board[row + i][col + j] = nums[index++];
            }
        }
    }

    void removeNumbers(int difficulty) {
        int cellsToRemove = (difficulty == 1) ? 40 : (difficulty == 2) ? 50 : 60;
        vector<pair<int, int> > positions;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                positions.push_back(make_pair(i, j));
            }
        }
        for (int i = positions.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            pair<int, int> temp = positions[i];
            positions[i] = positions[j];
            positions[j] = temp;
        }
        for (int i = 0; i < cellsToRemove; i++) {
            int row = positions[i].first;
            int col = positions[i].second;
            board[row][col] = EMPTY;
            fixed[row][col] = false;
        }
    }

public:
    Sudoku() {
        board = vector<vector<int> >(SIZE, vector<int>(SIZE, EMPTY));
        fixed = vector<vector<bool> >(SIZE, vector<bool>(SIZE, false));
    }

    void generatePuzzle(int difficulty) {
        board = vector<vector<int> >(SIZE, vector<int>(SIZE, EMPTY));
        fixed = vector<vector<bool> >(SIZE, vector<bool>(SIZE, false));
        generateSolution();
        removeNumbers(difficulty);
    }

    void printBoard() {
        cout << "   ";
        for (int col = 0; col < SIZE; col++) {
            cout << col + 1 << " ";
            if ((col + 1) % SUBGRID == 0 && col != SIZE - 1) cout << "| ";
        }
        cout << "\n  -------------------------\n";
        for (int row = 0; row < SIZE; row++) {
            cout << row + 1 << " |";
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col] == EMPTY) {
                    cout << "  ";
                } else {
                    cout << board[row][col] << " ";
                }
                if ((col + 1) % SUBGRID == 0 && col != SIZE - 1) cout << "| ";
            }
            cout << "\n";
            if ((row + 1) % SUBGRID == 0 && row != SIZE - 1) cout << "  -------------------------\n";
        }
    }

    bool isFixed(int row, int col) {
        return fixed[row][col];
    }

    bool makeMove(int row, int col, int num) {
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cout << "Invalid position. Please try again.\n";
            return false;
        }
        if (fixed[row][col]) {
            cout << "This cell is fixed. You can't change it.\n";
            return false;
        }
        if (num < 1 || num > 9) {
            cout << "Invalid number. Please enter a number between 1 and 9.\n";
            return false;
        }
        if (!isValid(row, col, num)) {
            cout << "Invalid move. This number conflicts with existing numbers.\n";
            return false;
        }
        board[row][col] = num;
        return true;
    }

    bool isComplete() {
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

    void showSolution() {
        cout << "\nSolution:\n";
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                cout << solution[row][col] << " ";
                if ((col + 1) % SUBGRID == 0 && col != SIZE - 1) cout << "| ";
            }
            cout << "\n";
            if ((row + 1) % SUBGRID == 0 && row != SIZE - 1) cout << "------+-------+------\n";
        }
    }

    void resetBoard() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (!fixed[row][col]) board[row][col] = EMPTY;
            }
        }
    }
};

void displayMenu() {
    cout << "\nSudoku Game Menu:\n";
    cout << "1. New Game (Easy)\n";
    cout << "2. New Game (Medium)\n";
    cout << "3. New Game (Hard)\n";
    cout << "4. Make a Move\n";
    cout << "5. Show Solution\n";
    cout << "6. Reset Board\n";
    cout << "7. Check Completion\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    srand(time(0));
    Sudoku game;
    int choice;
    bool gameInProgress = false;

    cout << "Welcome to Sudoku!\n";

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
        case 2:
        case 3:
            game.generatePuzzle(choice);
            game.printBoard();
            gameInProgress = true;
            break;
        case 4:
            if (!gameInProgress) {
                cout << "Please start a new game first.\n";
                break;
            }
            int row, col, num;
            cout << "Enter row (1-9), column (1-9), and number (1-9): ";
            cin >> row >> col >> num;
            if (game.makeMove(row - 1, col - 1, num)) game.printBoard();
            break;
        case 5:
            if (!gameInProgress) {
                cout << "Please start a new game first.\n";
                break;
            }
            game.showSolution();
            break;
        case 6:
            if (!gameInProgress) {
                cout << "Please start a new game first.\n";
                break;
            }
            game.resetBoard();
            cout << "Board has been reset.\n";
            game.printBoard();
            break;
        case 7:
            if (!gameInProgress) {
                cout << "Please start a new game first.\n";
                break;
            }
            if (game.isComplete()) {
                cout << "Congratulations! You've solved the Sudoku!\n";
            } else {
                cout << "The board is not complete yet. Keep trying!\n";
            }
            break;
        case 8:
            cout << "Thanks for playing Sudoku!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
