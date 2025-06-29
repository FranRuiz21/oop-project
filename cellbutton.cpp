#include "cellbutton.h"


CellButton::CellButton(int x, int y, QWidget *parent)
    : QPushButton(parent)
    , posX(x)
    , posY(y)
{}

void CellButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit leftClicked(posX, posY);
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(posX, posY);
    }
}
