#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "sudokuwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set button styles
    QString buttonStyle = "background-color: #b2bfc2; color: #ffffff; font-family: 'Times New Roman'; font-weight: bold;";
    ui->sudokuButton->setStyleSheet(buttonStyle);
    ui->minesweeperButton->setStyleSheet(buttonStyle);
    ui->snakeButton->setStyleSheet(buttonStyle);
    ui->tictactoeButton->setStyleSheet(buttonStyle);
    ui->blackjackButton->setStyleSheet(buttonStyle);

    // Connect buttons
    connect(ui->sudokuButton, &QPushButton::clicked, this, &MainWindow::onSudokuClicked);
    connect(ui->minesweeperButton, &QPushButton::clicked, this, &MainWindow::onMinesweeperClicked);
    connect(ui->snakeButton, &QPushButton::clicked, this, &MainWindow::onSnakeClicked);
    connect(ui->tictactoeButton, &QPushButton::clicked, this, &MainWindow::onTicTacToeClicked);
    connect(ui->blackjackButton, &QPushButton::clicked, this, &MainWindow::onBlackjackClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onSudokuClicked() {

    SudokuWindow *sudokuWindow = new SudokuWindow();
    sudokuWindow->setAttribute(Qt::WA_DeleteOnClose);
    sudokuWindow->show();
    this->close();
}

void MainWindow::onMinesweeperClicked() {
    MinesweeperWindow *w = new MinesweeperWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    this->close();
}

void MainWindow::onSnakeClicked() {
    qDebug() << "Snake Clicked!";
}

void MainWindow::onTicTacToeClicked() {
    qDebug() << "Tic Tac Toe Clicked!";
}

void MainWindow::onBlackjackClicked() {
    qDebug() << "Blackjack Clicked!";
}
