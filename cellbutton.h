#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QMouseEvent>
#include <QPushButton>

class CellButton : public QPushButton
{
    Q_OBJECT

public:
    CellButton(int x, int y, QWidget *parent = nullptr);

signals:
    void leftClicked(int x, int y);
    void rightClicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int posX, posY;
};

#endif // CELLBUTTON_H
