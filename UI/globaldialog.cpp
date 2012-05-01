#include <QtGui>
#include "globaldialog.h"

GlobalDialog::GlobalDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	QRegExp regExp("[a-zA-Z][a-zA-Z0-9]*(,[a-zA-Z][a-zA-Z0-9]*)*");
	//Asigan expresiones regulares a los elementos para
	//Que solo entren caracteres validos
	globalInt->setValidator(new QRegExpValidator(regExp,this));
	globalFloat->setValidator(new QRegExpValidator(regExp,this));
	globalString->setValidator(new QRegExpValidator(regExp,this));
	//Pone el boton como deshabilitado
	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}
