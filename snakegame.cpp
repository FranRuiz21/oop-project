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
    snake.push_back(QPoint(WIDTH/2, HEIGHT/2));
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
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, WIDTH, HEIGHT);

    painter.setBrush(Qt::green);
    for (const QPoint &p : std::as_const(snake)) {
        painter.drawRect(p.x(), p.y(), DOT_SIZE, DOT_SIZE);
    }

    painter.setBrush(Qt::red);
    painter.drawRect(food.x(), food.y(), DOT_SIZE, DOT_SIZE);


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
    case Left:  head.rx() -= DOT_SIZE; break;
    case Right: head.rx() += DOT_SIZE; break;
    case Up:    head.ry() -= DOT_SIZE; break;
    case Down:  head.ry() += DOT_SIZE; break;
    }

    if (head.x() < 0 || head.x() >= WIDTH || head.y() < 0 || head.y() >= HEIGHT || snake.contains(head)) {
        gameOver = true;
        update();
        return;
    }

    snake.push_front(head);

    if (head == food) {
        score += 10; // Aumenta puntos
        spawnFood();
    } else {
        snake.pop_back();
    }

    update();
}

void SnakeGame::spawnFood()
{
    int maxX = WIDTH / DOT_SIZE;
    int maxY = HEIGHT / DOT_SIZE;
    QPoint p;
    do {
        p.setX((rand() % maxX) * DOT_SIZE);
        p.setY((rand() % maxY) * DOT_SIZE);
    } while (snake.contains(p));
    food = p;
}
