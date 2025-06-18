#include "TicTacToeWindow.h"
#include <QMessageBox>

TicTacToeWindow::TicTacToeWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Tic Tac Toe");

    QGridLayout* layout = new QGridLayout(this);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j] = new QPushButton(" ");
            buttons[i][j]->setFixedSize(100, 100);
            buttons[i][j]->setFont(QFont("Arial", 24, QFont::Bold));
            layout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &QPushButton::clicked, this, &TicTacToeWindow::handleButton);
        }
    }

    statusLabel = new QLabel("Current Player: X", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(statusLabel, 3, 0, 1, 3);

    resetButton = new QPushButton("Reset", this);
    layout->addWidget(resetButton, 4, 0, 1, 3);
    connect(resetButton, &QPushButton::clicked, this, &TicTacToeWindow::resetGame);

    setLayout(layout);
}

void TicTacToeWindow::handleButton() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn || btn->text() != " ")
        return;

    int row = -1, col = -1;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (buttons[i][j] == btn) {
                row = i; col = j;
            }

    if (!game.makeMove(row, col))
        return;

    btn->setText(QString(game.getCurrentPlayer()));

    if (game.checkWin(game.getCurrentPlayer())) {
        QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(game.getCurrentPlayer()));
        disableButtons();
        return;
    }

    if (game.isDraw()) {
        QMessageBox::information(this, "Game Over", "It's a draw!");
        disableButtons();
        return;
    }

    game.switchPlayer();
    updateStatus();
}

void TicTacToeWindow::updateStatus() {
    statusLabel->setText(QString("Current Player: %1").arg(game.getCurrentPlayer()));
}

void TicTacToeWindow::disableButtons() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setEnabled(false);
}

void TicTacToeWindow::resetGame() {
    game = TicTacToe();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            buttons[i][j]->setText(" ");
            buttons[i][j]->setEnabled(true);
        }

    updateStatus();
}
