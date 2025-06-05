#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

const int SIZE = 10;
const int MINES = 15;

class Minesweeper {
private:
    vector<vector<char> > board;
    vector<vector<bool> > mines;
    vector<vector<bool> > revealed;
    int remaining;

    void placeMines() {
        int count = 0;
        while (count < MINES) {
            int x = rand() % SIZE;
            int y = rand() % SIZE;
            if (!mines[x][y]) {
                mines[x][y] = true;
                count++;
            }
        }
    }

    int countAdjacentMines(int x, int y) {
        int count = 0;
        for (int i = max(0, x-1); i <= min(SIZE-1, x+1); i++) {
            for (int j = max(0, y-1); j <= min(SIZE-1, y+1); j++) {
                if (mines[i][j]) count++;
            }
        }
        return count;
    }

public:
    Minesweeper() : board(SIZE, vector<char>(SIZE, '#')), 
                   mines(SIZE, vector<bool>(SIZE, false)),
                   revealed(SIZE, vector<bool>(SIZE, false)),
                   remaining(SIZE*SIZE - MINES) {
        srand(time(0));
        placeMines();
    }

    void printBoard(bool showMines = false) {
        cout << "  ";
        for (int i = 0; i < SIZE; i++) cout << i << " ";
        cout << "\n";

        for (int i = 0; i < SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < SIZE; j++) {
                if (showMines && mines[i][j]) cout << "* ";
                else if (revealed[i][j]) {
                    int count = countAdjacentMines(i, j);
                    if (count) cout << count << " ";
					else cout << "  ";
                }
                else cout << "# ";
            }
            cout << "\n";
        }
    }

    bool reveal(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || revealed[x][y]) return false;
        
        revealed[x][y] = true;
        if (mines[x][y]) return true;
        
        remaining--;
        if (countAdjacentMines(x, y) == 0) {
            for (int i = max(0, x-1); i <= min(SIZE-1, x+1); i++) {
                for (int j = max(0, y-1); j <= min(SIZE-1, y+1); j++) {
                    reveal(i, j);
                }
            }
        }
        return false;
    }

    bool isWon() { return remaining == 0; }
};

int main() {
    Minesweeper game;
    while (true) {
        game.printBoard();
        int x, y;
        cout << "Enter coordinates (row column): ";
        cin >> x >> y;
        
        if (game.reveal(x, y)) {
            cout << "Game Over! You hit a mine.\n";
            game.printBoard(true);
            break;
        }
        
        if (game.isWon()) {
            cout << "Congratulations! You won!\n";
            game.printBoard(true);
            break;
        }
    }
    return 0;
}
