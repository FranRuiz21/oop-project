#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
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
