#include "snakegame.h"
#include <QPainter>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    srand(time(nullptr));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeGame::gameLoop);

    resetGame();
}

void SnakeGame::resetGame()
{
    snake.clear();
    snake.push_back(QPoint(GRID_COLS / 2, GRID_ROWS / 2)); // Posición en grilla
    dir = Right;
    spawnFood();
    gameOver = false;
    score = 0;
    timer->start(speed);
    update();
}

void SnakeGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int cellWidth = width() / GRID_COLS;
    int cellHeight = height() / GRID_ROWS;
    int dotSize = qMin(cellWidth, cellHeight);

    painter.setBrush(Qt::black);
    painter.drawRect(rect());

    // Serpiente
    painter.setBrush(Qt::green);
    for (const QPoint &p : std::as_const(snake)) {
        painter.drawRect(p.x() * cellWidth, p.y() * cellHeight, dotSize, dotSize);
    }

    // Comida
    painter.setBrush(Qt::red);
    painter.drawEllipse(food.x() * cellWidth, food.y() * cellHeight, dotSize, dotSize);

    if (gameOver) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
    }
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        if (dir != Right) dir = Left;
        break;
    case Qt::Key_Right:
        if (dir != Left) dir = Right;
        break;
    case Qt::Key_Up:
        if (dir != Down) dir = Up;
        break;
    case Qt::Key_Down:
        if (dir != Up) dir = Down;
        break;
    }
}

void SnakeGame::gameLoop()
{
    if (gameOver) {
        timer->stop();
        return;
    }

    QPoint head = snake.front();

    switch (dir) {
    case Left:  head.rx() -= 1; break;
    case Right: head.rx() += 1; break;
    case Up:    head.ry() -= 1; break;
    case Down:  head.ry() += 1; break;
    }

    if (head.x() < 0 || head.x() >= GRID_COLS || head.y() < 0 || head.y() >= GRID_ROWS || snake.contains(head)) {
        gameOver = true;
        update();
        return;
    }

    snake.push_front(head);

    if (head == food) {
        score += 10;
        spawnFood();
    } else {
        snake.pop_back();
    }

    update();
}

void SnakeGame::spawnFood()
{
    QPoint p;
    do {
        p.setX(rand() % GRID_COLS);
        p.setY(rand() % GRID_ROWS);
    } while (snake.contains(p));
    food = p;
}

