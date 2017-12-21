/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_2;
    QPushButton *btnsubir;
    QTreeView *treeView_2;
    QGroupBox *groupBox_3;
    QPushButton *btnelegir;
    QTreeView *treeView;
    QPushButton *btncerrar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(543, 401);
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 10, 491, 161));
        btnsubir = new QPushButton(groupBox_2);
        btnsubir->setObjectName(QStringLiteral("btnsubir"));
        btnsubir->setGeometry(QRect(200, 130, 111, 22));
        treeView_2 = new QTreeView(groupBox_2);
        treeView_2->setObjectName(QStringLiteral("treeView_2"));
        treeView_2->setGeometry(QRect(30, 30, 431, 91));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 180, 491, 171));
        btnelegir = new QPushButton(groupBox_3);
        btnelegir->setObjectName(QStringLiteral("btnelegir"));
        btnelegir->setGeometry(QRect(200, 130, 111, 22));
        treeView = new QTreeView(groupBox_3);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(30, 30, 431, 91));
        btncerrar = new QPushButton(centralWidget);
        btncerrar->setObjectName(QStringLiteral("btncerrar"));
        btncerrar->setGeometry(QRect(230, 350, 80, 22));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(btncerrar, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Distribucion de partidos", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "           Ingresar archivo tipo CSV con la informacion de los equipos", 0));
        btnsubir->setText(QApplication::translate("MainWindow", "Subir Archivo", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "                   Eliga el directorio donde dejar el archivo resultante", 0));
        btnelegir->setText(QApplication::translate("MainWindow", "Elegir", 0));
        btncerrar->setText(QApplication::translate("MainWindow", "Cerrar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
