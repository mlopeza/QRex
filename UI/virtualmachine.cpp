#include <QtGui>
#include "virtualmachine.h"

VMDialog::VMDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	//Pone el boton como deshabilitado
	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
//	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}
