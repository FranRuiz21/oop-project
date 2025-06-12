#include "minesweeperwindow.h"
#include <QMessageBox>
#include <QString>

MinesweeperWindow::MinesweeperWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Minesweeper");
    setFixedSize(350, 450);

    setupUI();
    updateBoard();
    updateMineCounter();
}

void MinesweeperWindow::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mineCounterLabel = new QLabel(this);
    mineCounterLabel->setAlignment(Qt::AlignCenter);
    mineCounterLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    mainLayout->addWidget(mineCounterLabel);

    resetButton = new QPushButton("Reset", this);
    resetButton->setFixedHeight(30);
    mainLayout->addWidget(resetButton);
    connect(resetButton, &QPushButton::clicked, this, &MinesweeperWindow::resetClicked);

    gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);

    buttons.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        buttons[i].resize(BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            QPushButton *btn = new QPushButton("#");
            btn->setFixedSize(30, 30);
            btn->setStyleSheet("font-weight: bold; font-size: 16px;");
            gridLayout->addWidget(btn, i, j);
            buttons[i][j] = btn;

            connect(btn, &QPushButton::clicked, this, &MinesweeperWindow::cellClicked);
        }
    }
}

void MinesweeperWindow::updateBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (game.isRevealed(i, j)) {
                if (game.hasMine(i, j)) {
                    buttons[i][j]->setText("*");
                    buttons[i][j]->setStyleSheet("color: red; font-weight: bold; font-size: 16px;");
                } else {
                    int count = game.adjacentMines(i, j);
                    buttons[i][j]->setText(count > 0 ? QString::number(count) : "");
                    buttons[i][j]->setEnabled(false);
                    buttons[i][j]->setStyleSheet("font-weight: bold; font-size: 16px;");
                }
            } else {
                buttons[i][j]->setText("#");
                buttons[i][j]->setEnabled(true);
                buttons[i][j]->setStyleSheet("font-weight: bold; font-size: 16px;");
            }
        }
    }
}

void MinesweeperWindow::updateMineCounter() {
    // Mines left = total mines - revealed mines (no flagging implemented)
    int revealedCount = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (game.isRevealed(i, j) && game.hasMine(i, j))
                revealedCount++;

    int minesLeft = MINES - revealedCount;
    mineCounterLabel->setText(QString("Mines left: %1").arg(minesLeft));
}

void MinesweeperWindow::cellClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int row = -1, col = -1;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (buttons[i][j] == btn) {
                row = i; col = j;
                break;
            }
        }
        if (row != -1) break;
    }

    if (row == -1 || col == -1) return;

    revealCell(row, col);
}

void MinesweeperWindow::revealCell(int row, int col) {
    if (game.isRevealed(row, col)) return;

    bool hitMine = game.reveal(row, col);

    updateBoard();
    updateMineCounter();

    if (hitMine) {
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j)
                buttons[i][j]->setEnabled(false);

        QMessageBox::critical(this, "Game Over", "You hit a mine!");
    } else if (game.isWon()) {
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j)
                buttons[i][j]->setEnabled(false);

        QMessageBox::information(this, "Victory", "Congratulations! You won!");
    }
}

void MinesweeperWindow::resetClicked() {
    game.reset();
    updateBoard();
    updateMineCounter();
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            buttons[i][j]->setEnabled(true);
}
