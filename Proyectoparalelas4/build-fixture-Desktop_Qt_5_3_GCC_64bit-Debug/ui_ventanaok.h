/********************************************************************************
** Form generated from reading UI file 'ventanaok.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANAOK_H
#define UI_VENTANAOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ventanaok
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_2;

    void setupUi(QDialog *ventanaok)
    {
        if (ventanaok->objectName().isEmpty())
            ventanaok->setObjectName(QStringLiteral("ventanaok"));
        ventanaok->resize(424, 127);
        buttonBox = new QDialogButtonBox(ventanaok);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(100, 80, 201, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_2 = new QLabel(ventanaok);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 30, 531, 51));

        retranslateUi(ventanaok);
        QObject::connect(buttonBox, SIGNAL(accepted()), ventanaok, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ventanaok, SLOT(reject()));

        QMetaObject::connectSlotsByName(ventanaok);
    } // setupUi

    void retranslateUi(QDialog *ventanaok)
    {
        ventanaok->setWindowTitle(QApplication::translate("ventanaok", "Dialog", 0));
        label_2->setText(QApplication::translate("ventanaok", "\302\241Ha salido bien!, ya pudes ver la distribucion de partidos.", 0));
    } // retranslateUi

};

namespace Ui {
    class ventanaok: public Ui_ventanaok {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANAOK_H
