/********************************************************************************
** Form generated from reading UI file 'step.ui'
**
** Created: Mon Apr 30 22:10:25 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STEP_H
#define UI_STEP_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_StepDialog
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *stepText;
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *StepDialog)
    {
        if (StepDialog->objectName().isEmpty())
            StepDialog->setObjectName(QString::fromUtf8("StepDialog"));
        StepDialog->resize(504, 334);
        StepDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(StepDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stepText = new QPlainTextEdit(StepDialog);
        stepText->setObjectName(QString::fromUtf8("stepText"));

        gridLayout->addWidget(stepText, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(StepDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        label = new QLabel(StepDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(StepDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StepDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StepDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StepDialog);
    } // setupUi

    void retranslateUi(QDialog *StepDialog)
    {
        StepDialog->setWindowTitle(QApplication::translate("StepDialog", "Process", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StepDialog", "Put your code in here:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StepDialog: public Ui_StepDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEP_H
