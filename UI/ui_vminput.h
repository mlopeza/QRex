/********************************************************************************
** Form generated from reading UI file 'vminput.ui'
**
** Created: Tue May 1 19:55:12 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VMINPUT_H
#define UI_VMINPUT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_InputDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QLabel *inputLabel;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputText;

    void setupUi(QDialog *InputDialog)
    {
        if (InputDialog->objectName().isEmpty())
            InputDialog->setObjectName(QString::fromUtf8("InputDialog"));
        InputDialog->resize(500, 126);
        InputDialog->setMinimumSize(QSize(500, 126));
        InputDialog->setMaximumSize(QSize(16777215, 126));
        InputDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(InputDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(InputDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 2);

        inputLabel = new QLabel(InputDialog);
        inputLabel->setObjectName(QString::fromUtf8("inputLabel"));

        gridLayout->addWidget(inputLabel, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        inputText = new QLineEdit(InputDialog);
        inputText->setObjectName(QString::fromUtf8("inputText"));
        inputText->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(inputText);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(InputDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), InputDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputDialog);
    } // setupUi

    void retranslateUi(QDialog *InputDialog)
    {
        InputDialog->setWindowTitle(QApplication::translate("InputDialog", "Input", 0, QApplication::UnicodeUTF8));
        inputLabel->setText(QApplication::translate("InputDialog", "Request for input", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InputDialog: public Ui_InputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VMINPUT_H
