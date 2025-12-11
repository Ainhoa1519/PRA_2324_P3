#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry{
	public:
		std::string key;	//elemento clave del par
		V value;		//elemento valor del par

		//constructor con la clave y el valor
		TableEntry(std::string k, V v): key(k), value (v) {
		}

		//constructor solo con la clave
		TableEntry (std::string k): key(k), value(){
		}

		//constrtuctor por defecto
		TableEntry():key(""),value(){
		}

		//sobrecarga global del operador ==
		//determinar si 2 instancias son iguales (si comparten misma clave)
		friend bool operator==(const TableEntry<V>& te1, const TableEntry<V>& te2){
			return te1.key==te2.key;
		}

		//sobrecarga del operador !=
		//determinar si 2 instancias son diferentes (claves diferentes)
		friend bool operator!=(const TableEntry<V>& te1, const TableEntry<V>& te2){
			return te1.key!=te2.key;
		}

		//sobrecargar del operador <<
		//imprimir contenido de la entrada
		friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& te){
			out<<"("<<te.key<<" ' => "<<te.value<<")";
			return out;
		}
};

#endif
