/********************************************************************************
** Form generated from reading UI file 'function.ui'
**
** Created: Sat Apr 28 23:59:45 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTION_H
#define UI_FUNCTION_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_FunctionDialog
{
public:
    QFormLayout *formLayout;
    QLabel *labelType;
    QComboBox *typeComboBox;
    QLabel *labelFunction;
    QLabel *labelParameters;
    QDialogButtonBox *buttonBox;
    QLineEdit *functionName;
    QLineEdit *functionParameters;

    void setupUi(QDialog *FunctionDialog)
    {
        if (FunctionDialog->objectName().isEmpty())
            FunctionDialog->setObjectName(QString::fromUtf8("FunctionDialog"));
        FunctionDialog->resize(500, 162);
        FunctionDialog->setMinimumSize(QSize(470, 150));
        FunctionDialog->setMaximumSize(QSize(16777215, 162));
        formLayout = new QFormLayout(FunctionDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelType = new QLabel(FunctionDialog);
        labelType->setObjectName(QString::fromUtf8("labelType"));
        labelType->setMaximumSize(QSize(60, 17));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelType);

        typeComboBox = new QComboBox(FunctionDialog);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(typeComboBox->sizePolicy().hasHeightForWidth());
        typeComboBox->setSizePolicy(sizePolicy);
        typeComboBox->setMaximumSize(QSize(60, 16777215));
        typeComboBox->setBaseSize(QSize(0, 0));
        typeComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(0, QFormLayout::FieldRole, typeComboBox);

        labelFunction = new QLabel(FunctionDialog);
        labelFunction->setObjectName(QString::fromUtf8("labelFunction"));
        sizePolicy.setHeightForWidth(labelFunction->sizePolicy().hasHeightForWidth());
        labelFunction->setSizePolicy(sizePolicy);
        labelFunction->setMaximumSize(QSize(50, 17));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelFunction);

        labelParameters = new QLabel(FunctionDialog);
        labelParameters->setObjectName(QString::fromUtf8("labelParameters"));
        labelParameters->setMaximumSize(QSize(16777215, 17));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelParameters);

        buttonBox = new QDialogButtonBox(FunctionDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(6, QFormLayout::FieldRole, buttonBox);

        functionName = new QLineEdit(FunctionDialog);
        functionName->setObjectName(QString::fromUtf8("functionName"));
        functionName->setMinimumSize(QSize(200, 0));
        functionName->setMaximumSize(QSize(200, 16777215));
        functionName->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(1, QFormLayout::FieldRole, functionName);

        functionParameters = new QLineEdit(FunctionDialog);
        functionParameters->setObjectName(QString::fromUtf8("functionParameters"));
        functionParameters->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(4, QFormLayout::FieldRole, functionParameters);


        retranslateUi(FunctionDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FunctionDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FunctionDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FunctionDialog);
    } // setupUi

    void retranslateUi(QDialog *FunctionDialog)
    {
        FunctionDialog->setWindowTitle(QApplication::translate("FunctionDialog", "Function Definition", 0, QApplication::UnicodeUTF8));
        labelType->setText(QApplication::translate("FunctionDialog", "Type", 0, QApplication::UnicodeUTF8));
        typeComboBox->clear();
        typeComboBox->insertItems(0, QStringList()
         << QApplication::translate("FunctionDialog", "void", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FunctionDialog", "int", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FunctionDialog", "float", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FunctionDialog", "main", 0, QApplication::UnicodeUTF8)
        );
        labelFunction->setText(QApplication::translate("FunctionDialog", "Name", 0, QApplication::UnicodeUTF8));
        labelParameters->setText(QApplication::translate("FunctionDialog", "Parameters", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FunctionDialog: public Ui_FunctionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTION_H
