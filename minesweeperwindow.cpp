#include "minesweeperwindow.h"
#include "cellbutton.h"

MinesweeperWindow::MinesweeperWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Minesweeper");


    setupUI();
    updateBoard();
    updateMineCounter();
}

void MinesweeperWindow::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mineCounterLabel = new QLabel(this);
    mineCounterLabel->setAlignment(Qt::AlignCenter);
    mineCounterLabel->setStyleSheet("font-size: 24px; font-weight: bold;"); // un poco más grande para pantallas grandes
    mainLayout->addWidget(mineCounterLabel);

    resetButton = new QPushButton("Reset", this);
    resetButton->setFixedHeight(40); // un poco más alto
    mainLayout->addWidget(resetButton);
    connect(resetButton, &QPushButton::clicked, this, &MinesweeperWindow::resetClicked);

    gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);

    buttons.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        buttons[i].resize(BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            CellButton *btn = new CellButton(i, j, this);

            // ✅ En lugar de tamaño fijo, usa size policy expansivo
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            btn->setStyleSheet("font-weight: bold; font-size: 20px;"); // más grande para pantallas grandes

            gridLayout->addWidget(btn, i, j);
            buttons[i][j] = btn;

            connect(btn, &CellButton::leftClicked, this, &MinesweeperWindow::revealCell);
            connect(btn, &CellButton::rightClicked, this, &MinesweeperWindow::toggleFlag);
        }
    }
}

void MinesweeperWindow::updateBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (game.isRevealed(i, j)) {
                if (game.hasMine(i, j)) {
                    buttons[i][j]->setText("*");
                    buttons[i][j]->setStyleSheet("color: red; font-weight: bold; font-size: 20px;");
                } else {
                    int count = game.adjacentMines(i, j);
                    buttons[i][j]->setText(count > 0 ? QString::number(count) : "");
                    buttons[i][j]->setEnabled(false);
                    buttons[i][j]->setStyleSheet("font-weight: bold; font-size: 20px;");
                }
            } else if (game.isFlagged(i, j)) {
                buttons[i][j]->setText("F");
                buttons[i][j]->setStyleSheet("color: blue; font-weight: bold; font-size: 20px;");
            } else {
                buttons[i][j]->setText("#");
                buttons[i][j]->setEnabled(true);
                buttons[i][j]->setStyleSheet("font-weight: bold; font-size: 20px;");
            }
        }
    }
}

void MinesweeperWindow::updateMineCounter() {
    int flaggedCount = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (game.isFlagged(i, j))
                flaggedCount++;

    int minesLeft = MINES - flaggedCount;
    mineCounterLabel->setText(QString("Mines left: %1").arg(minesLeft));
}

void MinesweeperWindow::revealCell(int row, int col) {
    if (game.isRevealed(row, col) || game.isFlagged(row, col)) return;

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

void MinesweeperWindow::toggleFlag(int row, int col) {
    if (game.isRevealed(row, col)) return;

    game.toggleFlag(row, col);
    updateBoard();
    updateMineCounter();
}

void MinesweeperWindow::resetClicked() {
    game.reset();
    updateBoard();
    updateMineCounter();
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            buttons[i][j]->setEnabled(true);
}

void MinesweeperWindow::cellClicked() {
}
