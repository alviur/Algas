/********************************************************************************
** Form generated from reading UI file 'algas.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGAS_H
#define UI_ALGAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Algas
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Algas)
    {
        if (Algas->objectName().isEmpty())
            Algas->setObjectName(QStringLiteral("Algas"));
        Algas->resize(1049, 621);
        centralWidget = new QWidget(Algas);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 541, 361));
        label->setFrameShape(QFrame::WinPanel);
        label->setScaledContents(true);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 450, 99, 27));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(310, 450, 99, 27));
        Algas->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Algas);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1049, 25));
        Algas->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Algas);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Algas->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Algas);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Algas->setStatusBar(statusBar);

        retranslateUi(Algas);

        QMetaObject::connectSlotsByName(Algas);
    } // setupUi

    void retranslateUi(QMainWindow *Algas)
    {
        Algas->setWindowTitle(QApplication::translate("Algas", "Algas", 0));
        label->setText(QString());
        pushButton->setText(QApplication::translate("Algas", "Cargar", 0));
        pushButton_2->setText(QApplication::translate("Algas", "Procesar", 0));
    } // retranslateUi

};

namespace Ui {
    class Algas: public Ui_Algas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGAS_H
