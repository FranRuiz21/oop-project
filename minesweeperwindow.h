#ifndef MINESWEEPERWINDOW_H
#define MINESWEEPERWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include "minesweeper.h"

class MinesweeperWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MinesweeperWindow(QWidget *parent = nullptr);

private:
    Minesweeper game;
    QGridLayout *gridLayout;
    QLabel *mineCounterLabel;
    QPushButton *resetButton;
    QVector<QVector<QPushButton *>> buttons;

    void setupUI();
    void updateBoard();
    void revealCell(int row, int col);
    void updateMineCounter();

private slots:
    void cellClicked();
    void resetClicked();
    void toggleFlag(int row, int col);
};

#endif // MINESWEEPERWINDOW_H
