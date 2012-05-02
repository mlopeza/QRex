#include <QDebug>
#include <QtGui>
#include "vmachine.h"
#include <QStringList>
#include <map> //Para el uso de la tabla de hash
#include <utility>


//Constructor de la clase
VMachine::VMachine(QString a, VMDialog *d)
{
	//Asigna la Direccion del archivo
	archive = a;
	dialog = d;

	//Memoriaactual
	actualMemory = new Memory();
	//Memoria Global
	GlobalMemory = new Memory();

	//Pila de memoria
	memStack = new Pila();
}

//Lectura de Datos
void VMachine::ExecuteCode()
{
	QFile file(archive);

	//Abre el archivo
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
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

	//Debug
	//dumpMemory();

	
	qDebug()<<"\n\n\n\n\n\n\n\n\n\n=======================Empieza Ejecucion";
	//Empieza la ejecucion
	GlobalMemory->print();
	start();

	//Cierra el archivo
	file.close();
}

void VMachine::readGlobals(QTextStream *in){
	//Linea para leer
	QString line;
	//Define si se realizo de forma correcta la transformacion
	bool ok;
	int dir;
	
	line=(in->readLine()).simplified();
	qDebug()<<line;
	while( !in->atEnd() &&  (QString::compare(line,";;",Qt::CaseSensitive))!=0) {
		dir=line.toInt(&ok,10);
		qDebug()<<dir;
		if(ok==false && dir==0){
			qDebug() <<"Fallo de conversion readGlobals"<<line;
		}else{
			//Inserta el elemento
			QString a("0");
			GlobalMemory->setVar(dir,a);
		}
		line=(in->readLine()).simplified();
		qDebug()<<line;
	}
	qDebug()<<"Finished Globals";
}

void VMachine::readConstants(QTextStream *in){
	//Linea para leer
	QString line;
	//Define si se realizo de forma correcta la transformacion
	bool ok;
	int dir;

	line=(in->readLine()).simplified();
	qDebug()<<line;
	while( !in->atEnd() && (QString::compare(line, "..",Qt::CaseSensitive))!=0) {
		//Separa la linea
		QStringList fields=line.split(",");
		
		//Conversion
		dir=(fields.takeFirst()).toInt(&ok,10);
		if(ok==false && dir==0){
			qDebug() <<"Fallo de conversion readConstants:"<<dir<<","<<fields.takeFirst();
		}else{
			//Inserta el elemento
			QString x =fields.takeFirst();
			qDebug()<<"SET VAR>>"<<dir<<">>"<<x;
			GlobalMemory->setVar(dir,x);
		}

     		line = (in->readLine()).simplified();
		qDebug()<<line;
	}
	qDebug()<<"Finished Constants";
}

void VMachine::readQuadruples(QTextStream *in){
	//Linea para leer
	QString line;
	//Define si se realizo de forma correcta la transformacion
	bool ok;
	int dir;
	Quadruple *x;
	int numeroCuadruplo=0;
	line = (in->readLine()).simplified();//Primer separador
	qDebug()<<line;
	while( !in->atEnd() && (QString::compare(line, "--",Qt::CaseSensitive))!=0){
		x = new Quadruple();
		//Separa la linea
		QStringList fields=line.split(",");
		
		for(int i=0;i<4;i++){
		//Conversion
			dir=(fields.takeFirst()).toInt(&ok,10);
			if(ok==false && dir==0){
				qDebug() <<"Fallo de conversion:readQuadruples"<<dir<<","<<fields.last();
			}else{
				//Agrega el Quadruplo
				x->setQ(i,dir);
			}
		}
	
		Quadruples.insert(std::make_pair(numeroCuadruplo,x));
		numeroCuadruplo++;

     		line = (in->readLine()).simplified();
		qDebug()<<line;
	}
	qDebug()<<"FinishedQuadruples()";
}

void VMachine::start(){
	int cont=0;
	int a;
	int p=0;
	int wow = 0;
	QStringList elements;
	qDebug() << "Start Execution!";
	std::map<int,Quadruple *>::iterator it = Quadruples.find(cont);
	while(it->second->getQ(0)!= _FIN){
		p++;
		//printQuadruple(it->second);
		switch(it->second->getQ(0)){
			case _MAS:
				qDebug()<<"MAS";
				Operacion(it->second,_MAS);cont++;
				break;
			case _MENOS:
				qDebug()<<"MENOS";
				Operacion(it->second,_MENOS);cont++;
				break;
			case _POR:
				qDebug()<<"POR";
				Operacion(it->second,_POR);cont++;
				break;
			case _DIVISION:
				qDebug()<<"DIVISION";
				Operacion(it->second,_DIVISION);cont++;
				break;
			case _MODULO:
				qDebug()<<"MODULO";
				Operacion(it->second,_MODULO);cont++;
				break;
			case _MAYOR:
				qDebug()<<"MAYOR";
				Operacion(it->second,_MAYOR);cont++;
				break;
			case _MENOR:
				qDebug()<<"MENOR";
				Operacion(it->second,_MENOR);cont++;
				break;
			case _DIFERENTE:
				qDebug()<<"DIFERENTE";
				Operacion(it->second,_DIFERENTE);cont++;
				break;
			case _IGUAL:
				qDebug()<<"IGUAL";
				Operacion(it->second,_IGUAL);cont++;
				break;
			case _MAYQUE:
				qDebug()<<"MAYQUE";
				Operacion(it->second,_MAYQUE);cont++;
				break;
			case _MENQUE:
				qDebug()<<"MENQUE";
				Operacion(it->second,_MENQUE);cont++;
				break;
			case _AND:
				qDebug()<<"AND";
				Operacion(it->second,_AND);cont++;
				break;
			case _OR:
				qDebug()<<"OR";
				Operacion(it->second,_OR);cont++;
				break;
			case _ASIGNA:
				qDebug()<<"ASIGNA";
				Operacion(it->second,_ASIGNA);cont++;
				break;
			case _NOT:
				qDebug()<<"NOT";
				Operacion(it->second,_NOT);cont++;
				break;
			case _NEGATIVO:
				qDebug()<<"NEGATIVO";
				Operacion(it->second,_NEGATIVO);cont++;
				break;
			case _GOTOF:
				qDebug()<<"GOTOF"<<it->second->getQ(3);
				//Se fuerza el valor entero de la variable
				//Para hacer la evaluacion
				a = getInteger(it->second->getQ(1));
				if(a == 0){
					cont=it->second->getQ(3);
				}else{
					cont++;
				}
				break;
			case _GOTOV:
				qDebug()<<"GOTOV"<<it->second->getQ(3);
				a = getInteger(it->second->getQ(1));
				if(a != 0){
					cont=it->second->getQ(3);
				}else{
					cont++;
				}
				break;
			case _PRINT:
				qDebug()<<"PRINT";
				//Print Function
				//Limpieza del string y ejecucion de los saltos de linea
				linea = dameVariable(it->second->getQ(1)).remove(QChar('"'), Qt::CaseInsensitive);;
				wow=linea.count(QRegExp("\\\\n"));
				if(wow!=0){
					elements = linea.split("\\n");
					foreach(QString nl,elements){	
						dialog->mainOutput->insertPlainText(nl);
						dialog->mainOutput->insertPlainText("\n");
					}
				}else{
					dialog->mainOutput->insertPlainText(linea);
				}
				qDebug() <<"IMPRESION>>>>>>>>"<<it->second->getQ(1)<<">>>>"<< dameVariable(it->second->getQ(1));
				cont++;
				break;
			case _GOTO:
				qDebug()<<"GOTO"<<it->second->getQ(3);
				cont=it->second->getQ(3);
				break;
			case _READ:
				qDebug()<<"READ";
				vi = new VariableInput(dialog,tipoVariable(it->second->getQ(1)));
				if(vi->exec()){
					asignaVariable(it->second->getQ(1),vi->inputLine->text());
				}else{
					asignaVariable(it->second->getQ(1),"0");
				}
				delete vi;
				cont++;
				break;
			case _ERA:
				qDebug()<<"ERA";
				tempMemory = new Memory();
				cont++;
				break;
			case _PARAM:
				qDebug()<<"PARAM";
				tempMemory->setVar(it->second->getQ(3),dameVariable(it->second->getQ(1)));
				cont++;
				break;
			case _GOSUB:
				qDebug()<<"GOSUB";
				//Pone el retorno de linea
				tempMemory->setLine(cont+1);
				//Mete la memoria actual a la pila
				memStack->Push(actualMemory);
				//La memoria temporal se convierte en la actual
				actualMemory = tempMemory;
				tempMemory = NULL;
				//Salta a la linea
				cont=it->second->getQ(3);
				break;
			case _RETORNO:
				qDebug()<<"RETORNO";
				//Regreso a la ejecucion anterior
				//Saca la linea a la cual se va a regresar
				cont=actualMemory->getLine();
				//ELimina de la memoria el proceso terminado
				delete actualMemory;
				//Saca el proceso pendiente de la pila
				actualMemory = memStack->Pop();
				break;
			case _RETURN:
				qDebug()<<"RETURN";
				//La variable que va a regresar
				GlobalMemory->setVar(it->second->getQ(3),dameVariable(it->second->getQ(1)));
				cont++;
				break;
		}
	
		it = Quadruples.find(cont);

	}

	qDebug() << "Programa Terminado";
}

void VMachine::printQuadruple(Quadruple *q){
	qDebug()<<q->getQ(0)<<","
		<<q->getQ(1)<<","
		<<q->getQ(2)<<","
		<<q->getQ(3);

}

int VMachine::getInteger(int address){
	QString a;
	bool boo;
	return (int)(dameVariable(address)).toFloat(&boo);

}

int VMachine::tipoVariable(int direccion){
	/*Verifica de que tipo es una variable segun su dirección*/
	if(direccion == -1)
		return _ENTERO;
	if((direccion >= _PROCINT && direccion < _PROCFLOAT)
			|| (direccion >= _GLOBAL_INT && direccion < _GLOBAL_FLOAT)
			|| (direccion >= _CONSTANT_INT && direccion < _CONSTANT_FLOAT)
			|| (direccion >= _TEMP_INT && direccion < _TEMP_FLOAT) )
	{
		return _ENTERO;

	}else if((direccion >= _PROCFLOAT && direccion < _PROCSTRING)
			|| (direccion >= _GLOBAL_FLOAT && direccion < _GLOBAL_STRING)
			|| (direccion >= _CONSTANT_FLOAT && direccion < _CONSTANT_STRING)
			|| (direccion >= _TEMP_FLOAT && direccion < _TEMP_STRING) )
	{
		return _FLOTANTE;
	}

	return _CADENA;
}

void VMachine::Operacion(Quadruple *q,int operacion){
	int a = q->getQ(1);
	int b = q->getQ(2);
	int c = q->getQ(3);
	bool bo,bi;
	//Operaciones enteras
	int x=0;
	int xx=0;

	//Operaciones flotantes
	float y=0;
	float yy=0;
	int aa = tipoVariable(a);
	int bb = tipoVariable(b);
	int cc = tipoVariable(c);
	qDebug()<<"a:"<<aa<<"-"<<dameVariable(a);
	qDebug()<<"b:"<<bb<<"-"<<dameVariable(b);
	if(aa == _CADENA && cc == _CADENA && operacion == _ASIGNA){
		qDebug()<<"Es Cadena";
		asignaVariable(c,dameVariable(a));
	}else if(aa == _ENTERO && bb == _ENTERO){
		x=dameVariable(a).toInt(&bo,10);
		xx=dameVariable(b).toInt(&bi,10);
		if(!bo){qDebug()<<"Problemas con x";exit(-1);}
		if(!bi){qDebug()<<"Problemas con xx";exit(-1);}

		switch(operacion){
			case _MAS:
				x=x+xx;
				break;
			case _MENOS:
				x=x-xx;
				break;
			case _POR:
				x=x*xx;
				break;
			case _DIVISION:
				if(xx!=0){
					x=x/xx;
				}else{
					qDebug()<<"Divided by Zero";
				}
				break;
			case _MODULO:
				x=x%xx;
				break;
			case _MAYOR:
				x=(x>xx)?1:0;
				break;
			case _MENOR:
				x=(x<xx)?1:0;
				break;
			case _DIFERENTE:
				x=(x!=xx)?1:0;
				break;
			case _IGUAL:
				x=(x==xx)?1:0;
				break;
			case _MAYQUE:
				x=(x>=xx)?1:0;
				break;
			case _MENQUE:
				x=(x<=xx)?1:0;
				break;
			case _AND:
				x=(x && xx);
				break;
			case _OR:
				x=(x||xx);
				break;
			case _ASIGNA:
				//Se asignara X
				break;
			case _NOT:
				x=(!x);
				break;
			case _NEGATIVO:
				x=(-x);
				break;
		}
		QString value;
		//Impresion de la operacion
		if(cc == _FLOTANTE){
			asignaVariable(c,value.setNum((float)x));
		}else if(cc == _ENTERO){
			asignaVariable(c,value.setNum((int)x));
		}else{
			asignaVariable(c,value);
		}
	}else if( aa == _ENTERO && bb == _FLOTANTE){
		y=dameVariable(a).toInt(&bo,10);
		yy=dameVariable(b).toFloat(&bi);
		if(!bo){qDebug()<<"Problemas con y1";exit(-1);}
		if(!bi){qDebug()<<"Problemas con yy1";exit(-1);}

		switch(operacion){
			case _MAS:
				y=y+yy;
				break;
			case _MENOS:
				y=y-yy;
				break;
			case _POR:
				y=y*yy;
				break;
			case _DIVISION:
				if(yy!=0){
					y=y/yy;
				}else{
					qDebug()<<"Divided by Zero";
				}
				break;
			case _MAYOR:
				y=(y>yy)?1:0;
				break;
			case _MENOR:
				y=(y<yy)?1:0;
				break;
			case _DIFERENTE:
				y=(y!=yy)?1:0;
				break;
			case _IGUAL:
				y=(y==yy)?1:0;
				break;
			case _MAYQUE:
				y=(y>=yy)?1:0;
				break;
			case _MENQUE:
				y=(y>=yy)?1:0;
				break;
			case _AND:
				y=(y&&yy)?1:0;
				break;
			case _OR:
				y=(y||yy)?1:0;
				break;
			case _ASIGNA:
				//No se hace nada
				break;
			case _NOT:
				y=!y;
				break;
			case _NEGATIVO:
				y=-y;
				break;
		}
		QString value;
		//Impresion de la operacion
		if(cc == _FLOTANTE){
			asignaVariable(c,value.setNum((float)y));
		}else if(cc == _ENTERO){
			asignaVariable(c,value.setNum((int)y));
		}else{
			asignaVariable(c,value);
		}
	}else if(aa == _FLOTANTE && bb == _ENTERO){
		y=dameVariable(a).toFloat(&bo);
		yy=dameVariable(b).toInt(&bi,10);
		if(!bo){qDebug()<<"Problemas con y2";exit(-1);}
		if(!bi){qDebug()<<"Problemas con yy2";exit(-1);}
		switch(operacion){
			case _MAS:
				y=y+yy;
				break;
			case _MENOS:
				y=y-yy;
				break;
			case _POR:
				y=y*yy;
				break;
			case _DIVISION:
				if(yy !=0){
					y=y/yy;
				}else{
					qDebug()<<"Divided by 0";
				}
				break;
			case _MAYOR:
				y=(y>yy)?1:0;
				break;
			case _MENOR:
				y=(y<yy)?1:0;
				break;
			case _DIFERENTE:
				y=(y!=yy)?1:0;
				break;
			case _IGUAL:
				y=(y==yy)?1:0;
				break;
			case _MAYQUE:
				y=(y>=yy)?1:0;
				break;
			case _MENQUE:
				y=(y>=yy)?1:0;
				break;
			case _AND:
				y=(y&&yy)?1:0;
				break;
			case _OR:
				y=(y||yy)?1:0;
				break;
			case _ASIGNA:
				//No se hace nada
				break;
			case _NOT:
				y=!y;
				break;
			case _NEGATIVO:
				y=-y;
				break;
		}
		QString value;
		//Impresion de la operacion
		if(cc == _FLOTANTE){
			asignaVariable(c,value.setNum((float)y));
		}else if(cc == _ENTERO){
			asignaVariable(c,value.setNum((int)y));
		}else{
			asignaVariable(c,value);
		}
	}else if(aa == _FLOTANTE && bb == _FLOTANTE){
		y=dameVariable(a).toFloat(&bo);
		yy=dameVariable(b).toFloat(&bi);
		qDebug()<<y;
		qDebug()<<yy;
		if(!bo){qDebug()<<"Problemas con y3";exit(-1);}
		if(!bi){qDebug()<<"Problemas con yy3";exit(-1);}
		switch(operacion){
			case _MAS:
				y=y+yy;
				break;
			case _MENOS:
				y=y-yy;
				break;
			case _POR:
				y=y*yy;
				break;
			case _DIVISION:
				if(yy!=0){
					y=y/yy;
				}else{
					qDebug()<<"Divided by Zero";
				}
				break;
			case _MAYOR:
				y=(y>yy)?1:0;
				break;
			case _MENOR:
				y=(y<yy)?1:0;
				break;
			case _DIFERENTE:
				y=(y!=yy)?1:0;
				break;
			case _IGUAL:
				y=(y==yy)?1:0;
				break;
			case _MAYQUE:
				y=(y>=yy)?1:0;
				break;
			case _MENQUE:
				y=(y>=yy)?1:0;
				break;
			case _AND:
				y=(y&&yy)?1:0;
				break;
			case _OR:
				y=(y||yy)?1:0;
				break;
			case _ASIGNA:
				//No se hace nada
				break;
			case _NOT:
				y=!y;
				break;
			case _NEGATIVO:
				y=-y;
				break;
		}
		QString value;
		//Impresion de la operacion
		if(cc == _FLOTANTE){
			asignaVariable(c,value.setNum((float)y));
		}else if(cc == _ENTERO){
			asignaVariable(c,value.setNum((int)y));
		}else{
			asignaVariable(c,value);
		}
	}


}

//Regresa la variable dependiendo si es global o local
QString VMachine::dameVariable(int address){
	if(address >=10000 && address <22000){
		return GlobalMemory->getVar(address);
	}else{
		return actualMemory->getVar(address);
	}
}

//Regresa la variable dependiendo si es global o local
void VMachine::asignaVariable(int address,QString valor){
	if(address >=10000 && address <16000){
		GlobalMemory->setVar(address,valor);
	}else{
		actualMemory->setVar(address,valor);
	}
}
