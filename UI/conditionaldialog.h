#ifndef CONDITIONALDIALOG_H
#define CONDITIONALDIALOG_H

#include <QDialog>
#include "ui_conditional.h"

class ConditionalDialog: public QDialog, public Ui::ConditionalDialog{
	Q_OBJECT

	public:
		ConditionalDialog(QWidget *parent=0);

	private slots:
		void on_conditionText_textChanged();
};
#endif
