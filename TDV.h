#if !defined(TDV_H)
#define TDV_H
#include <map>
#include <utility>
#include <string>

#define PROCINT 4000
#define PROCFLOAT 6000
#define PROCSTRING 8000
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
	Node* next;

  public:
	Node() {data = -1; next = NULL;};
	~Node(){}
	void SetData(int aData) { data = aData; };
	void SetNext(Node* aNext) { next = aNext; };
	int Data() { return data; };
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

		void Print(){
			Node *tmp = head;
			std::wcout<< L"Parametros:";
			while(tmp != NULL){
				std::wcout<< L"("<< tmp->Data() << L")" <<L"   ";
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

	FuncionX(){
		tipo = 0;
		definida = 0;
		parametros = new List();
		intNum = PROCINT-1;
		floatNum = PROCFLOAT-1;
		stringNum = PROCSTRING-1;
	}

	void Insert(int n){
		parametros->Append(n);
	}

	~FuncionX(){
		parametros->Delete();
		delete(parametros);
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

};
#endif
