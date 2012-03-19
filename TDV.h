#if !defined(TDV_H)
#define TDV_H
#include <map>
#include <utility>
#include <string>

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
	Node *head;
	public:
		List() { head = NULL; };
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
};

/*Funciones*/
class FuncionX{
	public:
		std::wstring nombre;
		int tipo;
		List *parametros;
		std::map<std::wstring, Variable *> vhash;
		int intNum;
		int floatNum;
		int stringNum;

	FuncionX(){
		tipo = 0;
		parametros = new List();
		intNum = 0;
		floatNum = 0;
		stringNum = 0;
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

/*Definicion de la Tabla de Variables*/

class TablaDeVariables{
	public:
		std::map<std::wstring, FuncionX *> fhash;
		
		TablaDeVariables(){

		}

		~TablaDeVariables(){
			fhash.clear();
		}

};

};
#endif
