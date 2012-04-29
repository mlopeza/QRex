#include <QtGui>
#include "iodialog.h"

IODialog::IODialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	//QRegExp regExp("[:blank:]*[a-zA-Z][a-zA-Z0-9]*[:blank:]*");
	//QRegExp regExp("(.*-[,])(,(.*-[,]))*");
	QRegExp regExp(".*");

	IOText->setValidator(new QRegExpValidator(regExp,this));

	//Pone el boton como deshabilitado
	QPushButton *okButton=buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(false);

	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

//Si el nombre de la Funcion Tiene un INPUT aceptable habilita el boton de ok
void IODialog::on_IOText_textChanged(){
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(IOText->hasAcceptableInput());
}


