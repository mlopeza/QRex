#ifndef GLOBALVARDIALOG_H
#define GLOBALVARDIALOG_H

#include <QDialog>
#include "ui_global.h"

class GlobalDialog: public QDialog, public Ui::GlobalDialog{
	Q_OBJECT

	public:
		GlobalDialog(QWidget *parent=0);
};
#endif
