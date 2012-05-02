#include <QString>
#include <map>
#include <utility>
class Quadruple{
	public:
		Quadruple(){
			quadruple[0]=-1;
			quadruple[1]=-1;
			quadruple[2]=-1;
			quadruple[3]=-1;
		}

		int getQ(int index){
			return quadruple[index];
		}

		void setQ(int index,int value){
			quadruple[index]=value;
		}

	private:
		int quadruple[4];

};

class Memory{
	public:
		Memory(){
			ultimaLinea=0;
		}

		QString getVar(int address){
			std::map<int,QString>::iterator it = mem.find(address);
			if(it != mem.end()){
				return it->second;
			}else{
				mem.insert(std::make_pair(address,"0"));
				return "0";
			}

		}

		void setVar(int address,QString value){
			std::map<int,QString>::iterator it = mem.find(address);
			if(it != mem.end()){
				mem.erase(it);
				mem.insert(std::make_pair(address,value));
			}else{
				mem.insert(std::make_pair(address,value));
			}

		}

		void print(){
			std::map<int,QString>::iterator it = mem.begin();
			qDebug()<<"Memoria=============";
			while(it!=mem.end()){
				qDebug()<<it->first<<"::"<<it->second;
				it++;
			}
			qDebug()<<"Memoria============";
		}

		void setLine(int i){
			ultimaLinea = i;
		}

		int getLine(){
			return ultimaLinea;
		}
	private:
		std::map<int,QString> mem;
		int ultimaLinea;	

};

class Node {
	Memory *memory;
	Node* next;

	public:
	Node() {};
	~Node(){}

	void SetData(Memory *mem) { memory = mem; };
	void SetNext(Node* aNext) { next = aNext; };

	Memory *Data() { return memory; };
	Node* Next() { return next; };

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

	void Push(Memory *dato){
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

	Memory *Pop(){
		if(head == NULL)
			return NULL;

		//Resta uno en nodos
		nodos--;

		//Toma el valor
		Node *tmp = head;
		Memory *dato = tmp->Data();

		//Asigna el siguiente valor en la pila
		head = head->Next();

		//Borra el nodo de memoria
		delete tmp;

		//Regresa el dato
		return dato;
	};

	Memory *Peek(){
		if(head == NULL)
			return NULL;
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


