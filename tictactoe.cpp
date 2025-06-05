#include <iostream>
#include <vector>
using namespace std;

void printBoard(const vector<vector<char> >& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << (j < 2 ? " | " : "");
        }
        cout << "\n" << (i < 2 ? "---------\n" : "");
    }
}

bool checkWin(const vector<vector<char> >& board, char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

int main() {
    vector<vector<char> > board(3, vector<char>(3, ' '));
    char currentPlayer = 'X';
    int moves = 0;

    while (moves < 9) {
        printBoard(board);
        int row, col;
        cout << "Player " << currentPlayer << ", enter row (1-3) and column (1-3): ";
        cin >> row >> col;
        row--; col--;

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            moves++;

            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                cout << "Player " << currentPlayer << " wins!\n";
                return 0;
            }
            currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
    cout << "It's a draw!\n";
    return 0;
}