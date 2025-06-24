#ifndef WINDOWSNAKE_H
#define WINDOWSNAKE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

class SnakeGame;
class QPushButton;
class QLabel;

class Window : public QWidget {
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

private slots:
    void updateScore();
    void resetGame();

private:
    SnakeGame *snakeGame;
    QPushButton *resetButton;
    QLabel *scoreLabel;
};

#endif // WINDOW_H
