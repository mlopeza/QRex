#include <QDebug>
#include <QtGui>
#include "vmachine.h"

//Constructor de la clase
VMachine::VMachine(QString a)
{
	//Asigna la Direccion del archivo
	archive = a;
}

//Lectura de Datos
void VMachine::ExecuteCode()
{
	QFile file(archive);

	//Abre el archivo
	if(!file.open(QIODevice::ReadOnly)){
		qDebug()<<"Error Opening:"<<archive;
		return;
	}
	QTextStream in(&file);

	//Lee las globales
	readGlobals(&in);
	//Lee las constantes
	readConstants(&in);
	//Lee los cuadruplos
	readQuadruples(&in);

	//Empieza la ejecucion
	start();

	//Cierra el archivo
	file.close();
}

void VMachine::readGlobals(QTextStream *in){

}

void VMachine::readConstants(QTextStream *in){

}

void VMachine::readQuadruples(QTextStream *in){

}

void VMachine::start(){

}

