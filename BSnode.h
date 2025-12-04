#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>
template <typename T>
class BSNode{
	public:
		T elem;	//elemento tipo T almacena en el Nodo
		BSNode<T>* izquierda;	//puntero al nodo sigueinte (izquierdo)
		BSNode<T>* derecha;	//puntero al nodo anterior (derecho)


		//método constructor
		//crea BSNode con el elemento elem y los punteros 
		BSNode(T elem, BSNode<T>* izquierda= nullptr, BSNode<T>* derecha=nullptr):elem(elem), izquierda(izquierda),derecha(derecha){}

		//sobrecarga del operador <<
		//imprime el nodo por pantalla
		friend std::ostream& operator<<(std::ostream& out, const BSNode<T>& bsn){
			out<<bsn.elem;
			return out;
		}
};

#endif
