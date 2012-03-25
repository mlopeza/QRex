

#if !defined(QRex_COCO_PARSER_H__)
#define QRex_COCO_PARSER_H__

#include <iostream>
#include <string>
#include "TDV.h"
#include "wchar.h"

#define GLOBAL_INT 	10000
#define GLOBAL_FLOAT	12000
#define GLOBAL_STRING	14000

#define CONSTANT_INT	16000
#define CONSTANT_FLOAT	18000
#define CONSTANT_STRING 20000


#include "Scanner.h"

namespace QRex {


class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_id=1,
		_cte_string=2,
		_cte_float=3,
		_cte_int=4,
		_int=5,
		_float=6,
		_string=7,
		_if=8,
		_else=9,
		_print=10,
		_main=11,
		_read=12,
		_while=13,
		_void=14,
		_return=15,
		_global=16,
		_sign=17
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

int //operadores
	MAS,MENOS,POR,DIVISION,MODULO,MAYOR,MENOR,DIFERENTE,IGUAL,MAYQUE,MENQUE,AND,OR,NOT,ASIGNA,PIZQ,PDER,NEGATIVO;


	int //tipos
	tipovariable,enterov,flotantev,cadenav,errorv;
	int 
	tipofuncion,enterof,flotantef,voidf,errorf;

	int //tipos de objetos
	tipo,variable,funcion,llamada,undef,lectura,escritura,condicion,ciclo,regreso,funcionfirma;
	
	int //Manejo de expresiones
	expresion;

	int //Manejo de retornos
	retorno;
	
	int //Declaraciones Globales
	global;

	int //Declaracion de parametros en una funcion
	parametros;

	int //CHeca si es una firma o una funcion
	firma,definefunc,omiteCuerpo;

	/*Parte para codigos de operacion*/

	TablaDeVariables *tab;		
	FuncionX *f;
	Variable *v;
	FuncionX *ftemp;

	//Tabla de Variables globales y Constantes
	Contexto *tabconstantes;
	Contexto *tabglobales;

	std::wstring identificador;

	//Hash de Cuadruplos (Manejo de Cuadruplos)
	int contCuadruplos;
	std::map<int,Cuadruplo *> hashCuadruplos;

	//Pilas de Expresiones
	Pila *Poper;
	Pila *PilaO;
	Pila *PilaS;
	

	//Tabla de variables globales

	void InitDeclarations() {
		MAS=0;
		MENOS=1;
		POR=2;
		DIVISION=3;
		MODULO=4;
		MAYOR=5;
		MENOR=6;
		DIFERENTE=7;
		IGUAL=8;
		MAYQUE=9;
		MENQUE=10;
		AND=11;
		OR=12;
		NOT=13;
		ASIGNA=14;
		NEGATIVO = 15;
		PIZQ = 16;
		PDER = 17;
	
		//Hash de Cuadruplos (Manejo de Cuadruplos)
		contCuadruplos = 0;
		//std::map<int,Cuadruplo *> hashCuadruplos; Este maneja los cuadruplos

		//Pilas de Expresiones
		Poper = new Pila();
		PilaO = new Pila();
		PilaS = new Pila();


		//Inicializa la tabla de Variables
		tab = new TablaDeVariables();

		//Inicializa tabla de Constantes
		tabconstantes = new Contexto(CONSTANT_INT,CONSTANT_FLOAT,CONSTANT_STRING);
		
		//Inicializa tabla de globales
		tabglobales = new Contexto(GLOBAL_INT,GLOBAL_FLOAT,GLOBAL_STRING);

		//Inicializa la funcion
		f = new FuncionX();
		// Codigos de funciones y variables
		tipovariable=-1;enterov=11;flotantev=12;cadenav=13;errorv=14;

		tipofuncion=-1;enterof=21;flotantef=22;voidf=23;errorf=24;

		//Manejo de expresiones
		expresion = 0;

		//Manejo de retorno
		retorno = 0;

		//Declaraciones globales
		global = 0;

		//Declaracion de parametros
		parametros = 0;
	
		//Verificar si es una firma o la definicion de una funcion
		firma = 0;
		definefunc = 0;
		omiteCuerpo = 0;

		//Tipo de objetos
		variable = 0;
		funcion = 1;
		llamada = 3;
		lectura = 4;
		escritura = 5;
		condicion = 6;
		ciclo = 7;
		regreso = 8;
		funcionfirma = 9;
		undef = 10;

        int cubo[4][5][15] = {{{11,11,11,11,11,11,11,11,11,11,11,11,11,-666,11},{12,12,12,12,12,11,11,11,11,11,11,11,11,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,11,-666,}},
            {{12,12,12,12,12,11,11,11,11,11,11,-666,-666,-666,12},{12,12,12,12,12,11,11,11,11,11,11,-666,-666,-666,12},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,11,-666,}},
            {{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,13},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666}},
            {{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666},{-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666,-666}}
        };
		
	}

	void Err(wchar_t* msg) {
		errors->Error(la->line, la->col, msg);
	}


	//Esto se utiliza para registrar la funcion main en la tabla de funciones
	void registraMain(){
		std::map<std::wstring,FuncionX *>::iterator it = tab->fhash.find(L"main");
		if( it == tab->fhash.end() && identificador != f->nombre) {
		//Checa si hay una funcion antes de crear la funcion main
			if(f->nombre == std::wstring(L"")){
				f->nombre=std::wstring(L"main");
				f->tipo=voidf;
					
			}else{
			//Inserta la funcion  al hash y crea la funcion main
				tab->fhash.insert(std::make_pair(f->nombre,f));
				f = new FuncionX();
				f->nombre=std::wstring(L"main");
				f->tipo=voidf;
			}
		}else{
			Err(L"No puede haber dos funciones main()");
		}

	}

	/*Imprime todos los registros de Funciones
		La tabla de variables globales y la tabla de constantes
	*/
	void imprimeRegistros(){
		FuncionX *func;
		Variable *var;

		std::wcout<<L"\n\nTabla de Funciones y Variables\n";
		std::map<std::wstring,FuncionX *>::iterator it = tab->fhash.begin();
		while (it != tab->fhash.end()){
			func = it->second;
			std::wcout<<L" "<< func->tipo<< L" " << func->nombre << L'\n';
			
			//Imprime Parametros si los tiene.
			func->parametros->Print();
			
			std::wcout << L"intNum:"<< func->intNum << L" floatNum:";
			std::wcout << func->floatNum << L" stringNum:" << func->stringNum << L'\n';
	
			//Variables Dentro
			std::map<std::wstring,Variable *>::iterator it2 = func->vhash.begin();
			while(it2 != it->second->vhash.end()){
				var = it2->second;
				std::wcout << L"		nombre:" << var->nombre;
				std::wcout << L" tipo:" << var->tipo;
				std::wcout << L" direccion:" << var->direccion << L'\n';
	
				it2++;
			}
			
			it++;
			std::wcout << L"\n\n";
		}

		std::wcout<<L"Tabla de Variables Globales\n";
		std::map<std::wstring,Variable *>::iterator it2 = tabglobales->vhash.begin();
		while (it2 != tabglobales->vhash.end()){
			var = it2->second;
			std::wcout << L"	nombre:" << var->nombre;
			std::wcout << L" tipo:" << var->tipo;
			std::wcout << L" direccion:" << var->direccion << L'\n';
			it2++;
		}

		std::wcout<<L"Tabla de Variables Constantes\n";
		it2 = tabconstantes->vhash.begin();
		while (it2 != tabconstantes->vhash.end()){
			var = it2->second;
			std::wcout << L"	nombre:" << var->nombre;
			std::wcout << L" tipo:" << var->tipo;
			std::wcout << L" direccion:" << var->direccion << L'\n';
			it2++;
		}

	}

	//Registra las constantes encontradas en el programa
	void registraConstante(){
		std::map<std::wstring,Variable *>::iterator it = tabconstantes->vhash.find(identificador);
			if(it == tabconstantes->vhash.end()){
				v = new Variable();
				v->nombre = identificador;
				v->tipo = tipovariable;
				switch(tipovariable){
					case 11://entero
						v->direccion=tabconstantes->intNum;
						tabconstantes->intNum++;
						break;
					case 12://flotante
						v->direccion=tabconstantes->floatNum;
						tabconstantes->floatNum++;
						break;
					case 13://string
						v->direccion=tabconstantes->stringNum;
						tabconstantes->stringNum++;
						break;
				}
				//Se registra la constante
				tabconstantes->vhash.insert(std::make_pair(v->nombre,v));			
			}
	}

	//Agrega el parametro a la lista de la funcion
	void registraParametroFirma(){
			f->parametros->Append(tipovariable);
	}
	//Checa si efectivamente la firma es igual a la declaracion
	void verificaRegistroFuncion(){
		std::map<std::wstring,FuncionX *>::iterator it = tab->fhash.find(ftemp->nombre);
		if(it == tab->fhash.end()){
			std::wcout <<L"("<< ftemp->nombre<<L")";
			Err(L"Function signtarue not declared.");
			delete(ftemp);
			omiteCuerpo = 1;
		}else if(it->second->tipo != ftemp->tipo){
			std::wcout <<L"("<< ftemp->nombre<<L")";
			Err(L"Signature return type mismatch.");
			delete(ftemp);
			omiteCuerpo = 1;
		}else if(!(it->second->parametros->Equals(ftemp->parametros))){
			std::wcout <<L"("<< ftemp->nombre<<L")";
			Err(L"Signature parameters mismatch.");	
			delete(ftemp);
			omiteCuerpo =1;
		}else{
			//Asigna la funcion para que agregue variables a la tabla
			f=it->second;
			f->definida = 1;
			omiteCuerpo = 0;
			std::map<std::wstring,Variable *>::iterator it = ftemp->vhash.begin();
			while(it != ftemp->vhash.end()){
				
				f->vhash.insert(std::make_pair(it->first,it->second));
				it++;
			}
			//Paso de contador de direcciones virtuales
			f->intNum = ftemp->intNum;
			f->floatNum = ftemp->floatNum;
			f->stringNum = ftemp->stringNum;
			//Se libera memoria de la funcion temporal
			delete (ftemp);
			//Se necesita explicitamente NULL por que C++ no lo hace
			ftemp = NULL;
		}

	}

	//Metodo para agregar variable actual a funcion
	void agregaVariable(FuncionX *funcion){
		//Por ahora solo se guardan las variables
		//Mas adelante se guasrdaran los valores en la estructura
		std::map<std::wstring,Variable *>::iterator it = funcion->vhash.find(identificador);
		std::map<std::wstring,Variable *>::iterator itglobal = tabglobales->vhash.find(identificador);
		if( it != funcion->vhash.end() || itglobal != tabglobales->vhash.end()) {
			std::wcout << L"("<<identificador<<L")";
			Err(L"Variable already declared.");
		}else{
			//Si es un prametro de la funcion
			//Tambien se agrega a la lista de parametros
			if(parametros == 1){
				funcion->parametros->Append(tipovariable);
			}
			v = new Variable();
			v->nombre = identificador;
			v->tipo = tipovariable;
			switch(tipovariable){
				case 11://entero
					funcion->intNum++;
					v->direccion=funcion->intNum;
					break;
				case 12://flotante
					funcion->floatNum++;
					v->direccion=funcion->floatNum;
					break;
				case 13://string
					funcion->stringNum++;
					v->direccion=funcion->stringNum;
					break;
			}
			funcion->vhash.insert(std::make_pair(v->nombre,v));
		}

	}

/*-------------------------------------------------------------*/


	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void QRex();
	void DeclaracionGlobal();
	void FuncionFirma();
	void QRex2();
	void Funcion();
	void Cuerpo2();
	void Cuerpo();
	void Tipov();
	void ID(wchar_t* name);
	void Declaracion();
	void Estatuto();
	void Llamada();
	void Param();
	void Lectura();
	void Var_Cte();
	void Expresion();
	void Tipof();
	void Dec_Param();
	void Dec_ParamFirma();
	void Condicion();
	void Asignacion();
	void Escritura();
	void Ciclo();
	void Exp1();
	void Exp2();
	void Exp3();
	void Exp4();
	void Exp5();
	void Exp6();

	void Parse();

}; // end Parser

} // namespace


#endif

