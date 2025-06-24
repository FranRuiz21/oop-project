#include "mainwindow.h"
#include "TicTacToeWindow.h"
#include "windowsnake.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "sudokuwindow.h"
#include "minesweeperwindow.h"

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

    // Connect buttons
    connect(ui->sudokuButton, &QPushButton::clicked, this, &MainWindow::onSudokuClicked);
    connect(ui->minesweeperButton, &QPushButton::clicked, this, &MainWindow::onMinesweeperClicked);
    connect(ui->snakeButton, &QPushButton::clicked, this, &MainWindow::onSnakeClicked);
    connect(ui->tictactoeButton, &QPushButton::clicked, this, &MainWindow::onTicTacToeClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onSudokuClicked() {

    SudokuWindow *sudokuWindow = new SudokuWindow();
    sudokuWindow->setAttribute(Qt::WA_DeleteOnClose);
    sudokuWindow->show();

}

void MainWindow::onMinesweeperClicked() {
    MinesweeperWindow *w = new MinesweeperWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

}

void MainWindow::onSnakeClicked() {
    Window *snakeWindow = new Window();
    snakeWindow->setAttribute(Qt::WA_DeleteOnClose);
    snakeWindow->show();
}
void MainWindow::onTicTacToeClicked() {
    TicTacToeWindow* w = new TicTacToeWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

}


