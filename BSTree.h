#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSnode.h"


template <typename T>
class BSTree{
	private:
		int nelem;	//número de elementos almacenados en el ABB
		BSNode<T>* root;	//nodo raíz del ABB

		//metodo recursivo
		//busqueda elementos ABB, busca y devuelve el elemento e 
		//si encuentra el árbol (raíz n) , sino lanzar excepción
		BSNode<T>* search(BSNode<T>* n, T e) const{
			if(n==nullptr) throw std::runtime_error("Elemento no encontrado");
			if(e< n->elem) return search (n->izquierda, e);
			if(e>n->elem) return search(n->derecha, e);
			return n;
		}

		//metodo recursivo
		//inserción ordenada de elementos e de manera ordenada
		//devuelve el nodo que encabeza el árbol, sino lanza excepción
		BSNode<T>* insert(BSNode<T>* n, T e){
			if(n==nullptr) return new BSNode<T>(e);
			if(e==n->elem) throw std::runtime_error("Elemento duplicado");
			if(e<n->elem) n->izquierda= insert(n->izquierda, e);
			else n->derecha=insert(n->derecha, e);
			return n;
		}

		//recorrido inorder de raíz n el árbol
		void print_inorder(std::ostream& out, BSNode<T>* n)const{
			if(n!=nullptr){
				print_inorder(out, n->izquierda);
				out<<n->elem<<" ";
				print_inorder(out, n->derecha);
			}
		}

		//metodo recursivo
		//eliminación de los elementos e cuya raíz es n
		//devuelve nodo que encabeza el arbol modificado
		BSNode<T>* remove(BSNode<T>* n, T e)const{
			if(n==nullptr){
				throw std:: runtime_error("Elemento no encontrado");
			}
			if(e<n->elem){
				n->izquierda=remove(n->izquierda,e);	
			}
			else if(e> n->elem){
				n->derecha=remove(n->derecha, e);
			}
			else{
				if(n->izquierda !=nullptr && n->derecha !=nullptr){
					n->elem=max(n->izquierda);
					n->izquierda=remove_max(n->izquierda);
				}
				else{
					BSNode<T>* temp =(n->izquierda!=nullptr)? n->izquierda: n->derecha;
					delete n;
					return temp;
				}
			}
			return n;
		}

		//metodo recursivo
		//devuelve el elemento del máximo valor contenido cuya raíz es n 
		T max(BSNode<T>* n)const{
			if(n==nullptr){
				throw std::runtime_error("Arbol vacía");
			}
			if(n->derecha !=nullptr){
				return max(n->derecha);
			}
			return n->elem;
		}

		//metodo recursivo
		//elimina de maximo valor contenido en el arbol cuya raiz es n
		BSNode<T>* remove_max(BSNode<T>* n){
			if(n->derecha==nullptr){
				BSNode<T>* temp= n->izquierda;
				delete n;
				return temp;
			}
			n->derecha=remove_max(n->derecha);
			return n;
		}

		//metodo recursivo
		//libera memoria dinámica ocupada por los objetos de tipo BSnode<T> 
		void delete_cascade(BSNode<T>* n){
			if(n!= nullptr){
				delete_cascade(n->izquierda);
				delete_cascade(n->derecha);
				delete n;
			}
		}
	public:
		//metodo constructor, crea ABB vacio
		BSTree(): nelem(0), root(nullptr){}

		//metodo destructor
		//delega en el metodo privado recursivo delete_cascade()
		 ~BSTree() {
     		   delete_cascade(root);
    		}

		 //funcion que devuelve el número de elementos del ABB
		 int size()const{
			 return nelem;
		 }
			
		 //busca y devuelve el elemento e
		 //método lanzadera del emtodo recursivo privado search
		 T search(T e)const{
			return search(root, e)->elem;
		 }
			
		 //sobrecargar del operador []
		 //interfaz al metodo search(T e)
		 T operator[](T e)const{
			return search(e);
		 }
		
		 //inserta el elemento e de manera ordenada en ABB
		 //metodo lanzadera del metodo privado insert
		 void insert (T e){
			root=insert(root, e);
			nelem++;
		 }
		
		 //elimina el elemento e del ABB
		 //metodo lanzadera del metodo privado remove
		 void remove(T e){
			root=remove(root, e);
			nelem--;
		 }
		
		 //sobrecarga del operador <<
		 //mostrar contenido de los ABB
		 friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst){
			bst.print_inorder(out, bst.root);
			return out;
		 }
};

#endif
