#include "sudokuwindow.h"
#include <QHeaderView>
#include <QMessageBox>

SudokuWindow::SudokuWindow(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void SudokuWindow::setupUI()
{
    table = new QTableWidget(9, 9, this);
    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    table->setFont(QFont("Arial", 14));
    connect(table, &QTableWidget::cellChanged, this, &SudokuWindow::handleCellChanged);

    btnEasy = new QPushButton("Easy");
    btnMedium = new QPushButton("Medium");
    btnHard = new QPushButton("Hard");
    btnReset = new QPushButton("Reset");
    btnCheck = new QPushButton("Check");
    btnSolution = new QPushButton("Show Solution");

    connect(btnEasy, &QPushButton::clicked, this, &SudokuWindow::newGameEasy);
    connect(btnMedium, &QPushButton::clicked, this, &SudokuWindow::newGameMedium);
    connect(btnHard, &QPushButton::clicked, this, &SudokuWindow::newGameHard);
    connect(btnReset, &QPushButton::clicked, this, &SudokuWindow::resetBoard);
    connect(btnCheck, &QPushButton::clicked, this, &SudokuWindow::checkCompletion);
    connect(btnSolution, &QPushButton::clicked, this, &SudokuWindow::showSolution);

    QHBoxLayout *difficultyLayout = new QHBoxLayout;
    difficultyLayout->addWidget(btnEasy);
    difficultyLayout->addWidget(btnMedium);
    difficultyLayout->addWidget(btnHard);

    QHBoxLayout *actionLayout = new QHBoxLayout;
    actionLayout->addWidget(btnReset);
    actionLayout->addWidget(btnCheck);
    actionLayout->addWidget(btnSolution);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(difficultyLayout);
    mainLayout->addWidget(table);
    mainLayout->addLayout(actionLayout);

    setLayout(mainLayout);
    setWindowTitle("Sudoku");
    setMinimumSize(500, 600);
}

void SudokuWindow::newGameEasy() {
    game.generatePuzzle(1);
    loadBoard();
    lockFixedCells();
}

void SudokuWindow::newGameMedium() {
    game.generatePuzzle(2);
    loadBoard();
    lockFixedCells();
}

void SudokuWindow::newGameHard() {
    game.generatePuzzle(3);
    loadBoard();
    lockFixedCells();
}

void SudokuWindow::loadBoard() {
    table->blockSignals(true);
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int val = game.getCell(row, col);
            QTableWidgetItem *item = new QTableWidgetItem(val == 0 ? "" : QString::number(val));
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, col, item);
        }
    }
    table->blockSignals(false);
}

void SudokuWindow::lockFixedCells() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (game.isFixed(row, col)) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                item->setBackground(Qt::lightGray);
            } else {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
                item->setBackground(Qt::white);
            }
        }
    }
}

void SudokuWindow::resetBoard() {
    game.resetBoard();
    loadBoard();
    lockFixedCells();
}

void SudokuWindow::checkCompletion() {
    if (game.isComplete()) {
        QMessageBox::information(this, "Sudoku", "Congratulations! You completed the puzzle!");
    } else {
        QMessageBox::warning(this, "Sudoku", "The puzzle is not complete or contains mistakes.");
    }
}

void SudokuWindow::showSolution() {
    table->blockSignals(true);
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            table->item(row, col)->setText(QString::number(game.getSolution(row, col)));
        }
    }
    table->blockSignals(false);
}

void SudokuWindow::handleCellChanged(int row, int column) {
    QString val = table->item(row, column)->text();
    int num = val.toInt();
    if (num >= 1 && num <= 9) {
        game.makeMove(row, column, num);
    } else if (val.isEmpty()) {
        game.makeMove(row, column, 0);
    } else {
        table->item(row, column)->setText("");
    }
}
