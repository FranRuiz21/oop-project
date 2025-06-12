#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "sudoku.h"

class SudokuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuWindow(QWidget *parent = nullptr);

private slots:
    void newGameEasy();
    void newGameMedium();
    void newGameHard();
    void checkCompletion();
    void resetBoard();
    void showSolution();
    void handleCellChanged(int row, int column);

private:
    Sudoku game;
    QTableWidget *table;
    QPushButton *btnEasy, *btnMedium, *btnHard;
    QPushButton *btnReset, *btnCheck, *btnSolution;

    void setupUI();
    void loadBoard();
    void lockFixedCells();
};

#endif // SUDOKUWINDOW_H
