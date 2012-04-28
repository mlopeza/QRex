#include <QtGui>
#include "functiondialog.h"

FunctionDialog::FunctionDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	QRegExp regExp("[A-Za-z]*");
	functionName->setValidator(new QRegExpValidator(regExp,this));

	//Pone el boton como deshabilitado
	QPushButton *okButton=buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(false);

	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

//Si el nombre de la Funcion Tiene un INPUT aceptable habilita el boton de ok
void FunctionDialog::on_functionName_textChanged(){
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(functionName->hasAcceptableInput());
}


