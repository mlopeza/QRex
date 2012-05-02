/********************************************************************************
** Form generated from reading UI file 'variableinput.ui'
**
** Created: Tue May 1 21:31:35 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VARIABLEINPUT_H
#define UI_VARIABLEINPUT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_VariableInput
{
public:
    QGridLayout *gridLayout;
    QLineEdit *inputLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VariableInput)
    {
        if (VariableInput->objectName().isEmpty())
            VariableInput->setObjectName(QString::fromUtf8("VariableInput"));
        VariableInput->resize(300, 78);
        VariableInput->setMinimumSize(QSize(300, 78));
        VariableInput->setMaximumSize(QSize(300, 78));
        VariableInput->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(VariableInput);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        inputLine = new QLineEdit(VariableInput);
        inputLine->setObjectName(QString::fromUtf8("inputLine"));

        gridLayout->addWidget(inputLine, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(VariableInput);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(VariableInput);
        QObject::connect(buttonBox, SIGNAL(accepted()), VariableInput, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VariableInput, SLOT(reject()));

        QMetaObject::connectSlotsByName(VariableInput);
    } // setupUi

    void retranslateUi(QDialog *VariableInput)
    {
        VariableInput->setWindowTitle(QApplication::translate("VariableInput", "Variable Input", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VariableInput: public Ui_VariableInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VARIABLEINPUT_H
