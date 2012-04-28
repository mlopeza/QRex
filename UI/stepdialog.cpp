#include <QtGui>
#include "stepdialog.h"

StepDialog::StepDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	//Pone el boton como deshabilitado
	QPushButton *okButton=buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(false);

	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

//Si el nombre de la Funcion Tiene un INPUT aceptable habilita el boton de ok
void StepDialog::on_stepText_textChanged(){
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(true);
}

