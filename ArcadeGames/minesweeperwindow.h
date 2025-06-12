#ifndef MINESWEEPERWINDOW_H
#define MINESWEEPERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "minesweeper.h"

class MinesweeperWindow : public QWidget {
    Q_OBJECT
public:
    explicit MinesweeperWindow(QWidget *parent = nullptr);

private:
    Minesweeper game;
    QGridLayout *gridLayout;
    QLabel *mineCounterLabel;
    QPushButton *resetButton;
    QVector<QVector<QPushButton*>> buttons;

    void setupUI();
    void updateBoard();
    void revealCell(int row, int col);
    void updateMineCounter();

private slots:
    void cellClicked();
    void resetClicked();
};

#endif // MINESWEEPERWINDOW_H
