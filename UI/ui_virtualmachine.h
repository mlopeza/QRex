/********************************************************************************
** Form generated from reading UI file 'virtualmachine.ui'
**
** Created: Tue May 1 05:01:57 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIRTUALMACHINE_H
#define UI_VIRTUALMACHINE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_VMDialog
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *mainOutput;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VMDialog)
    {
        if (VMDialog->objectName().isEmpty())
            VMDialog->setObjectName(QString::fromUtf8("VMDialog"));
        VMDialog->resize(600, 300);
        VMDialog->setMinimumSize(QSize(600, 300));
        VMDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(VMDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainOutput = new QPlainTextEdit(VMDialog);
        mainOutput->setObjectName(QString::fromUtf8("mainOutput"));
        mainOutput->setMinimumSize(QSize(0, 0));
        mainOutput->setAcceptDrops(false);
        mainOutput->setUndoRedoEnabled(false);
        mainOutput->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(mainOutput, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(VMDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(VMDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VMDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VMDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VMDialog);
    } // setupUi

    void retranslateUi(QDialog *VMDialog)
    {
        VMDialog->setWindowTitle(QApplication::translate("VMDialog", "QRex Virtual Machine", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VMDialog: public Ui_VMDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIRTUALMACHINE_H
