#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <limits>  // Added for input validation

using namespace std;

// Color definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

const int SIZE = 9;
const int SUBGRID = 3;
const int EMPTY = 0;

class Sudoku {
private:
    vector<vector<int> > board;
    vector<vector<int> > solution;
    vector<vector<bool> > fixed;

    bool isValid(int row, int col, int num) {
        // Check row
        for (int x = 0; x < SIZE; x++) {
            if (board[row][x] == num) return false;
        }

        // Check column
        for (int x = 0; x < SIZE; x++) {
            if (board[x][col] == num) return false;
        }

        // Check subgrid
        int startRow = row - row % SUBGRID;
        int startCol = col - col % SUBGRID;
        for (int i = 0; i < SUBGRID; i++) {
            for (int j = 0; j < SUBGRID; j++) {
                if (board[i + startRow][j + startCol] == num) {
                    return false;
                }
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
                            if (solveBoard()) {
                                return true;
                            }
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
        // Fill diagonal subgrids first (they are independent)
        fillDiagonalSubgrids();
        
        // Solve the rest of the board
        if (!solveBoard()) {
            cerr << RED << "Failed to generate a valid Sudoku solution. Retrying...\n" << RESET;
            board = vector<vector<int> >(SIZE, vector<int>(SIZE, EMPTY));  // Reset and retry
            generateSolution();
        }
        
        // Save the solution
        solution = board;
    }

    void fillDiagonalSubgrids() {
        for (int box = 0; box < SIZE; box += SUBGRID) {
            fillSubgrid(box, box);
        }
    }

    void fillSubgrid(int row, int col) {
        int temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> nums(temp, temp + sizeof(temp)/sizeof(temp[0]));
        random_device rd;
        mt19937 g(rd());
        shuffle(nums.begin(), nums.end(), g);

        int index = 0;
        for (int i = 0; i < SUBGRID; i++) {
            for (int j = 0; j < SUBGRID; j++) {
                board[row + i][col + j] = nums[index++];
                fixed[row + i][col + j] = true;  // Mark as fixed initially
            }
        }
    }

    void removeNumbers(int difficulty) {
        int cellsToRemove;
        switch (difficulty) {
            case 1: cellsToRemove = 40; break; // Easy
            case 2: cellsToRemove = 50; break; // Medium
            case 3: cellsToRemove = 60; break; // Hard
            default: cellsToRemove = 50; break; // Default medium
        }

        // Mark all cells as fixed first
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fixed[i][j] = true;
            }
        }

        // Randomly choose cells to remove (mark as non-fixed)
        vector<pair<int, int> > positions;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                positions.emplace_back(i, j);
            }
        }

        random_device rd;
        mt19937 g(rd());
        shuffle(positions.begin(), positions.end(), g);

        for (int i = 0; i < cellsToRemove; i++) {
            int row = positions[i].first;
            int col = positions[i].second;
            board[row][col] = EMPTY;
            fixed[row][col] = false;  // These cells are editable
        }
    }

public:
    Sudoku() {
        board = vector<vector<int> >(SIZE, vector<int>(SIZE, EMPTY));
        fixed = vector<vector<bool> >(SIZE, vector<bool>(SIZE, false));
    }

    void generatePuzzle(int difficulty) {
        // Reset board
        board = vector<vector<int> >(SIZE, vector<int>(SIZE, EMPTY));
        fixed = vector<vector<bool> >(SIZE, vector<bool>(SIZE, false));
        
        generateSolution();
        removeNumbers(difficulty);
    }

    void printBoard() {
        cout << CYAN << "   ";
        for (int col = 0; col < SIZE; col++) {
            cout << col + 1 << " ";
            if ((col + 1) % SUBGRID == 0 && col != SIZE - 1) {
                cout << "| ";
            }
        }
        cout << "\n  " << YELLOW << "-------------------------" << RESET << "\n";

        for (int row = 0; row < SIZE; row++) {
            cout << CYAN << row + 1 << " " << YELLOW << "|" << RESET;
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col] == EMPTY) {
                    cout << "  ";
                } else {
                    if (fixed[row][col]) {
                        cout << BOLD << BLUE << board[row][col] << RESET << " ";
                    } else {
                        cout << GREEN << board[row][col] << RESET << " ";
                    }
                }

                if ((col + 1) % SUBGRID == 0 && col != SIZE - 1) {
                    cout << YELLOW << "| " << RESET;
                }
            }
            cout << "\n";

            if ((row + 1) % SUBGRID == 0 && row != SIZE - 1) {
                cout << YELLOW << "  -------------------------" << RESET << "\n";
            }
        }
    }

    bool isFixed(int row, int col) {
        return fixed[row][col];
    }

    bool makeMove(int row, int col, int num) {
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cout << RED << "Invalid position. Please try again.\n" << RESET;
            return false;
        }

        if (fixed[row][col]) {
            cout << RED << "This cell is fixed. You can't change it.\n" << RESET;
            return false;
        }

        if (num < 1 || num > 9) {
            cout << RED << "Invalid number. Please enter a number between 1 and 9.\n" << RESET;
            return false;
        }

        if (!isValid(row, col, num)) {
            cout << RED << "Invalid move. This number conflicts with existing numbers.\n" << RESET;
            return false;
        }

        board[row][col] = num;
        return true;
    }

    bool isComplete() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col] == EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }

    void showSolution() {
        cout << MAGENTA << "\nSolution:\n" << RESET;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                cout << solution[row][col] << " ";
                if ((col + 1) % SUBGRID == 0 && col != SIZE - 1) {
                    cout << YELLOW << "| " << RESET;
                }
            }
            cout << "\n";

            if ((row + 1) % SUBGRID == 0 && row != SIZE - 1) {
                cout << YELLOW << "------+-------+------" << RESET << "\n";
            }
        }
    }

    void resetBoard() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (!fixed[row][col]) {
                    board[row][col] = EMPTY;
                }
            }
        }
    }
};

void displayMenu() {
    cout << MAGENTA << "\nSudoku Game Menu:\n" << RESET;
    cout << CYAN << "1. " << RESET << "New Game (" << GREEN << "Easy" << RESET << ")\n";
    cout << CYAN << "2. " << RESET << "New Game (" << YELLOW << "Medium" << RESET << ")\n";
    cout << CYAN << "3. " << RESET << "New Game (" << RED << "Hard" << RESET << ")\n";
    cout << CYAN << "4. " << RESET << "Make a Move\n";
    cout << CYAN << "5. " << RESET << "Show Solution\n";
    cout << CYAN << "6. " << RESET << "Reset Board\n";
    cout << CYAN << "7. " << RESET << "Check Completion\n";
    cout << CYAN << "8. " << RESET << "Exit\n";
    cout << BOLD << "Enter your choice: " << RESET;
}

int main() {
    Sudoku game;
    int choice;
    bool gameInProgress = false;

    cout << BOLD << BLUE << "Welcome to " << MAGENTA << "S" << GREEN << "U" << YELLOW << "D" << RED << "O" << CYAN << "K" << MAGENTA << "U" << BLUE << "!" << RESET << "\n";

    while (true) {
        displayMenu();
        if (!(cin >> choice)) {  // Input validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input. Please enter a number.\n" << RESET;
            continue;
        }

        switch (choice) {
            case 1:
            case 2:
            case 3: {
                string difficulty;
                switch (choice) {
                    case 1: difficulty = GREEN + string("Easy") + RESET; break;
                    case 2: difficulty = YELLOW + string("Medium") + RESET; break;
                    case 3: difficulty = RED + string("Hard") + RESET; break;
                }
                cout << "\nStarting new " << difficulty << " game...\n";
                game.generatePuzzle(choice);
                game.printBoard();
                gameInProgress = true;
                break;
            }
            case 4: {
                if (!gameInProgress) {
                    cout << RED << "Please start a new game first.\n" << RESET;
                    break;
                }
                int row, col, num;
                cout << CYAN << "Enter row (1-9), column (1-9), and number (1-9): " << RESET;
                if (!(cin >> row >> col >> num)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << RED << "Invalid input. Please try again.\n" << RESET;
                    break;
                }
                if (game.makeMove(row - 1, col - 1, num)) {
                    game.printBoard();
                }
                break;
            }
            case 5: {
                if (!gameInProgress) {
                    cout << RED << "Please start a new game first.\n" << RESET;
                    break;
                }
                game.showSolution();
                break;
            }
            case 6: {
                if (!gameInProgress) {
                    cout << RED << "Please start a new game first.\n" << RESET;
                    break;
                }
                game.resetBoard();
                cout << GREEN << "Board has been reset.\n" << RESET;
                game.printBoard();
                break;
            }
            case 7: {
                if (!gameInProgress) {
                    cout << RED << "Please start a new game first.\n" << RESET;
                    break;
                }
                if (game.isComplete()) {
                    cout << BOLD << GREEN << "\nCongratulations! You've solved the Sudoku!\n" << RESET;
                    cout << YELLOW << "   _____   _____   _____   _____   _____ \n";
                    cout << "  / ____| / ____| / ____| / ____| / ____|\n";
                    cout << " | (___  | (___  | (___  | (___  | (___  \n";
                    cout << "  \\___ \\  \\___ \\  \\___ \\  \\___ \\  \\___ \\ \n";
                    cout << "  ____) | ____) | ____) | ____) | ____) |\n";
                    cout << " |_____/ |_____/ |_____/ |_____/ |_____/ \n" << RESET;
                } else {
                    cout << YELLOW << "The board is not complete yet. Keep trying!\n" << RESET;
                }
                break;
            }
            case 8: {
                cout << BOLD << BLUE << "Thanks for playing Sudoku!\n" << RESET;
                return 0;
            }
            default: {
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
                break;
            }
        }
    }

    return 0;
}
