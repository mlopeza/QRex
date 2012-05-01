/********************************************************************************
** Form generated from reading UI file 'conditional.ui'
**
** Created: Mon Apr 30 22:10:25 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDITIONAL_H
#define UI_CONDITIONAL_H

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

class Ui_ConditionalDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *conditionLabel;
    QLineEdit *conditionText;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ConditionalDialog)
    {
        if (ConditionalDialog->objectName().isEmpty())
            ConditionalDialog->setObjectName(QString::fromUtf8("ConditionalDialog"));
        ConditionalDialog->resize(396, 130);
        ConditionalDialog->setMinimumSize(QSize(0, 130));
        ConditionalDialog->setMaximumSize(QSize(16777215, 130));
        ConditionalDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(ConditionalDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        conditionLabel = new QLabel(ConditionalDialog);
        conditionLabel->setObjectName(QString::fromUtf8("conditionLabel"));
        conditionLabel->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(conditionLabel);

        conditionText = new QLineEdit(ConditionalDialog);
        conditionText->setObjectName(QString::fromUtf8("conditionText"));
        conditionText->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(conditionText);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ConditionalDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(ConditionalDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConditionalDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConditionalDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConditionalDialog);
    } // setupUi

    void retranslateUi(QDialog *ConditionalDialog)
    {
        ConditionalDialog->setWindowTitle(QApplication::translate("ConditionalDialog", "Condition", 0, QApplication::UnicodeUTF8));
        conditionLabel->setText(QApplication::translate("ConditionalDialog", "Condition:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConditionalDialog: public Ui_ConditionalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDITIONAL_H
