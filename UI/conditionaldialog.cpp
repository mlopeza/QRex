#include <QtGui>
#include "conditionaldialog.h"

ConditionalDialog::ConditionalDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	//QRegExp regExp(".*[a-zA-Z][a-zA-Z0-9]*.*[>|<|!=|==|<=|>=].*[a-zA-Z][a-zA-Z0-9]*.*");
	QRegExp regExp(".*");

	conditionText->setValidator(new QRegExpValidator(regExp,this));

	//Pone el boton como deshabilitado
	QPushButton *okButton=buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(false);

	connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

//Si el nombre de la Funcion Tiene un INPUT aceptable habilita el boton de ok
void ConditionalDialog::on_conditionText_textChanged(){
	(buttonBox->button(QDialogButtonBox::Ok))->setEnabled(conditionText->hasAcceptableInput());
}

