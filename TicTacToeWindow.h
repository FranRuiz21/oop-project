#ifndef TICTACTOEWINDOW_H
#define TICTACTOEWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "TicTacToe.h"

class TicTacToeWindow : public QWidget
{
    Q_OBJECT

public:
    TicTacToeWindow(QWidget *parent = nullptr);

private slots:
    void handleButton();

private:
    TicTacToe game;
    QPushButton *buttons[3][3];
    QLabel *statusLabel;
    QPushButton *resetButton;

    void updateStatus();
    void disableButtons();
    void resetGame();
};

#endif // TICTACTOEWINDOW_H
