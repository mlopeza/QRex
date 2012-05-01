#ifndef IODIALOG_H
#define IONDIALOG_H

#include <QDialog>
#include "ui_io.h"

class IODialog: public QDialog, public Ui::IODialog{
	Q_OBJECT

	public:
		IODialog(QWidget *parent=0);

	private slots:
		void on_IOText_textChanged();
};
#endif
