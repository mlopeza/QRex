#include <QtGui>
#include "functiondialog.h"

FunctionDialog::FunctionDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	QRegExp regExp("(int|float) [a-zA-Z][a-zA-Z0-9]*(,(int|float) [a-zA-Z][a-zA-Z0-9]*)*");
	QRegExp regExp2("[a-zA-Z][a-zA-Z0-9]*");
	functionParameters->setValidator(new QRegExpValidator(regExp,this));
	functionName->setValidator(new QRegExpValidator(regExp2,this));
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(false);
	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

//Si el nombre de la Funcion Tiene un INPUT aceptable habilita el boton de ok
void FunctionDialog::on_functionName_textChanged(){
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(functionName->hasAcceptableInput());
}

void FunctionDialog::on_functionParameters_textChanged(){
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(functionParameters->hasAcceptableInput());
}
void FunctionDialog::on_typeComboBox_currentIndexChanged(){
	if(typeComboBox->currentText() != "main"){
		//Habilita entradas de texto
		functionName->setEnabled(true);
		functionParameters->setEnabled(true);
		emit changed_Object();
	}else{
		//Deshabilita las entradas de texto
		functionName->setEnabled(false);
		functionParameters->setEnabled(false);
		(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(true);

		//Se avisa que se cambio a main
		emit changed_toMain(this);
	}
	
}
