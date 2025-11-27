#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;	//puntero al primer nodo de la lista
    int n;	//numero de leementos en la lista
		
	Node<T>* head;
	int size_;
public:
//método constructor
    ListLinked() : first(nullptr), n(0) {	//inicializar los 2 atributos 
    }	//lista vacía
//método destructor
    ~ListLinked() {	//liberar memoria
        while (first != nullptr) {	//mientras haya nodos
            Node<T>* aux = first->next;	//guardar siguiente nodo
            //liberar nodo
	    delete first;	
            first = aux;	//avanza al siguiente nodo
        }
    }

    //sobrecarga del operador []
    T operator[](int pos) {	//devuelve el elemento situado en pos
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida!");
        Node<T>* aux = first;
        for (int i = 0; i < pos; ++i)
            aux = aux->next;
        return aux->data;	//devuelve el dato del noto de esa posición
    }

    //sobrecarga el operador <<
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
	//imprime una instancia de Listinked<T> por pantalla
        Node<T>* aux = list.first;
        out << "List => [";
        //recorrer la lista
	while (aux != nullptr) {
            out << aux->data;
	    //añadir espacio si hay otro nodo
            if (aux->next != nullptr) out << " ";
            aux = aux->next;
        }
        out << "]";	//fin de la escritura
        return out;
    }

    // implementaciones override de List<T>
    bool empty()const override{
			//devolver true si la lista está vacía
			return n==0;
		}

    int size()const override{
			//devolver número de elementos de la lista
			return n;
		}

    T get(int pos) override {
    	if (pos < 0 || pos >= n){ // Verifica si la posición es válida
        	throw std::out_of_range("Posición inválida!");
    	}
    	Node<T>* aux = first; // Empieza desde el primer nodo
    	for (int i = 0; i < pos; i++){
        	aux = aux->next; // Avanza hasta la posición deseada
	}
    	return aux->data; // Devuelve el dato del nodo
	}

    void insert(int pos, const T& item) override {
    	if (pos < 0 || pos > n){ // Verifica si la posición es válida
        	throw std::out_of_range("Posición inválida!");
    		}
	if (pos == 0) {
        	first = new Node<T>(item, first); // Inserta al principio
    		} 
	else {
        	Node<T>* aux = first; // Empieza desde el primer nodo
        	for (int i = 0; i < pos - 1; i++)
            		aux = aux->next; // Avanza hasta el nodo anterior
        	aux->next = new Node<T>(item, aux->next); // Inserta en medio o al final
    }
    n++; // Incrementa el tamaño de la lista
}

	
	T remove(int pos) override {
    		if (pos < 0 || pos >= n){ // ver si está fuera de rango
        		throw std::out_of_range("Posición inválida!");
		}
			T result;
    		if (pos == 0) {
        		Node<T>* aux = first; // Nodo a eliminar
        		result = aux->data; // Guarda el dato
        		first = first->next; // Actualiza el primer nodo
        		delete aux; // Libera memoria
    			} 
		else {
        		Node<T>* aux = first; // Nodo anterior al que se elimina
        		for (int i = 0; i < pos - 1; i++){
            		aux = aux->next;
        		Node<T>* toDelete = aux->next; // Nodo a eliminar
        		result = toDelete->data; // Guarda el dato
        		aux->next = toDelete->next; // Salta el nodo eliminado
        		delete toDelete; // Libera memoria
			}
    }
    n--; // Reduce el tamaño de la lista
    return result; // Devuelve el dato eliminado
}

	int search(const T& item) const override {
    		Node<T>* aux = first; // Empieza desde el primer nodo
    		int pos = 0;
    		while (aux != nullptr) {
        		if (aux->data == item){ // Si encuentra el dato
            			return pos; // Devuelve la posición
		}
			aux = aux->next;
        		pos++;
    }
    return -1; // Si no lo encuentra, devuelve -1
}
    
	friend ListLinked<T> operator-(const ListLinked<T>& l1, const ListLinked<T>& l2){
		ListLinked<T>result;
		Node<T>* p1= l1.head;
		Node<T>* p2= l2.head;
		while(p1&&p2){
			result.insert(p1->value - p2->value);
			p1= p1->next;
			p2=p2->next;
		}

		return result;
	}

	void append(T e) override {
    	Node<T>* nuevo = new Node<T>(e);
    	if (head == nullptr) {
        	head = nuevo;
    	} else {
        	Node<T>* aux = head;
        	while (aux->next != nullptr) {
            		aux = aux->next;
        	}
        	aux->next = nuevo;
    	}
    		size_++;
	}

	void prepend(T e) override {
    		Node<T>* nuevo = new Node<T>(e);
    		nuevo->next = head;
    		head = nuevo;
    		size_++;
	}



};

#endif
