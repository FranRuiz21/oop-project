#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QPoint>

class SnakeGame : public QWidget {
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);

    int getScore() const { return score; }
    void resetGame();

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void gameLoop();

private:
    enum Direction { Left, Right, Up, Down };

    const int DOT_SIZE = 10;
    const int WIDTH = 400;
    const int HEIGHT = 400;
    int speed = 100; // ms

    QVector<QPoint> snake;
    QPoint food;
    Direction dir = Right;
    QTimer *timer;
    bool gameOver = false;
    int score = 0;

    void spawnFood();
};

#endif // SNAKEGAME_H
