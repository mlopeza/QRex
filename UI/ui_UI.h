/********************************************************************************
** Form generated from reading UI file 'UI.ui'
**
** Created: Sun Apr 22 00:50:26 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_H
#define UI_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Exit;
    QAction *action_About;
    QAction *action_DeleteObject;
    QAction *action_AddLine;
    QAction *action_Point;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *startEnd;
    QPushButton *process;
    QPushButton *print;
    QPushButton *read;
    QPushButton *decision;
    QPushButton *whileButton;
    QTabWidget *function_tabs;
    QWidget *main;
    QGridLayout *gridLayout_2;
    QGraphicsView *maingraphicsView;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *terminal_out;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menu_Help;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1179, 607);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_DeleteObject = new QAction(MainWindow);
        action_DeleteObject->setObjectName(QString::fromUtf8("action_DeleteObject"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/delete.png"), QSize(), QIcon::Normal, QIcon::On);
        action_DeleteObject->setIcon(icon);
        action_AddLine = new QAction(MainWindow);
        action_AddLine->setObjectName(QString::fromUtf8("action_AddLine"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/linepointer.png"), QSize(), QIcon::Normal, QIcon::On);
        action_AddLine->setIcon(icon1);
        action_Point = new QAction(MainWindow);
        action_Point->setObjectName(QString::fromUtf8("action_Point"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Images/pointer.png"), QSize(), QIcon::Normal, QIcon::On);
        action_Point->setIcon(icon2);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        startEnd = new QPushButton(groupBox);
        startEnd->setObjectName(QString::fromUtf8("startEnd"));

        verticalLayout_2->addWidget(startEnd);

        process = new QPushButton(groupBox);
        process->setObjectName(QString::fromUtf8("process"));

        verticalLayout_2->addWidget(process);

        print = new QPushButton(groupBox);
        print->setObjectName(QString::fromUtf8("print"));

        verticalLayout_2->addWidget(print);

        read = new QPushButton(groupBox);
        read->setObjectName(QString::fromUtf8("read"));

        verticalLayout_2->addWidget(read);

        decision = new QPushButton(groupBox);
        decision->setObjectName(QString::fromUtf8("decision"));

        verticalLayout_2->addWidget(decision);

        whileButton = new QPushButton(groupBox);
        whileButton->setObjectName(QString::fromUtf8("whileButton"));

        verticalLayout_2->addWidget(whileButton);


        horizontalLayout->addWidget(groupBox);

        function_tabs = new QTabWidget(centralwidget);
        function_tabs->setObjectName(QString::fromUtf8("function_tabs"));
        function_tabs->setMinimumSize(QSize(700, 500));
        function_tabs->setMaximumSize(QSize(16777215, 16777215));
        main = new QWidget();
        main->setObjectName(QString::fromUtf8("main"));
        gridLayout_2 = new QGridLayout(main);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        maingraphicsView = new QGraphicsView(main);
        maingraphicsView->setObjectName(QString::fromUtf8("maingraphicsView"));

        gridLayout_2->addWidget(maingraphicsView, 0, 0, 1, 1);

        function_tabs->addTab(main, QString());

        horizontalLayout->addWidget(function_tabs);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        terminal_out = new QPlainTextEdit(centralwidget);
        terminal_out->setObjectName(QString::fromUtf8("terminal_out"));
        terminal_out->setMinimumSize(QSize(200, 0));
        terminal_out->setMaximumSize(QSize(200, 16777215));
        terminal_out->setUndoRedoEnabled(false);
        terminal_out->setReadOnly(true);

        verticalLayout->addWidget(terminal_out);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1179, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menuFile->addAction(action_Open);
        menuFile->addAction(action_Save);
        menuFile->addAction(action_Exit);
        menu_Help->addAction(action_About);
        toolBar->addAction(action_DeleteObject);
        toolBar->addAction(action_AddLine);
        toolBar->addAction(action_Point);

        retranslateUi(MainWindow);

        function_tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QRex", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", "&Save As", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        action_DeleteObject->setText(QApplication::translate("MainWindow", "&Delete Object", 0, QApplication::UnicodeUTF8));
        action_AddLine->setText(QApplication::translate("MainWindow", "&Add Connection", 0, QApplication::UnicodeUTF8));
        action_Point->setText(QApplication::translate("MainWindow", "Point", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "DIagram Elements", 0, QApplication::UnicodeUTF8));
        startEnd->setText(QApplication::translate("MainWindow", "Start/End", 0, QApplication::UnicodeUTF8));
        process->setText(QApplication::translate("MainWindow", "Process", 0, QApplication::UnicodeUTF8));
        print->setText(QApplication::translate("MainWindow", "Print", 0, QApplication::UnicodeUTF8));
        read->setText(QApplication::translate("MainWindow", "Read", 0, QApplication::UnicodeUTF8));
        decision->setText(QApplication::translate("MainWindow", "Decision", 0, QApplication::UnicodeUTF8));
        whileButton->setText(QApplication::translate("MainWindow", "While", 0, QApplication::UnicodeUTF8));
        function_tabs->setTabText(function_tabs->indexOf(main), QApplication::translate("MainWindow", "main", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_H
