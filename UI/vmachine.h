#ifndef VMACHINE_H
#define VMACHINE_H
#define _MAS 0
#define _MENOS 1
#define _POR 2
#define _DIVISION 3
#define _MODULO 4
#define _MAYOR 5
#define _MENOR 6
#define _DIFERENTE 7
#define _IGUAL 8
#define _MAYQUE 9
#define _MENQUE 10
#define _AND 11
#define _OR 12
#define _ASIGNA 13
#define _NOT 14
#define _NEGATIVO 15
#define _GOTOF 18
#define _GOTOV 19
#define _PRINT 20
#define _GOTO 21
#define _IFF 22
#define _READ 24
#define _ERA 25
#define _PARAM 26
#define _GOSUB 27
#define _RETORNO 28
#define _RETURN 29
#define _FIN 30

#define _PROCINT 4000
#define _PROCFLOAT 6000
#define _PROCSTRING 8000
#define _GLOBAL_INT      10000
#define _GLOBAL_FLOAT    12000
#define _GLOBAL_STRING   14000
#define _CONSTANT_INT    16000
#define _CONSTANT_FLOAT  18000
#define _CONSTANT_STRING 20000
#define _TEMP_INT 22000
#define _TEMP_FLOAT 23000
#define _TEMP_STRING 24000

#define _FLOTANTE 1
#define _CADENA 2
#define _ENTERO 3
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include "vmdatastruct.h"
#include "virtualmachine.h"
class VMachine{

	public:
		//Constructor del objeto
		VMachine(QString archive,VMDialog *d);
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
		//Funciones en La Maquina Virtual
		void Operacion(Quadruple *,int operacion);
		//Regresa el tipo de variable segun su direccion
		int tipoVariable(int direccion);

		//Regresa el valor entero de la variable
		int getInteger(int address);
		QString dameVariable(int address);
		//Asigna la variable
		void asignaVariable(int address,QString valor);

		//Imprime un Quadruplo para Debug
		void printQuadruple(Quadruple *q);

		//Archivo del cual se va a Leer
		QString archive;

		//Memoria Global y de Constantes
		Memory *GlobalMemory;

		//Cuadruplos
		std::map<int,Quadruple *> Quadruples;	

		//Salida a pantalla de ejecucion
		VMDialog *dialog;
		

		Memory *actualMemory;
		Pila *memStack;

};

#endif
