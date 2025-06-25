/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QVBoxLayout *buttonLayout;
    QPushButton *sudokuButton;
    QPushButton *minesweeperButton;
    QPushButton *snakeButton;
    QPushButton *tictactoeButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(355, 282);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #90cad6;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(24);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("color: #1389a1;"));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(centralwidget);
        subtitleLabel->setObjectName("subtitleLabel");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(14);
        font1.setBold(true);
        subtitleLabel->setFont(font1);
        subtitleLabel->setStyleSheet(QString::fromUtf8("color: #1389a1;"));
        subtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(subtitleLabel);

        buttonLayout = new QVBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        sudokuButton = new QPushButton(centralwidget);
        sudokuButton->setObjectName("sudokuButton");

        buttonLayout->addWidget(sudokuButton);

        minesweeperButton = new QPushButton(centralwidget);
        minesweeperButton->setObjectName("minesweeperButton");

        buttonLayout->addWidget(minesweeperButton);

        snakeButton = new QPushButton(centralwidget);
        snakeButton->setObjectName("snakeButton");

        buttonLayout->addWidget(snakeButton);

        tictactoeButton = new QPushButton(centralwidget);
        tictactoeButton->setObjectName("tictactoeButton");

        buttonLayout->addWidget(tictactoeButton);

        buttonLayout->setStretch(0, 1);
        buttonLayout->setStretch(1, 1);
        buttonLayout->setStretch(2, 1);
        buttonLayout->setStretch(3, 1);

        verticalLayout->addLayout(buttonLayout);

        verticalLayout->setStretch(2, 1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Arcade Games", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("MainWindow", "OOP Group 6", nullptr));
        sudokuButton->setText(QCoreApplication::translate("MainWindow", "Sudoku", nullptr));
        minesweeperButton->setText(QCoreApplication::translate("MainWindow", "Minesweeper", nullptr));
        snakeButton->setText(QCoreApplication::translate("MainWindow", "Snake", nullptr));
        tictactoeButton->setText(QCoreApplication::translate("MainWindow", "Tic Tac Toe", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
