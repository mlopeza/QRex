

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
		operadorActual=GOTO;
		metePoper();
		gCuadruploInicial();
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
		QRex2();
}

void Parser::DeclaracionGlobal() {
		Tipov();
		ID();
		registraGlobal();
		while (la->kind == 21) {
			Get();
			ID();
			registraGlobal();
		}
		Expect(18);
}

void Parser::FuncionFirma() {
		Tipof();
		ID();
		registraFirma();
		Expect(19);
		if (la->kind == 5 || la->kind == 6 || la->kind == 7) {
			Dec_ParamFirma();
		}
		Expect(20);
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
		registraMain(); gCuadruploGOTOMain();
		tipo = undef;
		Cuerpo();
		tab->fhash.insert(std::make_pair(f->nombre,f));
		
		verificaLlamadaDefinida();
		operadorActual=FIN;
		metePoper();
		gCuadruplo();
		imprimeRegistros();
		creaObj();
		
}

void Parser::Funcion() {
		Tipof();
		tipo = funcion;
		ID();
		wchar_t* name = coco_string_create(t->val);
		identificador = std::wstring(name);
		coco_string_delete(name);
		ftemp = new FuncionX();
		ftemp->nombre = identificador;
		ftemp->tipo =tipofuncion;
		
		Expect(19);
		if (la->kind == 5 || la->kind == 6 || la->kind == 7) {
			Dec_Param();
		}
		Expect(20);
		tipo = undef;
}

void Parser::Cuerpo2() {
		Expect(22);
		while (la->kind == 5 || la->kind == 6 || la->kind == 7) {
			Declaracion();
		}
		while (StartOf(1)) {
			Estatuto();
		}
		if (la->kind == 15) {
			Get();
			if (StartOf(2)) {
				Expresion();
				if (f->tipo != dameTipo(PilaO->Peek())+10 ){
				std::wcout<< L"Returned value not expected"<< f->tipo << L"\n";
				exit(-1);
				}
				operadorActual=RETURN;
				metePoper();
				gCuadruplo();
				
				
			} else if (la->kind == 2) {
				Get();
				std::wcout<< L"Returned value not allowed"<< L"\n";
				exit(-1);
				
				/*tipovariable = cadenav;
				wchar_t* name = coco_string_create(t->val);
				identificador = std::wstring(name);
				coco_string_delete(name);
				registraConstante(); */
				
			} else SynErr(40);
			Expect(18);
		}
		Expect(23);
		if(omiteCuerpo == 0){
		operadorActual=RETORNO;
		metePoper();
		gCuadruplo();
		}
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

void Parser::ID() {
		Expect(1);
}

void Parser::Declaracion() {
		tipo = variable;
		Tipov();
		ID();
		registraVariable(f);
		while (la->kind == 21) {
			Get();
			ID();
			registraVariable(f);
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
		std::wcout << L"Fin de parametros\n";
			meteLlamada();std::wcout << L"Fin de parametros1\n";
}

void Parser::Param() {
		operadorActual=PIZQ;
		llamada = 1;
		metePoper();
		
		if (StartOf(2)) {
			if(tipo == escritura){
			Poper->Push(PRINT);
			}
			
			Expresion();
			if(tipo == escritura){
			gCuadruplo();
			} else if(llamada == 1){
			generaParametro();
			}
			
		} else if (la->kind == 2) {
			Get();
			tipovariable = cadenav;
			wchar_t* name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			if(tipo == escritura){
			std::map<std::wstring,Variable *>::iterator it = tabconstantes->vhash.find(identificador);
			Poper->Push(PRINT);
			PilaO->Push((it->second)->direccion);
			gCuadruplo();
			std::wcout << L" cuadruplo correcto string \n";
			} else	if(llamada == 1){
			std::map<std::wstring,Variable *>::iterator it = tabconstantes->vhash.find(identificador);
			PilaO->Push((it->second)->direccion);
			generaParametro();
			}
			std::wcout << L" param fin  string 4\n";
			
		} else SynErr(43);
		operadorActual=PDER;
		llamada = 0;
		sacaPoper();
		//	std::wcout << L" poper 3 " << Poper->Peek() << L'\n';
		//	std::wcout << L" despeus de meter llamada poper 4 " << Poper->Peek() << L'\n';
		
		if (la->kind == 21) {
			Get();
			Param();
		}
}

void Parser::Lectura() {
		Expect(12);
		Expect(19);
		ID();
		verificaExistenciaLectura();
		Expect(20);
		Expect(18);
}

void Parser::Var_Cte() {
		if (la->kind == 4) {
			Get();
			tipovariable = enterov;
			wchar_t* name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			if(expresion == 1){
			metePilaO();
			}
			
		} else if (la->kind == 3) {
			Get();
			tipovariable = flotantev;
			wchar_t* name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			if(expresion == 1){
			metePilaO();
			}
			
		} else if (la->kind == 1) {
			ID();
			metePilaOV();
			if (la->kind == 19) {
				PilaO->Pop();
				verificaLlamada();
				
				Llamada();
				std::wcout<< L"Fin de llamada qwer:"<<  L"\n";
				//else if(llamada == 1){
				if (p != NULL){
				std::wcout<< L"p not null:"<<  L"\n";
				exit(-1);
				}
				Poper->Push(GOSUB);
				gCuadruplo();
				
				//}
				llamada = 0;
				l = NULL;
				p = NULL;
				
			}
		} else SynErr(44);
}

void Parser::Expresion() {
		expresion = 1;
		Exp1();
		int peek = Poper->Peek();
		if(peek == OR){
		//std::wcout << "Se genero en EXP1\n";
		gCuadruplo();
		}
		
		if (la->kind == 25) {
			Get();
			operadorActual=OR; metePoper();
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
		Tipov();
		ID();
		registraParametroFuncion(ftemp);
		if (la->kind == 21) {
			Get();
			Dec_Param();
		}
}

void Parser::Dec_ParamFirma() {
		Tipov();
		if(firma == 1)
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
		operadorActual=GOTOF; metePoper(); gCuadruplo();
		Expect(20);
		tipo = undef;
		Cuerpo();
		if (la->kind == 9) {
			Get();
			operadorActual=GOTO; metePoper();gCuadruploGOTOElse();
			Cuerpo();
		}
		operadorActual=GOTO; metePoper();gCuadruploGOTOIf();
}

void Parser::Asignacion() {
		ID();
		metePilaOV();		
		Expect(24);
		if (StartOf(2)) {
			Poper->Push(ASIGNA);	
			Expresion();
			gCuadruplo();	
		} else if (la->kind == 2) {
			Get();
			tipovariable = cadenav;
			wchar_t* name = coco_string_create(t->val);
			identificador = std::wstring(name);
			coco_string_delete(name);
			registraConstante();
			
		} else SynErr(46);
		Expect(18);
}

void Parser::Escritura() {
		Expect(10);
		tipo = escritura;
		std::wcout<< L"Print " << L'\n';
		Expect(19);
		Param();
		std::wcout<< L"despues de param " << L'\n';
		Expect(20);
		Expect(18);
		tipo = undef;
}

void Parser::Ciclo() {
		Expect(13);
		tipo = ciclo;
		Expect(19);
		PilaS->Push(contCuadruplos);
		Expresion();
		operadorActual=GOTOF; metePoper(); gCuadruplo();
		Expect(20);
		tipo = undef;
		Cuerpo();
		operadorActual=GOTO; metePoper();gCuadruploGOTOWhile();
}

void Parser::Exp1() {
		Exp2();
		int peek = Poper->Peek();
		if(peek == AND){
		//std::wcout << "Se genero en EXP1\n";
		gCuadruplo();
		}
		
		if (la->kind == 26) {
			Get();
			operadorActual = AND;metePoper();
			Exp1();
		}
}

void Parser::Exp2() {
		Exp3();
		if (StartOf(4)) {
			switch (la->kind) {
			case 27: {
				Get();
				operadorActual=MAYOR;
				break;
			}
			case 28: {
				Get();
				operadorActual=MENOR;
				break;
			}
			case 29: {
				Get();
				operadorActual=MAYQUE;
				break;
			}
			case 30: {
				Get();
				operadorActual=MENQUE;
				break;
			}
			case 31: {
				Get();
				operadorActual=IGUAL;
				break;
			}
			case 32: {
				Get();
				operadorActual=DIFERENTE;
				break;
			}
			}
			metePoper();
			Exp3();
			gCuadruplo();	
			//std::wcout << "Se genero en EXP2\n";
			
			
		}
}

void Parser::Exp3() {
		Exp4();
		int peek = Poper->Peek();
		if(peek == MAS || peek == MENOS){
		//std::wcout << "Se genero en EXP3\n";
		gCuadruplo();
		}
		
		if (la->kind == 33 || la->kind == 34) {
			if (la->kind == 33) {
				Get();
				operadorActual=MAS;
			} else {
				Get();
				operadorActual=MENOS;
			}
			metePoper();
			Exp3();
		}
}

void Parser::Exp4() {
		Exp5();
		int peek = Poper->Peek();
		if(peek == POR || peek == DIVISION || peek == MODULO){
		//std::wcout << "Se genero en EXP4\n";
		gCuadruplo();
		}
		
		if (la->kind == 35 || la->kind == 36 || la->kind == 37) {
			if (la->kind == 35) {
				Get();
				operadorActual=POR;
			} else if (la->kind == 36) {
				Get();
				operadorActual=DIVISION;
			} else {
				Get();
				operadorActual=MODULO;
			}
			metePoper();
			Exp4();
		}
}

void Parser::Exp5() {
		if (la->kind == 38) {
			Get();
			operadorActual=NOT;metePoper(); 
		}
		Exp6();
		int peek = Poper->Peek();
		if(peek == NOT){
		//std::wcout << "Se genero en EXP5\n";
		gCuadruplo();
		}
		
}

void Parser::Exp6() {
		if (la->kind == 19) {
			Get();
			operadorActual=PIZQ;metePoper();
			Expresion();
			Expect(20);
			operadorActual=PDER;sacaPoper();
		} else if (StartOf(5)) {
			if (la->kind == 33 || la->kind == 34) {
				if (la->kind == 33) {
					Get();
				} else {
					Get();
					operadorActual=NEGATIVO;metePoper();
				}
			}
			Var_Cte();
			int peek = Poper->Peek();
			if(peek == NEGATIVO){
			//std::wcout << "Se genero en EXP6\n";
			gCuadruplo();
			}
			
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

