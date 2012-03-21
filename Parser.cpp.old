

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
		while (la->kind == _int || la->kind == _float || la->kind == _void) {
			Funcion();
			Cuerpo2();
		}
		tipo = funcion;
		Expect(_main);
		Expect(16 /* "(" */);
		Expect(17 /* ")" */);
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
		Expect(16 /* "(" */);
		if (la->kind == _int || la->kind == _float || la->kind == _string) {
			Dec_Param();
		}
		Expect(17 /* ")" */);
		tipo = undef;
}

void Parser::Cuerpo2() {
		Expect(18 /* "{" */);
		while (la->kind == _int || la->kind == _float || la->kind == _string) {
			Declaracion();
		}
		while (StartOf(1)) {
			Estatuto();
		}
		if (la->kind == _return) {
			retorno = 1;tipo = regreso;
			Get();
			if (StartOf(2)) {
				Expresion();
			} else if (la->kind == _cte_string) {
				Get();
			} else SynErr(38);
			Expect(21 /* ";" */);
		}
		Expect(19 /* "}" */);
		retorno = 0;tipo = undef;
}

void Parser::Cuerpo() {
		Expect(18 /* "{" */);
		while (la->kind == _int || la->kind == _float || la->kind == _string) {
			Declaracion();
		}
		while (StartOf(1)) {
			Estatuto();
		}
		Expect(19 /* "}" */);
}

void Parser::Declaracion() {
		wchar_t* name; 
		tipo = variable;
		Tipov();
		ID(name);
		while (la->kind == 20 /* "," */) {
			Get();
			ID(name);
		}
		Expect(21 /* ";" */);
		tipo = undef;
}

void Parser::Estatuto() {
		if (la->kind == _id) {
			Asignacion();
		} else if (la->kind == _if) {
			Condicion();
		} else if (la->kind == _print) {
			Escritura();
		} else if (la->kind == _read) {
			Lectura();
		} else if (la->kind == _while) {
			Ciclo();
		} else SynErr(39);
}

void Parser::Tipov() {
		if (la->kind == _int) {
			Get();
			tipovariable = enterov;    
		} else if (la->kind == _float) {
			Get();
			tipovariable = flotantev;  
		} else if (la->kind == _string) {
			Get();
			tipovariable = cadenav;    
		} else SynErr(40);
}

void Parser::ID(wchar_t* name) {
		Expect(_id);
		name = coco_string_create(t->val); 
		//Conversion para meter el string a la tabla de hash
		identificador = std::wstring(name);
		//Eliminar el string de coco
		coco_string_delete(name);
		
		if(tipo == variable){
		//Por ahora solo se guardan las variables
		//Mas adelante se guasrdar'an los valores en la estructura
			std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		
			if( it != f->vhash.end() ) {
				std::wcout << L"("<<identificador<<L")";
				Err(L"Variable already declared.");
			}else{
				v = new Variable();
				v->nombre = identificador;
				v->tipo = tipovariable;
				switch(tipovariable){
					case 11://entero
						f->intNum++;
						v->direccion=f->intNum;
		
						break;
		
					case 12://flotante
						f->floatNum++;
						v->direccion=f->floatNum;
						break;
		
					case 13://string
						f->stringNum++;
						v->direccion=f->stringNum;
						break;
		
				}
				f->vhash.insert(std::make_pair(v->nombre,v));
			}
		}else if(tipo == funcion){
		std::map<std::wstring,FuncionX *>::iterator it = tab->fhash.find(identificador);
		
		//Con esto se sobreescribe la funcion poniendo la ultima en la lista
		//Es una forma de lidiar con funciones con el mismo nombre
		if(identificador == f->nombre){
			delete(f);
			f = new FuncionX();
			f->nombre = identificador;
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
		
		} else if(tipo == lectura){
		std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		
		if( it != f->vhash.end() ) {
			//Read Variable
		}else{
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Trying to read and variable doesn't exist.");
		}	
		}else if(tipo == escritura){
		std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		if( it != f->vhash.end() ) {
			//Read Variable
		}else{
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Trying to write and variable doesn't exist.");
		}		
		}else if(tipo == condicion || tipo == ciclo || tipo == regreso){
		std::map<std::wstring,Variable *>::iterator it = f->vhash.find(identificador);
		if( it != f->vhash.end() ) {
			//Read Variable
		}else{
			std::wcout <<L"("<< identificador<<L")";
			Err(L"Trying use a variable that doesn't exist.");
		}		
		
		}
		
		
}

void Parser::Llamada() {
		Expect(16 /* "(" */);
		if (StartOf(3)) {
			Param();
		}
		Expect(17 /* ")" */);
}

void Parser::Param() {
		if (StartOf(2)) {
			Expresion();
		} else if (la->kind == _cte_string) {
			Get();
		} else SynErr(41);
		if (la->kind == 20 /* "," */) {
			Get();
			Param();
		}
}

void Parser::Lectura() {
		wchar_t* name; 
		Expect(_read);
		Expect(16 /* "(" */);
		tipo=lectura;
		ID(name);
		Expect(17 /* ")" */);
		Expect(21 /* ";" */);
		tipo = undef;
}

void Parser::Var_Cte() {
		wchar_t* name; 
		if (la->kind == _cte_int) {
			Get();
		} else if (la->kind == _cte_float) {
			Get();
		} else if (la->kind == _id) {
			ID(name);
			if (la->kind == 16 /* "(" */) {
				Llamada();
			}
		} else SynErr(42);
}

void Parser::Expresion() {
		expresion = 1;
		Exp1();
		if (la->kind == 23 /* "||" */) {
			Get();
			Expresion();
		}
		expresion = 0;
}

void Parser::Tipof() {
		if (la->kind == _int) {
			Get();
			tipofuncion = enterof;   
		} else if (la->kind == _float) {
			Get();
			tipofuncion = flotantef; 
		} else if (la->kind == _void) {
			Get();
			tipofuncion = voidf; 
		} else SynErr(43);
}

void Parser::Dec_Param() {
		wchar_t* name; 
		Tipov();
		ID(name);
		if (la->kind == 20 /* "," */) {
			Get();
			Dec_Param();
		}
}

void Parser::Condicion() {
		Expect(_if);
		tipo = condicion;
		Expect(16 /* "(" */);
		Expresion();
		Expect(17 /* ")" */);
		tipo = undef;
		Cuerpo();
		if (la->kind == _else) {
			Get();
			Cuerpo();
		}
}

void Parser::Asignacion() {
		wchar_t* name; 
		ID(name);
		Expect(22 /* "=" */);
		if (StartOf(2)) {
			Expresion();
		} else if (la->kind == _cte_string) {
			Get();
		} else SynErr(44);
		Expect(21 /* ";" */);
}

void Parser::Escritura() {
		Expect(_print);
		tipo = escritura;
		Expect(16 /* "(" */);
		Param();
		Expect(17 /* ")" */);
		Expect(21 /* ";" */);
		tipo = undef;
}

void Parser::Ciclo() {
		Expect(_while);
		tipo = ciclo;
		Expect(16 /* "(" */);
		Expresion();
		Expect(17 /* ")" */);
		tipo = undef;
		Cuerpo();
}

void Parser::Exp1() {
		Exp2();
		if (la->kind == 24 /* "&&" */) {
			Get();
			Exp1();
		}
}

void Parser::Exp2() {
		Exp3();
		if (StartOf(4)) {
			switch (la->kind) {
			case 25 /* ">" */: {
				Get();
				break;
			}
			case 26 /* "<" */: {
				Get();
				break;
			}
			case 27 /* ">=" */: {
				Get();
				break;
			}
			case 28 /* "<=" */: {
				Get();
				break;
			}
			case 29 /* "==" */: {
				Get();
				break;
			}
			case 30 /* "!=" */: {
				Get();
				break;
			}
			}
			Exp3();
		}
}

void Parser::Exp3() {
		Exp4();
		if (la->kind == 31 /* "+" */ || la->kind == 32 /* "-" */) {
			if (la->kind == 31 /* "+" */) {
				Get();
			} else {
				Get();
			}
			Exp4();
		}
}

void Parser::Exp4() {
		Exp5();
		if (la->kind == 33 /* "*" */ || la->kind == 34 /* "/" */ || la->kind == 35 /* "%" */) {
			if (la->kind == 33 /* "*" */) {
				Get();
			} else if (la->kind == 34 /* "/" */) {
				Get();
			} else {
				Get();
			}
			Exp5();
		}
}

void Parser::Exp5() {
		if (la->kind == 36 /* "!" */) {
			Get();
		}
		Exp6();
}

void Parser::Exp6() {
		if (la->kind == 16 /* "(" */) {
			Get();
			Expresion();
			Expect(17 /* ")" */);
		} else if (StartOf(5)) {
			if (la->kind == 31 /* "+" */ || la->kind == 32 /* "-" */) {
				if (la->kind == 31 /* "+" */) {
					Get();
				} else {
					Get();
				}
			}
			Var_Cte();
		} else SynErr(45);
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
	maxT = 37;

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

	static bool set[6][39] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,x,x, x,x,x,x, T,x,T,x, T,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,x,T, T,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x,x, T,x,x},
		{x,T,T,T, T,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x,x, T,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,T, T,T,T,x, x,x,x,x, x,x,x},
		{x,T,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x,x, x,x,x}
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
			case 16: s = coco_string_create(L"\"(\" expected"); break;
			case 17: s = coco_string_create(L"\")\" expected"); break;
			case 18: s = coco_string_create(L"\"{\" expected"); break;
			case 19: s = coco_string_create(L"\"}\" expected"); break;
			case 20: s = coco_string_create(L"\",\" expected"); break;
			case 21: s = coco_string_create(L"\";\" expected"); break;
			case 22: s = coco_string_create(L"\"=\" expected"); break;
			case 23: s = coco_string_create(L"\"||\" expected"); break;
			case 24: s = coco_string_create(L"\"&&\" expected"); break;
			case 25: s = coco_string_create(L"\">\" expected"); break;
			case 26: s = coco_string_create(L"\"<\" expected"); break;
			case 27: s = coco_string_create(L"\">=\" expected"); break;
			case 28: s = coco_string_create(L"\"<=\" expected"); break;
			case 29: s = coco_string_create(L"\"==\" expected"); break;
			case 30: s = coco_string_create(L"\"!=\" expected"); break;
			case 31: s = coco_string_create(L"\"+\" expected"); break;
			case 32: s = coco_string_create(L"\"-\" expected"); break;
			case 33: s = coco_string_create(L"\"*\" expected"); break;
			case 34: s = coco_string_create(L"\"/\" expected"); break;
			case 35: s = coco_string_create(L"\"%\" expected"); break;
			case 36: s = coco_string_create(L"\"!\" expected"); break;
			case 37: s = coco_string_create(L"??? expected"); break;
			case 38: s = coco_string_create(L"invalid Cuerpo2"); break;
			case 39: s = coco_string_create(L"invalid Estatuto"); break;
			case 40: s = coco_string_create(L"invalid Tipov"); break;
			case 41: s = coco_string_create(L"invalid Param"); break;
			case 42: s = coco_string_create(L"invalid Var_Cte"); break;
			case 43: s = coco_string_create(L"invalid Tipof"); break;
			case 44: s = coco_string_create(L"invalid Asignacion"); break;
			case 45: s = coco_string_create(L"invalid Exp6"); break;

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

