

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
		_global=16
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
	MAS,MENOS,POR,DIVISION,MODULO,MAYOR,MENOR,DIFERENTE,IGUAL,MAYQUE,MENQUE,AND,OR,NOT,ASIGNA;


	int //tipos
	tipovariable,enterov,flotantev,cadenav,errorv;
	int 
	tipofuncion,enterof,flotantef,voidf,errorf;

	int //tipos de objetos
	tipo,variable,funcion,llamada,undef,lectura,escritura,condicion,ciclo,regreso;
	
	int //Manejo de expresiones
	expresion;

	int //Manejo de retornos
	retorno;
	
	int //Declaraciones Globales
	global;

	int //Declaracion de parametros en una funcion
	parametros;

	/*Parte para codigos de operacion*/

	TablaDeVariables *tab;		
	FuncionX *f;
	Variable *v;

	//Tabla de Variables globales y Constantes
	Contexto *tabconstantes;
	Contexto *tabglobales;

	std::wstring identificador;

	//Tabla de variables globales

	void InitDeclarations() { // it must exist
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

		//Tipo de objetos
		variable = 0;
		funcion = 1;
		llamada = 3;
		lectura = 4;
		escritura = 5;
		condicion = 6;
		ciclo = 7;
		regreso = 8;
		undef = 9;

		
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


/*-------------------------------------------------------------*/


	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void QRex();
	void DeclaracionGlobal();
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

