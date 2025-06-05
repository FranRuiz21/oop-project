#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

// Utility functions
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Game forward declarations
void playBlackjack();
void playSudoku();
void playMinesweeper();
void playSeaBattle();
void playTicTacToe();


// Main menu
void displayMenu() {
    clearScreen();
    cout << "=================================\n";
    cout << "          MINI ARCADE           \n";
    cout << "=================================\n";
    cout << "1. Blackjack (21)\n";
    cout << "2. Sudoku\n";
    cout << "3. Minesweeper\n";
    cout << "4. SeaBattle\n";
    cout << "5. Tic-Tac-Toe\n";
    cout << "6. Exit\n";
    cout << "=================================\n";
    cout << "Enter your choice (1-6): ";
}

int main() {
    srand(time(0)); // Seed random number generator
    
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: playBlackjack(); break;
            case 2: playSudoku(); break;
            case 3: playMinesweeper(); break;
            case 4: playSeaBattle(); break;
            case 5: playTicTacToe(); break;
            case 6:
                cout << "Thanks for playing! Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                pressEnterToContinue();
        }
    }
    return 0;
}

// ================== GAME IMPLEMENTATIONS ==================

// 1. Blackjack
class Card {
public:
    string suit;
    string rank;
    int value;
    
    Card(string s, string r, int v) : suit(s), rank(r), value(v) {}
    string toString() { return rank + " of " + suit; }
};

class Deck {
private:
    vector<Card> cards;
public:
    Deck() {
        string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string ranks[] = {"2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
        int values[] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
        
        for (size_t s = 0; s < sizeof(suits)/sizeof(suits[0]); s++) {
            for (size_t i = 0; i < 13; i++) {
                cards.push_back(Card(suits[s], ranks[i], values[i]));
            }
        }
        shuffle();
    }
    
    void shuffle() {
        for (size_t i = 0; i < cards.size(); i++) {
            size_t j = i + rand() % (cards.size() - i);
            swap(cards[i], cards[j]);
        }
    }
    
    Card deal() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

class Hand {
protected:
    vector<Card> cards;
public:
    void add(Card card) { cards.push_back(card); }
    int getTotal() {
        int total = 0, aces = 0;
        for (size_t i = 0; i < cards.size(); i++) {
            total += cards[i].value;
            if (cards[i].rank == "Ace") aces++;
        }
        while (total > 21 && aces) { total -= 10; aces--; }
        return total;
    }
    void show(bool showFirst = true) {
        for (size_t i = 0; i < cards.size(); i++) {
            if (i == 0 && !showFirst) cout << "[hidden]\n";
            else cout << cards[i].toString() << "\n";
        }
    }
    Card getLastCard() { return cards.back(); }
};

void playBlackjack() {
    clearScreen();
    cout << "=== BLACKJACK ===\n\n";
    
    Deck deck;
    Hand player, dealer;
    
    // Initial deal
    player.add(deck.deal());
    dealer.add(deck.deal());
    player.add(deck.deal());
    dealer.add(deck.deal());
    
    // Player's turn
    cout << "Dealer's hand:\n";
    dealer.show(false);
    cout << "\nYour hand (" << player.getTotal() << "):\n";
    player.show();
    
    while (player.getTotal() < 21) {
        cout << "\nHit or stand? (h/s): ";
        char choice;
        cin >> choice;
        
        if (tolower(choice) == 'h') {
            player.add(deck.deal());
            cout << "\nYour hand (" << player.getTotal() << "):\n";
            player.show();
        } else break;
    }
    
    // Dealer's turn
    cout << "\nDealer's hand (" << dealer.getTotal() << "):\n";
    dealer.show();
    
    while (dealer.getTotal() < 17) {
        dealer.add(deck.deal());
        cout << "\nDealer hits:\n" << dealer.getLastCard().toString();
        cout << "\nDealer's hand (" << dealer.getTotal() << "):\n";
        dealer.show();
    }
    
    // Determine winner
    int playerTotal = player.getTotal();
    int dealerTotal = dealer.getTotal();
    
    cout << "\nFinal Scores:\n";
    cout << "You: " << playerTotal << "  Dealer: " << dealerTotal << "\n";
    
    if (playerTotal > 21) cout << "You busted. Dealer wins!\n";
    else if (dealerTotal > 21) cout << "Dealer busted. You win!\n";
    else if (playerTotal > dealerTotal) cout << "You win!\n";
    else if (playerTotal < dealerTotal) cout << "Dealer wins!\n";
    else cout << "It's a tie!\n";
    
    pressEnterToContinue();
}

// 2. Sudoku
const int SUDOKU_SIZE = 9;
const int SUDOKU_SUBGRID = 3;
const int SUDOKU_EMPTY = 0;

class Sudoku {
private:
    vector<vector<int> > board;
    vector<vector<int> > solution;
    vector<vector<bool> > fixed;
    
    bool isValid(int row, int col, int num) {
        // Check row and column
        for (int x = 0; x < SUDOKU_SIZE; x++) {
            if (board[row][x] == num || board[x][col] == num) return false;
        }
        // Check subgrid
        int startRow = row - row % SUDOKU_SUBGRID;
        int startCol = col - col % SUDOKU_SUBGRID;
        for (int i = 0; i < SUDOKU_SUBGRID; i++)
            for (int j = 0; j < SUDOKU_SUBGRID; j++)
                if (board[i+startRow][j+startCol] == num) return false;
        return true;
    }
    
    bool solveBoard() {
        for (int row = 0; row < SUDOKU_SIZE; row++) {
            for (int col = 0; col < SUDOKU_SIZE; col++) {
                if (board[row][col] == SUDOKU_EMPTY) {
                    for (int num = 1; num <= SUDOKU_SIZE; num++) {
                        if (isValid(row, col, num)) {
                            board[row][col] = num;
                            if (solveBoard()) return true;
                            board[row][col] = SUDOKU_EMPTY;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    void fillDiagonalSubgrids() {
        for (int box = 0; box < SUDOKU_SIZE; box += SUDOKU_SUBGRID) {
            fillSubgrid(box, box);
        }
    }
    
    void fillSubgrid(int row, int col) {
        vector<int> nums;
        for (int i = 1; i <= SUDOKU_SIZE; i++) nums.push_back(i);
        for (size_t i = 0; i < nums.size(); i++) {
            size_t j = i + rand() % (nums.size() - i);
            swap(nums[i], nums[j]);
        }
        
        int index = 0;
        for (int i = 0; i < SUDOKU_SUBGRID; i++) {
            for (int j = 0; j < SUDOKU_SUBGRID; j++) {
                board[row+i][col+j] = nums[index++];
                fixed[row+i][col+j] = true;
            }
        }
    }
    
    void removeNumbers(int difficulty) {
        int cellsToRemove = (difficulty == 1) ? 40 : (difficulty == 2) ? 50 : 60;
        vector<pair<int,int> > positions;
        
        for (int i = 0; i < SUDOKU_SIZE; i++)
            for (int j = 0; j < SUDOKU_SIZE; j++)
                positions.push_back(make_pair(i,j));
        
        for (size_t i = 0; i < positions.size(); i++) {
            size_t j = i + rand() % (positions.size() - i);
            swap(positions[i], positions[j]);
        }
        
        for (int i = 0; i < cellsToRemove; i++) {
            int row = positions[i].first;
            int col = positions[i].second;
            board[row][col] = SUDOKU_EMPTY;
            fixed[row][col] = false;
        }
    }

public:
    Sudoku() : board(SUDOKU_SIZE, vector<int>(SUDOKU_SIZE, SUDOKU_EMPTY)),
               fixed(SUDOKU_SIZE, vector<bool>(SUDOKU_SIZE, false)) {}
    
    void generatePuzzle(int difficulty) {
        board = vector<vector<int> >(SUDOKU_SIZE, vector<int>(SUDOKU_SIZE, SUDOKU_EMPTY));
        fixed = vector<vector<bool> >(SUDOKU_SIZE, vector<bool>(SUDOKU_SIZE, false));
        fillDiagonalSubgrids();
        solveBoard();
        solution = board;
        removeNumbers(difficulty);
    }
    
    void printBoard() {
        cout << "   ";
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            cout << col+1 << " ";
            if ((col+1) % SUDOKU_SUBGRID == 0 && col != SUDOKU_SIZE-1) cout << "| ";
        }
        cout << "\n  -------------------------\n";
        
        for (int row = 0; row < SUDOKU_SIZE; row++) {
            cout << row+1 << " |";
            for (int col = 0; col < SUDOKU_SIZE; col++) {
                if (board[row][col] == SUDOKU_EMPTY) cout << "  ";
                else cout << board[row][col] << " ";
                if ((col+1) % SUDOKU_SUBGRID == 0 && col != SUDOKU_SIZE-1) cout << "| ";
            }
            cout << "\n";
            if ((row+1) % SUDOKU_SUBGRID == 0 && row != SUDOKU_SIZE-1)
                cout << "  -------------------------\n";
        }
    }
    
    bool makeMove(int row, int col, int num) {
        if (row < 0 || row >= SUDOKU_SIZE || col < 0 || col >= SUDOKU_SIZE) {
            cout << "Invalid position.\n"; return false;
        }
        if (fixed[row][col]) {
            cout << "Fixed cell. Can't change.\n"; return false;
        }
        if (num < 1 || num > 9) {
            cout << "Invalid number (1-9).\n"; return false;
        }
        if (!isValid(row, col, num)) {
            cout << "Invalid move. Conflict exists.\n"; return false;
        }
        board[row][col] = num;
        return true;
    }
    
    bool isComplete() {
        for (int row = 0; row < SUDOKU_SIZE; row++) {
            for (int col = 0; col < SUDOKU_SIZE; col++) {
                if (board[row][col] == SUDOKU_EMPTY || !isValid(row, col, board[row][col]))
                    return false;
            }
        }
        return true;
    }
    
    void showSolution() {
        cout << "\nSolution:\n";
        for (int row = 0; row < SUDOKU_SIZE; row++) {
            for (int col = 0; col < SUDOKU_SIZE; col++) {
                cout << solution[row][col] << " ";
                if ((col+1) % SUDOKU_SUBGRID == 0 && col != SUDOKU_SIZE-1) cout << "| ";
            }
            cout << "\n";
            if ((row+1) % SUDOKU_SUBGRID == 0 && row != SUDOKU_SIZE-1)
                cout << "------+-------+------\n";
        }
    }
    
    void resetBoard() {
        for (int row = 0; row < SUDOKU_SIZE; row++)
            for (int col = 0; col < SUDOKU_SIZE; col++)
                if (!fixed[row][col]) board[row][col] = SUDOKU_EMPTY;
    }
};

void playSudoku() {
    clearScreen();
    cout << "=== SUDOKU ===\n\n";
    
    Sudoku game;
    cout << "Select difficulty:\n1. Easy\n2. Medium\n3. Hard\nChoice: ";
    int difficulty;
    cin >> difficulty;
    game.generatePuzzle(difficulty);
    
    while (true) {
        clearScreen();
        cout << "=== SUDOKU ===\n\n";
        game.printBoard();
        
        if (game.isComplete()) {
            cout << "\nCongratulations! Puzzle solved!\n";
            break;
        }
        
        cout << "\nOptions:\n1. Make move\n2. Show solution\n3. Reset board\n4. Back to menu\nChoice: ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            int row, col, num;
            cout << "Enter row (1-9), column (1-9), number (1-9): ";
            cin >> row >> col >> num;
            game.makeMove(row-1, col-1, num);
        } 
        else if (choice == 2) {
            game.showSolution();
            pressEnterToContinue();
            break;
        }
        else if (choice == 3) {
            game.resetBoard();
            cout << "Board reset.\n";
            pressEnterToContinue();
        }
        else if (choice == 4) {
            break;
        }
    }
    pressEnterToContinue();
}

// 3. Minesweeper
const int MS_SIZE = 10;
const int MS_MINES = 15;

class Minesweeper {
private:
    vector<vector<char> > board;
    vector<vector<bool> > mines;
    vector<vector<bool> > revealed;
    int remaining;
    
    void placeMines() {
        int count = 0;
        while (count < MS_MINES) {
            int x = rand() % MS_SIZE;
            int y = rand() % MS_SIZE;
            if (!mines[x][y]) {
                mines[x][y] = true;
                count++;
            }
        }
    }
    
    int countAdjacentMines(int x, int y) {
        int count = 0;
        for (int i = max(0, x-1); i <= min(MS_SIZE-1, x+1); i++) {
            for (int j = max(0, y-1); j <= min(MS_SIZE-1, y+1); j++) {
                if (mines[i][j]) count++;
            }
        }
        return count;
    }

public:
    Minesweeper() : board(MS_SIZE, vector<char>(MS_SIZE, '#')),
                   mines(MS_SIZE, vector<bool>(MS_SIZE, false)),
                   revealed(MS_SIZE, vector<bool>(MS_SIZE, false)),
                   remaining(MS_SIZE*MS_SIZE - MS_MINES) {
        placeMines();
    }
    
    void printBoard(bool showMines = false) {
        cout << "  ";
        for (int i = 0; i < MS_SIZE; i++) cout << i << " ";
        cout << "\n";
        
        for (int i = 0; i < MS_SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < MS_SIZE; j++) {
                if (showMines && mines[i][j]) cout << "* ";
                else if (revealed[i][j]) {
                    int count = countAdjacentMines(i, j);
                    cout << (count ? to_string(count) : " ") << " ";
                }
                else cout << "# ";
            }
            cout << "\n";
        }
    }
    
    bool reveal(int x, int y) {
        if (x < 0 || x >= MS_SIZE || y < 0 || y >= MS_SIZE || revealed[x][y]) 
            return false;
        
        revealed[x][y] = true;
        if (mines[x][y]) return true;
        
        remaining--;
        if (countAdjacentMines(x, y) == 0) {
            for (int i = max(0, x-1); i <= min(MS_SIZE-1, x+1); i++) {
                for (int j = max(0, y-1); j <= min(MS_SIZE-1, y+1); j++) {
                    reveal(i, j);
                }
            }
        }
        return false;
    }
    
    bool isWon() { return remaining == 0; }
};

void playMinesweeper() {
    clearScreen();
    cout << "=== MINESWEEPER ===\n\n";
    
    Minesweeper game;
    while (true) {
        clearScreen();
        cout << "=== MINESWEEPER ===\n\n";
        game.printBoard();
        
        if (game.isWon()) {
            cout << "\nCongratulations! You found all the mines!\n";
            game.printBoard(true);
            break;
        }
        
        int x, y;
        cout << "\nEnter coordinates (row column): ";
        cin >> x >> y;
        
        if (game.reveal(x, y)) {
            clearScreen();
            cout << "=== MINESWEEPER ===\n\n";
            cout << "BOOM! You hit a mine!\n";
            game.printBoard(true);
            break;
        }
    }
    pressEnterToContinue();
}

// 4. Sea Battle

class SeaBattle {
private:
    static const int SIZE = 10;
    vector<vector<int> > board; // 0=empty, 1=ship, 2=hit, 3=miss
    int shipsRemaining;
    
    void placeShips(int shipCount) {
        int placed = 0;
        while (placed < shipCount) {
            int x = rand() % SIZE;
            int y = rand() % SIZE;
            if (board[x][y] == 0) {
                board[x][y] = 1;
                placed++;
            }
        }
    }
    
    void printBoard() {
        // Clear screen and print header
        system("clear || cls");
        printf("\033[36;40m");
        cout << "===========================\n";
        cout << "       SEA BATTLE GAME\n";
        cout << "===========================\n";
        printf("\033[0m");

        // Print column numbers
        printf("\033[33;40m  ");
        for (int i = 0; i < SIZE; i++) printf("%d ", i);
        printf("\n");

        // Print board
        for (int i = 0; i < SIZE; i++) {
            printf("\033[33;40m%d ", i);
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0 || board[i][j] == 1) {
                    printf("\033[34;44m  "); // Unknown (water)
                }
                else if (board[i][j] == 2) {
                    printf("\033[31;47mX "); // Hit
                }
                else {
                    printf("\033[30;47mO "); // Miss
                }
            }
            printf("\n");
        }
        printf("\033[0m");

        // Print ships remaining
        printf("\033[33;40m");
        cout << "\nShips remaining: " << shipsRemaining << endl;
        printf("\033[0m");
    }

public:
    SeaBattle() : board(SIZE, vector<int>(SIZE, 0)), shipsRemaining(5) {
        srand(time(0));
        placeShips(5);
    }
    
    void play() {
        while (shipsRemaining > 0) {
            printBoard();
            
            // Get player input
            printf("\033[37;40m");
            cout << "Enter shot coordinates (row column): ";
            int x, y;
            cin >> x >> y;

            // Validate input
            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                printf("\033[31;40m");
                cout << "Invalid coordinates! Use numbers from 0 to 9.\n";
                printf("\033[0m");
                cin.ignore();
                cin.get();
                continue;
            }

            // Process shot
            if (board[x][y] == 1) { // Hit a ship
                board[x][y] = 2;
                shipsRemaining--;
                printf("\033[32;40m");
                cout << "Hit! ";
                if (shipsRemaining > 0) {
                    cout << shipsRemaining << " ship(s) remaining.\n";
                } else {
                    cout << "You sank all the ships!\n";
                }
                printf("\033[0m");
            } 
            else if (board[x][y] == 0) { // Miss
                board[x][y] = 3;
                printf("\033[31;40m");
                cout << "Miss!\n";
                printf("\033[0m");
            }
            else { // Already shot here
                printf("\033[33;40m");
                cout << "You already shot here!\n";
                printf("\033[0m");
            }

            // Pause before continuing
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }

        // Final board and victory message
        printBoard();
        printf("\033[32;40m");
        cout << "\nCongratulations! You won!\n";
        printf("\033[0m");
        cout << "Press Enter to return to menu...";
        cin.ignore();
        cin.get();
    }
};
void playSeaBattle() {
    SeaBattle game;
    game.play();
}

// // In your arcade menu, replace the playBattleship() function with:
// void playSeaBattle() {
//     SeaBattle game;
//     game.play();
// }

// 5. Tic-Tac-Toe
const int TTT_SIZE = 3;

class TicTacToe {
private:
    vector<vector<char> > board;
    char currentPlayer;
    
    bool checkWin(char player) {
        // Check rows and columns
        for (int i = 0; i < TTT_SIZE; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        // Check diagonals
        return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
               (board[0][2] == player && board[1][1] == player && board[2][0] == player);
    }

public:
    TicTacToe() : board(TTT_SIZE, vector<char>(TTT_SIZE, ' ')), currentPlayer('X') {}
    
    void printBoard() {
        cout << "\n";
        for (int i = 0; i < TTT_SIZE; i++) {
            for (int j = 0; j < TTT_SIZE; j++) {
                cout << board[i][j] << (j < TTT_SIZE-1 ? " | " : "");
            }
            cout << "\n" << (i < TTT_SIZE-1 ? "---------\n" : "");
        }
        cout << "\n";
    }
    
    bool makeMove(int row, int col) {
        if (row < 0 || row >= TTT_SIZE || col < 0 || col >= TTT_SIZE || board[row][col] != ' ') {
            cout << "Invalid move. Try again.\n";
            return false;
        }
        
        board[row][col] = currentPlayer;
        return true;
    }
    
    bool isGameOver() {
        if (checkWin('X') || checkWin('O')) return true;
        
        for (int i = 0; i < TTT_SIZE; i++)
            for (int j = 0; j < TTT_SIZE; j++)
                if (board[i][j] == ' ') return false;
        return true;
    }
    
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
    }
    
    char getCurrentPlayer() { return currentPlayer; }
    
    char getWinner() {
        if (checkWin('X')) return 'X';
        if (checkWin('O')) return 'O';
        return ' ';
    }
};

void playTicTacToe() {
    clearScreen();
    cout << "=== TIC-TAC-TOE ===\n\n";
    
    TicTacToe game;
    while (!game.isGameOver()) {
        game.printBoard();
        int row, col;
        cout << "Player " << game.getCurrentPlayer() << ", enter row (1-3) and column (1-3): ";
        cin >> row >> col;
        row--; col--; // Convert to 0-based index
        
        if (game.makeMove(row, col)) {
            if (game.isGameOver()) break;
            game.switchPlayer();
        }
    }
    
    game.printBoard();
    char winner = game.getWinner();
    if (winner != ' ') cout << "Player " << winner << " wins!\n";
    else cout << "It's a draw!\n";
    
    pressEnterToContinue();
}