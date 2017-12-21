/********************************************************************************
** Form generated from reading UI file 'ventanaerror.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANAERROR_H
#define UI_VENTANAERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ventanaerror
{
public:
    QLabel *label_2;
    QPushButton *btnok;

    void setupUi(QDialog *ventanaerror)
    {
        if (ventanaerror->objectName().isEmpty())
            ventanaerror->setObjectName(QStringLiteral("ventanaerror"));
        ventanaerror->resize(402, 105);
        label_2 = new QLabel(ventanaerror);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 40, 431, 16));
        btnok = new QPushButton(ventanaerror);
        btnok->setObjectName(QStringLiteral("btnok"));
        btnok->setGeometry(QRect(150, 70, 80, 22));

        retranslateUi(ventanaerror);
        QObject::connect(btnok, SIGNAL(clicked()), ventanaerror, SLOT(close()));

        QMetaObject::connectSlotsByName(ventanaerror);
    } // setupUi

    void retranslateUi(QDialog *ventanaerror)
    {
        ventanaerror->setWindowTitle(QApplication::translate("ventanaerror", "Dialog", 0));
        label_2->setText(QApplication::translate("ventanaerror", "\302\241Lo sentimos!, no se ha podido procesar el archivo", 0));
        btnok->setText(QApplication::translate("ventanaerror", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class ventanaerror: public Ui_ventanaerror {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANAERROR_H
