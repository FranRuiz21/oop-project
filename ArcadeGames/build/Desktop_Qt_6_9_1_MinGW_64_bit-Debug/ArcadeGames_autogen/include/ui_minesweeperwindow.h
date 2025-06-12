/********************************************************************************
** Form generated from reading UI file 'minesweeperwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINESWEEPERWINDOW_H
#define UI_MINESWEEPERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MinesweeperWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *mineCounter;
    QGridLayout *gridLayout;
    QPushButton *resetButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MinesweeperWindow)
    {
        if (MinesweeperWindow->objectName().isEmpty())
            MinesweeperWindow->setObjectName("MinesweeperWindow");
        MinesweeperWindow->resize(500, 600);
        centralwidget = new QWidget(MinesweeperWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        mineCounter = new QLabel(centralwidget);
        mineCounter->setObjectName("mineCounter");
        mineCounter->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(mineCounter);

        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");

        verticalLayout->addWidget(gridLayout);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");

        verticalLayout->addWidget(resetButton);

        MinesweeperWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MinesweeperWindow);
        menubar->setObjectName("menubar");
        MinesweeperWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MinesweeperWindow);
        statusbar->setObjectName("statusbar");
        MinesweeperWindow->setStatusBar(statusbar);

        retranslateUi(MinesweeperWindow);

        QMetaObject::connectSlotsByName(MinesweeperWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MinesweeperWindow)
    {
        MinesweeperWindow->setWindowTitle(QCoreApplication::translate("MinesweeperWindow", "Minesweeper", nullptr));
        mineCounter->setText(QCoreApplication::translate("MinesweeperWindow", "Mines left: 15", nullptr));
        resetButton->setText(QCoreApplication::translate("MinesweeperWindow", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MinesweeperWindow: public Ui_MinesweeperWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINESWEEPERWINDOW_H
