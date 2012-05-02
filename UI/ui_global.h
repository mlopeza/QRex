/********************************************************************************
** Form generated from reading UI file 'global.ui'
**
** Created: Tue May 1 23:36:46 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLOBAL_H
#define UI_GLOBAL_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_GlobalDialog
{
public:
    QFormLayout *formLayout;
    QLabel *labelFunction;
    QLabel *labelParameters;
    QDialogButtonBox *buttonBox;
    QLineEdit *globalFloat;
    QLineEdit *globalString;
    QLineEdit *globalInt;
    QLabel *labelType;

    void setupUi(QDialog *GlobalDialog)
    {
        if (GlobalDialog->objectName().isEmpty())
            GlobalDialog->setObjectName(QString::fromUtf8("GlobalDialog"));
        GlobalDialog->resize(500, 168);
        GlobalDialog->setMinimumSize(QSize(470, 168));
        GlobalDialog->setMaximumSize(QSize(16777215, 168));
        GlobalDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        formLayout = new QFormLayout(GlobalDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelFunction = new QLabel(GlobalDialog);
        labelFunction->setObjectName(QString::fromUtf8("labelFunction"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelFunction->sizePolicy().hasHeightForWidth());
        labelFunction->setSizePolicy(sizePolicy);
        labelFunction->setMaximumSize(QSize(100, 17));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelFunction);

        labelParameters = new QLabel(GlobalDialog);
        labelParameters->setObjectName(QString::fromUtf8("labelParameters"));
        labelParameters->setMaximumSize(QSize(120, 17));

        formLayout->setWidget(5, QFormLayout::LabelRole, labelParameters);

        buttonBox = new QDialogButtonBox(GlobalDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        formLayout->setWidget(7, QFormLayout::FieldRole, buttonBox);

        globalFloat = new QLineEdit(GlobalDialog);
        globalFloat->setObjectName(QString::fromUtf8("globalFloat"));
        globalFloat->setMinimumSize(QSize(200, 0));
        globalFloat->setMaximumSize(QSize(16777215, 16777215));
        globalFloat->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(2, QFormLayout::FieldRole, globalFloat);

        globalString = new QLineEdit(GlobalDialog);
        globalString->setObjectName(QString::fromUtf8("globalString"));
        globalString->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(5, QFormLayout::FieldRole, globalString);

        globalInt = new QLineEdit(GlobalDialog);
        globalInt->setObjectName(QString::fromUtf8("globalInt"));

        formLayout->setWidget(0, QFormLayout::FieldRole, globalInt);

        labelType = new QLabel(GlobalDialog);
        labelType->setObjectName(QString::fromUtf8("labelType"));
        labelType->setMaximumSize(QSize(100, 17));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelType);


        retranslateUi(GlobalDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GlobalDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GlobalDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GlobalDialog);
    } // setupUi

    void retranslateUi(QDialog *GlobalDialog)
    {
        GlobalDialog->setWindowTitle(QApplication::translate("GlobalDialog", "Global Variables", 0, QApplication::UnicodeUTF8));
        labelFunction->setText(QApplication::translate("GlobalDialog", "global float", 0, QApplication::UnicodeUTF8));
        labelParameters->setText(QApplication::translate("GlobalDialog", "global string", 0, QApplication::UnicodeUTF8));
        labelType->setText(QApplication::translate("GlobalDialog", "global int", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GlobalDialog: public Ui_GlobalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLOBAL_H
