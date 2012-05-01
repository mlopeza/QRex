#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

#include <QDialog>
#include "ui_function.h"

class FunctionDialog: public QDialog, public Ui::FunctionDialog{
	Q_OBJECT

	public:
		FunctionDialog(QWidget *parent=0);
	signals:
		void changed_toMain(FunctionDialog *);
		void changed_Object();
	private slots:
		void on_functionName_textChanged();
		void on_typeComboBox_currentIndexChanged();
		void on_functionParameters_textChanged();
};
#endif
