#ifndef SUDOKU_H
#define SUDOKU_H

#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

using namespace std;

const int SIZE = 9;
const int SUBGRID = 3;
const int EMPTY = 0;

class Sudoku
{
private:
    vector<vector<int>> board;
    vector<vector<int>> solution;
    vector<vector<bool>> fixed;

    QMediaPlayer *backgroundMusic;
    QAudioOutput *backgroundOutput;
    bool isValid(int row, int col, int num);
    bool solveBoard();
    void generateSolution();
    void fillDiagonalSubgrids();
    void fillSubgrid(int row, int col);
    void removeNumbers(int difficulty);

public:
    Sudoku();
    ~Sudoku();
    void generatePuzzle(int difficulty);
    bool isFixed(int row, int col) const;
    bool makeMove(int row, int col, int num);
    bool isComplete();
    void resetBoard();
    int getCell(int row, int col) const;
    int getSolution(int row, int col) const;
};

#endif // SUDOKU_H
