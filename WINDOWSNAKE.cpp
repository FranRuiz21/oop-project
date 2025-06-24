#include "windowsnake.h"
#include "snakegame.h"


Window::Window(QWidget *parent)
    : QWidget(parent)
{
    snakeGame = new SnakeGame(this);
    resetButton = new QPushButton("Reset", this);
    scoreLabel = new QLabel("Score: 0", this);

    scoreLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scoreLabel);
    layout->addWidget(snakeGame, 1);
    layout->addWidget(resetButton);

    setLayout(layout);
    setWindowTitle("Arcade - Snake Retro");
    resize(420, 500);

    connect(resetButton, &QPushButton::clicked, this, &Window::resetGame);

    QTimer *scoreTimer = new QTimer(this);
    connect(scoreTimer, &QTimer::timeout, this, &Window::updateScore);
    scoreTimer->start(100);
}
void Window::updateScore()
{
    scoreLabel->setText(QString("Score: %1").arg(snakeGame->getScore()));
}

void Window::resetGame()
{
    snakeGame->resetGame();
}
