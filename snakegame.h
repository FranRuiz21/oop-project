#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include <QKeyEvent>
#include <QPainter>
#include <cstdlib>
#include <ctime>
#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <QSoundEffect> 
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


    const int GRID_COLS = 40;
    const int GRID_ROWS = 40;
    int speed = 100;
    QSoundEffect *eatSound;
    QSoundEffect *crashSound; //SOUND ADDED
    QVector<QPoint> snake;
    QPoint food;
    Direction dir = Right;
    QTimer *timer;
    bool gameOver = false;
    int score = 0;

    void spawnFood();
};

#endif
