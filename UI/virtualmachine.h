#ifndef VIRTUALMACHINEDIALOG_H
#define VIRTUALMACHINEDIALOG_H

#include <QDialog>
#include "ui_virtualmachine.h"

class VMDialog: public QDialog, public Ui::VMDialog{
	Q_OBJECT

	public:
		VMDialog(QWidget *parent=0);
};
#endif
