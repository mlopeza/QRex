#ifndef VMACHINE_H
#define VMACHINE_H

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QString>
class VMachine{

	public:
		//Constructor del objeto
		VMachine(QString archive);
		~VMachine();		
		//Ejecuta el codigo
		void ExecuteCode();
	private:
		//Verifica la existencia de una variable
		bool checkExistence(int address);

		//Empieza la ejecucion de los cuadruplos
		void start();

		//devuelve el tipo de Variable
		int addressType(int);
		//Lee las variables Globales del archivo
		void readGlobals(QTextStream *in);
		//Lee las constantes del archivo
		void readConstants(QTextStream *in);
		//Lee los cuadruplos del archivo
		void readQuadruples(QTextStream *in);


		//Archivo del cual se va a Leer
		QString archive;
		//Aqui ira el Dialog de Ejecucion
		
};

#endif
