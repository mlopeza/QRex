#if !defined(TDV_H)
#define TDV_H
#include <map>
#include <utility>
#include <string>

#define PROCINT 4000
#define PROCFLOAT 6000
#define PROCSTRING 8000

#define GLOBAL_INT 	10000
#define GLOBAL_FLOAT	12000
#define GLOBAL_STRING	14000

#define CONSTANT_INT	16000
#define CONSTANT_FLOAT	18000
#define CONSTANT_STRING 20000

#define TEMP_INT 22000
#define TEMP_FLOAT 23000
#define TEMP_STRING 24000

namespace std
{
	typedef basic_string<char> string;
	typedef basic_string<wchar_t> wstring;
};

namespace QRex{
	/*Variables*/
	class Variable{
		public:
			std::wstring nombre;
			int tipo;
			int direccion;

			Variable(){
				tipo = -1;
				direccion = -1;
			}

			~Variable(){
			}

	};

	/*Linked List de Parametros*/
	class Node {
		int data;
		std::wstring nombre;

		Node* next;

		public:
		Node() {data = -1; next = NULL;};
		~Node(){}
		void SetData(int aData) { data = aData; };
		void SetNombre(std::wstring aNombre) { nombre = aNombre; };
		void SetNext(Node* aNext) { next = aNext; };
		int Data() { return data; };
		std::wstring Nombre() { return nombre; };
		Node* Next() { return next; };

	};

	class List {
		public:
			Node *head;
			int size;

			List() { head = NULL; size = 0;};
			void Append(int data){
				// Crea nuevo nodo
				Node* newNode = new Node();
				newNode->SetData(data);
				newNode->SetNext(NULL);

				// Crea pointer temporal
				Node *tmp = head;

				if ( tmp != NULL ) {
					// Hay nodos en la Lista
					// Busca hasta llegar al final de la lista
					while ( tmp->Next() != NULL ) {
						tmp = tmp->Next();
					}

					// Asigna al ultimo nodo el nuevo nodo
					tmp->SetNext(newNode);
				}else {
					// Asigna el primer Nodo
					head = newNode;
				}
				size++;
			};

			void Append2(int data,std::wstring nombre){
				// Crea nuevo nodo
				Node* newNode = new Node();
				newNode->SetData(data);
				newNode->SetNombre(nombre);
				newNode->SetNext(NULL);

				// Crea pointer temporal
				Node *tmp = head;

				if ( tmp != NULL ) {
					// Hay nodos en la Lista
					// Busca hasta llegar al final de la lista
					while ( tmp->Next() != NULL ) {
						tmp = tmp->Next();
					}

					// Asigna al ultimo nodo el nuevo nodo
					tmp->SetNext(newNode);
				}else {
					// Asigna el primer Nodo
					head = newNode;
				}
				size++;
			}
			void Print(){
				Node *tmp = head;
				std::wcout<< L"Parametros:";
				while(tmp != NULL){
					std::wcout<< L"("<< tmp->Data() << L","<<tmp->Nombre()<< L")" <<L"   ";
					tmp=tmp->Next();
				}

				std::wcout<< L"\n";
			};

			void Delete(){
				Node *tmp = head;
				Node *tmp2;
				while(tmp != NULL){
					tmp2=tmp->Next();
					delete(tmp);
					tmp=tmp2;
				}
			};

			bool Equals(List *lista){
				Node *tmp = head;
				Node *x = lista->head;

				//Tienen la misma cantidad de parametros?
				if(lista->size != this->size)
					return false;

				//Checa si son del mismo tipo
				while(tmp != NULL){

					if(x->Data() != tmp->Data())
						return false;
					x = x->Next();
					tmp = tmp->Next();
				}

				//Los parametros son iguales
				return true;
			};

			Node *getNode(int place){
				
				int index = 1;

				Node *tmp = head;
				while(tmp != NULL && index < place){
					tmp = tmp->Next();
					index++;
				}

				return tmp;
			};

	};

	/*Funciones*/
	class FuncionX{
		public:
			std::wstring nombre;
			int tipo;
			int definida;
			List *parametros;
			std::map<std::wstring, Variable *> vhash;
			int intNum;
			int floatNum;
			int stringNum;
			int dirInicial;

			FuncionX(){
				tipo = 0;
				definida = 0;
				parametros = new List();
				intNum = PROCINT-1;
				floatNum = PROCFLOAT-1;
				stringNum = PROCSTRING-1;
				dirInicial = -1;
			}

			void Insert(int n){
				parametros->Append(n);
			}

			~FuncionX(){
				if(parametros != NULL){

					parametros->Delete();
					delete(parametros);
				}
				vhash.clear();
			}

	};

	/*Contexto, se utiliza para variables globales
	  y constantes*/
	class Contexto{
		public:
			std::map<std::wstring, Variable *> vhash;
			int intNum;
			int floatNum;
			int stringNum;

			Contexto(int enteros,int flotantes,int cadenas){
				intNum = enteros;
				floatNum = flotantes;
				stringNum = cadenas;
			}

			~Contexto(){
				vhash.clear();
			}

	};

	/*Definicion de la Tabla de Variables*/
	class TablaDeVariables{
		public:
			std::map<std::wstring, FuncionX *> fhash;

			TablaDeVariables(){}
			~TablaDeVariables(){fhash.clear();}
	};

	class Cuadruplo{
		public:
			int op;
			int operador1;
			int operador2;
			int resultado;

			Cuadruplo(int a, int b, int c, int d){
				op = a;
				operador1 = b;
				operador2 = c;
				resultado = d;
			}

			~Cuadruplo(){}
	};

	class Pila{
		Node *head;
		int nodos;

		public:
		Pila(){
			head = NULL;
			nodos = 0;
		};

		~Pila(){};

		void Push(int dato){
			//Crea el Nodo
			Node *n = new Node();
			n->SetData(dato);

			if(head == NULL){
				head = n;
			}else{
				n->SetNext(head);
				head = n;
			}
			
			//Suma uno en nodos
			nodos++;
		};

		int Pop(){
			if(head == NULL)
				return -1;

			//Resta uno en nodos
			nodos--;

			//Toma el valor
			Node *tmp = head;
			int dato = tmp->Data();

			//Asigna el siguiente valor en la pila
			head = head->Next();

			//Borra el nodo de memoria
			delete tmp;

			//Regresa el dato
			return dato;
		};

		int Peek(){
			if(head == NULL)
				return -1;
			return head->Data();
		};

		bool Vacio(){
			if (head == NULL)
				return true;

			return false;			
		};
		
		int Size(){
			return nodos;
		};

	};

	class Temporales{
		public:
			std::map<int, Variable *> vhash;
			int intNum;
			int floatNum;
			int stringNum;

			Temporales(int enteros,int flotantes,int cadenas){
				intNum = enteros;
				floatNum = flotantes;
				stringNum = cadenas;
			}

			int AsignaTemporal(int tipo){
				Variable *v;
				switch(tipo){
					case 11:
						v = new Variable();
						v->direccion =intNum;v->tipo=tipo;
						vhash.insert(std::make_pair(intNum,v));
						intNum++;
						return intNum -1;
						break;
					case 12:
						v = new Variable();
						v->direccion =floatNum;v->tipo=tipo;
						vhash.insert(std::make_pair(floatNum,v));
						floatNum++;
						return floatNum -1;
						break;
					default: return -1;

						break;
				}
			}

			int LiberTemporales(){
				vhash.clear();
			}

			~Temporales(){
				vhash.clear();
			}

	};

};
#endif
