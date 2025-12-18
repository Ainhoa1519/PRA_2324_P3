#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;   // puntero al primer nodo de la lista
    int n;            // número de elementos en la lista

public:

    // ---------------------------------------------------------
    // Constructor: lista vacía
    // ---------------------------------------------------------
    ListLinked() : first(nullptr), n(0) {}

    // ---------------------------------------------------------
    // Destructor: libera todos los nodos
    // ---------------------------------------------------------
    ~ListLinked() {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
    }

    // ---------------------------------------------------------
    // Sobrecarga operador []
    // ---------------------------------------------------------
    T operator[](int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida!");

        Node<T>* aux = first;
        for (int i = 0; i < pos; ++i)
            aux = aux->next;

        return aux->data;
    }

    // ---------------------------------------------------------
    // Sobrecarga operador <<
    // ---------------------------------------------------------
    friend
