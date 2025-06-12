/********************************************************************************
** Form generated from reading UI file 'sudokuwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOKUWINDOW_H
#define UI_SUDOKUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SudokuWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *resetButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SudokuWindow)
    {
        if (SudokuWindow->objectName().isEmpty())
            SudokuWindow->setObjectName("SudokuWindow");
        SudokuWindow->resize(600, 650);
        centralwidget = new QWidget(SudokuWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");

        verticalLayout->addWidget(gridLayout);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");

        verticalLayout->addWidget(resetButton);

        SudokuWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SudokuWindow);
        menubar->setObjectName("menubar");
        SudokuWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SudokuWindow);
        statusbar->setObjectName("statusbar");
        SudokuWindow->setStatusBar(statusbar);

        retranslateUi(SudokuWindow);

        QMetaObject::connectSlotsByName(SudokuWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SudokuWindow)
    {
        SudokuWindow->setWindowTitle(QCoreApplication::translate("SudokuWindow", "Sudoku", nullptr));
        resetButton->setText(QCoreApplication::translate("SudokuWindow", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SudokuWindow: public Ui_SudokuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOKUWINDOW_H
