/********************************************************************************
** Form generated from reading UI file 'io.ui'
**
** Created: Sat Apr 28 17:19:35 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IO_H
#define UI_IO_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_IODialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *ioComboBox;
    QLineEdit *IOText;

    void setupUi(QDialog *IODialog)
    {
        if (IODialog->objectName().isEmpty())
            IODialog->setObjectName(QString::fromUtf8("IODialog"));
        IODialog->resize(500, 126);
        IODialog->setMinimumSize(QSize(500, 126));
        IODialog->setMaximumSize(QSize(16777215, 126));
        IODialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(IODialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(IODialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 7, 0, 1, 2);

        label = new QLabel(IODialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(IODialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ioComboBox = new QComboBox(IODialog);
        ioComboBox->setObjectName(QString::fromUtf8("ioComboBox"));
        ioComboBox->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(ioComboBox);

        IOText = new QLineEdit(IODialog);
        IOText->setObjectName(QString::fromUtf8("IOText"));
        IOText->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(IOText);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(IODialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), IODialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IODialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(IODialog);
    } // setupUi

    void retranslateUi(QDialog *IODialog)
    {
        IODialog->setWindowTitle(QApplication::translate("IODialog", "Input/Output", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IODialog", "INPUT:  Write the ID of the Variable", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IODialog", "OUTPUT: Write values separated by commas (ID,STRING,CONSTANT)", 0, QApplication::UnicodeUTF8));
        ioComboBox->clear();
        ioComboBox->insertItems(0, QStringList()
         << QApplication::translate("IODialog", "Input", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IODialog", "Output", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class IODialog: public Ui_IODialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IO_H
