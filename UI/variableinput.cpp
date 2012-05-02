#include <QtGui>
#include "variableinput.h"

VariableInput::VariableInput(QWidget *parent,int type):QDialog(parent){
	setupUi(this);
	QRegExp	 regExp;
	//Flotante
	if(type==1){regExp=QRegExp("(-|)[0-9]+(.[0-9]+|)");}
	
	//Cadena
	if(type==2){regExp=QRegExp(".*");}
	
	//Entero
	if(type==3){regExp=QRegExp("(-|)[1-9][0-9]*");}
	
	inputLine->setValidator(new QRegExpValidator(regExp,this));

	//Pone el boton como deshabilitado
	QPushButton *okButton=buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(false);

	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

//Si el nombre de la Funcion Tiene un INPUT aceptable habilita el boton de ok
void VariableInput::on_inputLine_textChanged(){
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(inputLine->hasAcceptableInput());
}

