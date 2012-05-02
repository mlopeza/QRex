#ifndef VARIABLEINPUT_H
#define VARIABLEINPUT_H

#include <QDialog>
#include "ui_variableinput.h"

class VariableInput: public QDialog, public Ui::VariableInput{
	Q_OBJECT

	public:
		VariableInput(QWidget *parent=0,int type=0);
	private slots:
		void on_inputLine_textChanged();
};
#endif
