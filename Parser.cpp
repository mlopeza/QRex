

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"


namespace QRex {


void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::QRex() {
		InitDeclarations();
		while (la->kind == 16 || la->kind == 17) {
			if (la->kind == 16) {
				Get();
				DeclaracionGlobal();
			} else {
				firma = 1;
				Get();
				FuncionFirma();
				Expect(18);
				firma = 0;
			}
		}
		tab->fhash.insert(std::make_pair(f->nombre,f));
		QRex2();
}

void Parser::DeclaracionGlobal() {
		wchar_t* name; global = 1; 
		tipo = variable;		
		Tipov();
		ID(name);
		while (la->kind == 21) {
			Get();
			ID(name);
		}
		Expect(18);
		tipo = undef; global = 0;	
}

void Parser::FuncionFirma() {
		wchar_t* name; 
		Tipof();
		tipo = funcionfirma;
		ID(name);
		tipo = variable;
		Expect(19);
		if (la->kind == 5 || la->kind == 6 || la->kind == 7) {
			Dec_ParamFirma();
		}
		Expect(20);
		tipo = undef;
}

void Parser::QRex2() {
		while (la->kind == 5 || la->kind == 6 || la->kind == 14) {
			definefunc = 1;
			Funcion();
			verificaRegistroFuncion();
			Cuerpo2();
			definefunc = 0;omiteCuerpo=0;
		}
		tipo = funcion;
		Expect(11);
		Expect(19);
		Expect(20);
		registraMain();
		tipo = undef;
		Cuerpo();
		tab->fhash.insert(std::make_pair(f->nombre,f));
		
		imprimeRegistros();
}

void Parser::Funcion() {
		wchar_t* name; 
		Tipof();
		tipo = funcion;
		ID(name);
		tipo = variable;
		Expect(19);
		if (la->kind == 5 || la->kind == 6 || la->kind == 7) {
			Dec_Param();
		}
		Expect(20);
		tipo = undef;
}

void Parser::Cuerpo2() {
		wchar_t* name;
		Expect(22);
		while (la->kind == 5 || la->kind == 6 || la->kind == 7) {
			Declaracion();
		}
		while (StartOf(1)) {
			Estatuto();
		}
		if (la->kind == 15) {
			retorno = 1;tipo = regreso;
			Get();
			if (StartOf(2)) {
				Expresion();
			} else if (la->kind == 2) {
				Get();
				tipovariable = cadenav;
				name = coco_string_create(t->val);
				identificador = std::wstring(name);
				coco_string_delete(name);
				registraConstante();
				
			} else SynErr(40);
			Expect(18);
		}
		Expect(23);
		retorno = 0;tipo = undef;
}

void Parser::Cuerpo() {
		Expect(22);
		while (la->kind == 5 || la->kind == 6 || la->kind == 7) {
			Declaracion();
		}
		while (StartOf(1)) {
			Estatuto();
		}
		Expect(23);
}

void Parser::Tipov() {
		if (la->kind == 5) {
			Get();
			tipovariable = enterov;    
		} else if (la->kind == 6) {
			Get();
			tipovariable = flotantev;  
		} else if (la->kind == 7) {
			Get();
			tipovariable = cadenav;    
		} else SynErr(41);
}

void Parser::ID(wchar_t* name) {
		Expect(1);
		if(omiteCuerpo == 1){
		return;
		}
		//Crea el string de coco 
		//Conversion para meter el string a la tabla de hash
		//Eliminar el string de coco
		name = coco_string_create(t->val);identificador = std::wstring(name);coco_string_delete(name);
		
		/*Crea las firmas de las funciones*/
		if(tipo == funcionfirma && firma == 1){
		std::map<std::wstring,FuncionX *>::iterator it = tab->fhash.find(identificador);
		
		//Con esto se sobreescribe la funcion poniendo la ultima en la lista
		//Es una forma de lidiar con funciones con el mismo nombre
		if(identificador == f->nombre){
			delete(f);
			f = new FuncionX();
			f->nombre = identificador;
			f->tipo = tipofuncion;
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Function already declared.");
		}else if( it == tab->fhash.end()) {
			//Checa si hay una funcion antes de crear la funcion main
			if(f->nombre == std::wstring(L"")){
				f->nombre=identificador;
				f->tipo=tipofuncion;
		
			}else{
				//Inserta la funcion  al hash y crea la funcion main
				tab->fhash.insert(std::make_pair(f->nombre,f));
				f = new FuncionX();
				f->nombre=identificador;
				f->tipo=tipofuncion;
			}
		}else{
			//Ejecuta lo mismo que el primer if, solo que cuando ya existe en el hash
			tab->fhash.insert(std::make_pair(f->nombre,f));
			tab->fhash.erase(it);
			f = new FuncionX();
			f->nombre = identificador;
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Function already declared.");
		}
		return;
		
		}
		
		//Se agregan parametros para comparar a la funcion temporal con la firma
		if(tipo == variable && definefunc == 1){
		//Agrega a la tabla de variables temporal
		if(ftemp == NULL){
			agregaVariable(f);
		}else{					
			agregaVariable(ftemp);
		
		}
		return;
		}
		
		//Registro de la funcion
		if(tipo == funcion && definefunc == 1){
		//Crea la funcion a comparar con la firma
		//Y asigna los atributos necesarios
		ftemp = new FuncionX();
		ftemp->tipo = tipofuncion;
		ftemp->nombre = identificador;
		return;					
		
		} 
		
		
		/*Registra las variables globales*/				
		if(tipo == variable && global == 1){
		std::map<std::wstring,Variable *>::iterator it = tabglobales->vhash.find(identificador);
		
		if(it != tabglobales->vhash.end()){
			std::wcout << L"Global("<<identificador<<")";
			Err(L"Variable already declared.");
		}else{
			v = new Variable();
			v->nombre = identificador;
			v->tipo = tipovariable;
			switch(tipovariable){
				case 11://entero
					v->direccion=tabglobales->intNum;
					tabglobales->intNum++;
					break;
				case 12://flotante
					v->direccion=tabglobales->floatNum;
					tabglobales->floatNum++;
					break;
				case 13://string
					v->direccion=tabglobales->stringNum;
					tabglobales->stringNum++;
					break;
			}	
		}
		//Insertar en tabla de variables Globales
		tabglobales->vhash.insert(std::make_pair(v->nombre,v));
		return;
		
		}
		
		//Registra las variables de las funciones
		if(tipo == variable){
		//Registra la variable en la funcion
		agregaVariable(f);
		return;
		}
		
		//Definiciones semanticas de lectura
		if(tipo == lectura){
		std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		std::map<std::wstring,Variable *>::iterator itglobal = tabglobales->vhash.find(identificador);
		if( it != f->vhash.end() || itglobal != tabglobales->vhash.end()) {
			//Read Variable
		}else{
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Trying to read and variable doesn't exist.");
		}
		return;	
		}
		
		//Definiciones semanticas de escritura
		if(tipo == escritura){
		std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		std::map<std::wstring,Variable *>::iterator itglobal = tabglobales->vhash.find(identificador);
		if( it != f->vhash.end() || itglobal != tabglobales->vhash.end()) {
			//Write Variable
		}else{
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Trying to write and variable doesn't exist.");
		}
		
		return;		
		}
		
		//Definiciones semanticas de ciclo o condicion
		if(tipo == condicion || tipo == ciclo){
		std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		std::map<std::wstring,Variable *>::iterator itglobal = tabglobales->vhash.find(identificador);
		if( it != f->vhash.end() || itglobal != tabglobales->vhash.end()) {
			//Do whatever
		}else{
			if((it->second)->tipo == 13 ){
				std::wcout <<L"("<< identificador<<L")";
				Err(L"Trying use a String value in expresion.");
			}else{
				std::wcout <<L"("<< identificador<<L")";
				Err(L"Trying use a variable that doesn't exist.");
			}
		}
		
		return;		
		
		}
		
		//Define semantica de retorno
		if(tipo == regreso){
		std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		std::map<std::wstring,Variable *>::iterator itglobal = tabglobales->vhash.find(identificador);
		if( it != f->vhash.end() || itglobal != tabglobales->vhash.end()) {
			//Do Return
		}else{
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Trying use a variable that doesn't exist.");
		}
		
		return;
		}
		
		
}

void Parser::Declaracion() {
		wchar_t* name; 
		tipo = variable;
		Tipov();
		ID(name);
		while (la->kind == 21) {
			Get();
			ID(name);
		}
		Expect(18);
		tipo = undef;
}

void Parser::Estatuto() {
		if (la->kind == 1) {
			Asignacion();
		} else if (la->kind == 8) {
			Condicion();
		} else if (la->kind == 10) {
			Escritura();
		} else if (la->kind == 12) {
			Lectura();
		} else if (la->kind == 13) {
			Ciclo();
		} else SynErr(42);
}

void Parser::Llamada() {
		Expect(19);
		if (StartOf(3)) {
			Param();
		}
		Expect(20);
}

void Parser::Param() {
		wchar_t* name;
		if (StartOf(2)) {
			Expresion();
		} else if (la->kind == 2) {
			Get();
			tipovariable = cadenav;
			name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			
		} else SynErr(43);
		if (la->kind == 21) {
			Get();
			Param();
		}
}

void Parser::Lectura() {
		wchar_t* name; 
		Expect(12);
		Expect(19);
		tipo=lectura;
		ID(name);
		Expect(20);
		Expect(18);
		tipo = undef;
}

void Parser::Var_Cte() {
		wchar_t* name;
		if (la->kind == 4) {
			Get();
			tipovariable = enterov;
			name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			
		} else if (la->kind == 3) {
			Get();
			tipovariable = flotantev;
			name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			
		} else if (la->kind == 1) {
			ID(name);
			if (la->kind == 19) {
				Llamada();
			}
		} else SynErr(44);
}

void Parser::Expresion() {
		expresion = 1;
		Exp1();
		if (la->kind == 25) {
			Get();
			Expresion();
		}
		expresion = 0;
}

void Parser::Tipof() {
		if (la->kind == 5) {
			Get();
			tipofuncion = enterof;   
		} else if (la->kind == 6) {
			Get();
			tipofuncion = flotantef; 
		} else if (la->kind == 14) {
			Get();
			tipofuncion = voidf; 
		} else SynErr(45);
}

void Parser::Dec_Param() {
		wchar_t* name; 
		parametros = 1;
		Tipov();
		ID(name);
		parametros = 0;
		if (la->kind == 21) {
			Get();
			Dec_Param();
		}
}

void Parser::Dec_ParamFirma() {
		wchar_t* name; 
		Tipov();
		registraParametroFirma();
		if (la->kind == 21) {
			Get();
			Dec_ParamFirma();
		}
}

void Parser::Condicion() {
		Expect(8);
		tipo = condicion;
		Expect(19);
		Expresion();
		Expect(20);
		tipo = undef;
		Cuerpo();
		if (la->kind == 9) {
			Get();
			Cuerpo();
		}
}

void Parser::Asignacion() {
		wchar_t* name; 
		ID(name);
		Expect(24);
		if (StartOf(2)) {
			Expresion();
		} else if (la->kind == 2) {
			Get();
			tipovariable = cadenav;
			name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			
		} else SynErr(46);
		Expect(18);
}

void Parser::Escritura() {
		Expect(10);
		tipo = escritura;
		Expect(19);
		Param();
		Expect(20);
		Expect(18);
		tipo = undef;
}

void Parser::Ciclo() {
		Expect(13);
		tipo = ciclo;
		Expect(19);
		Expresion();
		Expect(20);
		tipo = undef;
		Cuerpo();
}

void Parser::Exp1() {
		Exp2();
		if (la->kind == 26) {
			Get();
			Exp1();
		}
}

void Parser::Exp2() {
		Exp3();
		if (StartOf(4)) {
			switch (la->kind) {
			case 27: {
				Get();
				break;
			}
			case 28: {
				Get();
				break;
			}
			case 29: {
				Get();
				break;
			}
			case 30: {
				Get();
				break;
			}
			case 31: {
				Get();
				break;
			}
			case 32: {
				Get();
				break;
			}
			}
			Exp3();
		}
}

void Parser::Exp3() {
		Exp4();
		if (la->kind == 33 || la->kind == 34) {
			if (la->kind == 33) {
				Get();
			} else {
				Get();
			}
			Exp4();
		}
}

void Parser::Exp4() {
		Exp5();
		if (la->kind == 35 || la->kind == 36 || la->kind == 37) {
			if (la->kind == 35) {
				Get();
			} else if (la->kind == 36) {
				Get();
			} else {
				Get();
			}
			Exp5();
		}
}

void Parser::Exp5() {
		if (la->kind == 38) {
			Get();
		}
		Exp6();
}

void Parser::Exp6() {
		if (la->kind == 19) {
			Get();
			Expresion();
			Expect(20);
		} else if (StartOf(5)) {
			if (la->kind == 33 || la->kind == 34) {
				if (la->kind == 33) {
					Get();
				} else {
					Get();
				}
			}
			Var_Cte();
		} else SynErr(47);
}




// If the user declared a method Init and a mehtod Destroy they should
// be called in the contructur and the destructor respctively.
//
// The following templates are used to recognize if the user declared
// the methods Init and Destroy.

template<typename T>
struct ParserInitExistsRecognizer {
	template<typename U, void (U::*)() = &U::Init>
	struct ExistsIfInitIsDefinedMarker{};

	struct InitIsMissingType {
		char dummy1;
	};
	
	struct InitExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static InitIsMissingType is_here(...);

	// exist only if ExistsIfInitIsDefinedMarker is defined
	template<typename U>
	static InitExistsType is_here(ExistsIfInitIsDefinedMarker<U>*);

	enum { InitExists = (sizeof(is_here<T>(NULL)) == sizeof(InitExistsType)) };
};

template<typename T>
struct ParserDestroyExistsRecognizer {
	template<typename U, void (U::*)() = &U::Destroy>
	struct ExistsIfDestroyIsDefinedMarker{};

	struct DestroyIsMissingType {
		char dummy1;
	};
	
	struct DestroyExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static DestroyIsMissingType is_here(...);

	// exist only if ExistsIfDestroyIsDefinedMarker is defined
	template<typename U>
	static DestroyExistsType is_here(ExistsIfDestroyIsDefinedMarker<U>*);

	enum { DestroyExists = (sizeof(is_here<T>(NULL)) == sizeof(DestroyExistsType)) };
};

// The folloing templates are used to call the Init and Destroy methods if they exist.

// Generic case of the ParserInitCaller, gets used if the Init method is missing
template<typename T, bool = ParserInitExistsRecognizer<T>::InitExists>
struct ParserInitCaller {
	static void CallInit(T *t) {
		// nothing to do
	}
};

// True case of the ParserInitCaller, gets used if the Init method exists
template<typename T>
struct ParserInitCaller<T, true> {
	static void CallInit(T *t) {
		t->Init();
	}
};

// Generic case of the ParserDestroyCaller, gets used if the Destroy method is missing
template<typename T, bool = ParserDestroyExistsRecognizer<T>::DestroyExists>
struct ParserDestroyCaller {
	static void CallDestroy(T *t) {
		// nothing to do
	}
};

// True case of the ParserDestroyCaller, gets used if the Destroy method exists
template<typename T>
struct ParserDestroyCaller<T, true> {
	static void CallDestroy(T *t) {
		t->Destroy();
	}
};

void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	QRex();
	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 39;

	ParserInitCaller<Parser>::CallInit(this);
	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[6][41] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x},
		{x,T,x,x, x,x,x,x, T,x,T,x, T,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x},
		{x,T,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,x, x,x,T,x, x},
		{x,T,T,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,x, x,x,T,x, x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,T,T,T, T,x,x,x, x,x,x,x, x},
		{x,T,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,x, x,x,x,x, x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	ParserDestroyCaller<Parser>::CallDestroy(this);
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"id expected"); break;
			case 2: s = coco_string_create(L"cte_string expected"); break;
			case 3: s = coco_string_create(L"cte_float expected"); break;
			case 4: s = coco_string_create(L"cte_int expected"); break;
			case 5: s = coco_string_create(L"int expected"); break;
			case 6: s = coco_string_create(L"float expected"); break;
			case 7: s = coco_string_create(L"string expected"); break;
			case 8: s = coco_string_create(L"if expected"); break;
			case 9: s = coco_string_create(L"else expected"); break;
			case 10: s = coco_string_create(L"print expected"); break;
			case 11: s = coco_string_create(L"main expected"); break;
			case 12: s = coco_string_create(L"read expected"); break;
			case 13: s = coco_string_create(L"while expected"); break;
			case 14: s = coco_string_create(L"void expected"); break;
			case 15: s = coco_string_create(L"return expected"); break;
			case 16: s = coco_string_create(L"global expected"); break;
			case 17: s = coco_string_create(L"sign expected"); break;
			case 18: s = coco_string_create(L"\";\" expected"); break;
			case 19: s = coco_string_create(L"\"(\" expected"); break;
			case 20: s = coco_string_create(L"\")\" expected"); break;
			case 21: s = coco_string_create(L"\",\" expected"); break;
			case 22: s = coco_string_create(L"\"{\" expected"); break;
			case 23: s = coco_string_create(L"\"}\" expected"); break;
			case 24: s = coco_string_create(L"\"=\" expected"); break;
			case 25: s = coco_string_create(L"\"||\" expected"); break;
			case 26: s = coco_string_create(L"\"&&\" expected"); break;
			case 27: s = coco_string_create(L"\">\" expected"); break;
			case 28: s = coco_string_create(L"\"<\" expected"); break;
			case 29: s = coco_string_create(L"\">=\" expected"); break;
			case 30: s = coco_string_create(L"\"<=\" expected"); break;
			case 31: s = coco_string_create(L"\"==\" expected"); break;
			case 32: s = coco_string_create(L"\"!=\" expected"); break;
			case 33: s = coco_string_create(L"\"+\" expected"); break;
			case 34: s = coco_string_create(L"\"-\" expected"); break;
			case 35: s = coco_string_create(L"\"*\" expected"); break;
			case 36: s = coco_string_create(L"\"/\" expected"); break;
			case 37: s = coco_string_create(L"\"%\" expected"); break;
			case 38: s = coco_string_create(L"\"!\" expected"); break;
			case 39: s = coco_string_create(L"??? expected"); break;
			case 40: s = coco_string_create(L"invalid Cuerpo2"); break;
			case 41: s = coco_string_create(L"invalid Tipov"); break;
			case 42: s = coco_string_create(L"invalid Estatuto"); break;
			case 43: s = coco_string_create(L"invalid Param"); break;
			case 44: s = coco_string_create(L"invalid Var_Cte"); break;
			case 45: s = coco_string_create(L"invalid Tipof"); break;
			case 46: s = coco_string_create(L"invalid Asignacion"); break;
			case 47: s = coco_string_create(L"invalid Exp6"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}

} // namespace

