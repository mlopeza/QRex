#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

#include <QDialog>
#include "ui_function.h"

class FunctionDialog: public QDialog, public Ui::FunctionDialog{
	Q_OBJECT

	public:
		FunctionDialog(QWidget *parent=0);

	private slots:
		void on_functionName_textChanged();
};
#endif
