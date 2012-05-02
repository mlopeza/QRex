#ifndef STEPDIALOG_H
#define STEPDIALOG_H

#include <QDialog>
#include "ui_step.h"

class StepDialog: public QDialog, public Ui::StepDialog{
	Q_OBJECT

	public:
		StepDialog(QWidget *parent=0);

	private slots:
		void on_stepText_textChanged();
};
#endif
