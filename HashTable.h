#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V>{
	private:
		int n;	//elementos actuales
		int max;	//número total de cubetas (tamaño de la tabla)
		ListLinked<TableEntry<V>>** table;	//array de listas enlazadas (tabla de cubetas)
//almacena pares clave-> valor

		//función que suma los valores ASCII de la clave y el tamaño de la tabla hash
		int h(std::string key){
			int sum=0;	//variable que acumula la suma de los códigos ASCII
			for(size_t i=0; i<key.size(); i++){	//recorrer toda la cadena
				sum+= int(key.at(i));
			}
			return sum%max;	//devolver el resto entre la suma de caracteres y el tamaño de la tabla hash
		}

	public:
		//constructor que reserva e inicializa
		HashTable(int size): n(0), max(size), table(nullptr){
			//fuera de rango-> lanzar excepción
			if(size<=0) throw std::runtime_error("Tamaño de la tabla invalido.");
			//está dentro del rango
			table=new ListLinked<TableEntry<V>>*[max];
			for (int i = 0; i < max; ++i) {
    				table[i] = new ListLinked<TableEntry<V>>();
			}
		}

		//destructor que libera memoria
		~HashTable() {
        		for(int i=0; i<max; i++){
				delete table[i];
			}
			delete[] table;
    		}

		//capacidad total de la tabla (cubetas)
		int capacity(){
			return max;	//devolver nº total de cubetas
		}

		//implementación Dict<V>
		void insert(std::string key, V value)override{
			//calcular la posición hash donde debería ir la clave (llamar función de suma)
			int b= h(key);
			TableEntry<V> probe(key);	//crea un objeti solo con la clave, sin valor alguno
			for(int i=0; i<table[b]->size(); i++){	//recorre la lista table[b]
				//obtiene cada entrada te
				const auto& te= table[b]->get(i);
				//comparar si la clave que quiero insertar ya existe
				if(te== probe){	//si existe
					throw std::runtime_error("Key '"+key+" 'ya existe");
				}
			}//si no existe la clave
			//crear un TableEntry completo y lo añade al final de la lista de b
			table[b]->append(TableEntry<V>(key,value));
			//actualizar el contador de elementos del diccionario
			n++;
		}

		int entries()override{
			return n;
		}

		//sobrecargar operador[]
		//devuelve el valor de la clave
		V operator[](std::string key){
			return this->search(key);
		}

		//sobrecarga del operador <<
		//imprimir contenido de la tabla
		friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th){
			//imprimir número de elementos almacenados y el número de cubetas
			out<<"HashTable [entries: "<<th.n<<", capacity: "<<th.max<<"]\n";
			out<<"===================\n\n";
			for(int b=0; b<th.max; b++){	//recorre todas las cubetas
				//imprimir la cabecera de la cubeta
				out<<"== Cubeta"<<b<<" ==\n\n";
				//cada cubeta es una lista, abrir la lista de esa cubeta
				out<<"List=> [\n";
				for(int i=0; i<th.table[b]->size(); i++){	//recorrer los elementos de la lista
					//obtiene la referencia constante al elemento i almacenado en la lista b (cubetas)
					const auto& te= th.table[b]->get(i);
					out<<" ('"<<te.key<<"' => "<<te.value<<")\n";
				}
				out<<"]\n\n";	//cerrar la lista
			}
			out<<"=============\n";
			return out;	//devolver flujo
		}

		V remove(std::string key) override {
			//calcular en qué cubeta debería estar la clave
		    int b = h(key);
    			TableEntry<V> probe(key);	//crear entrada con solo la clave (para comparar)
    			for (int i = 0; i < table[b]->size(); i++) {
					//obtener el elemento i de la cubeta sin copiarlo
        			const auto& te = table[b]->get(i);
        			if (te == probe) {	//mirar si la clave es la que busco
            				V val = te.value;	//guarda el valor asociado a la clave
            				table[b]->remove(i);	//elimina la netrada de la cubeta
            				n--;
						//devolver valor que estaba asociado a esa clave
            				return val;
        	}	
    }	//si no se encuentra la clave en la cubeta -> lanzar excepción
    throw std::runtime_error("Key '" + key + "' not found!");
}


V search(std::string key) override {
	//calcular en qué cubeta debe estar la clave (llamar a la función de la suma)
    int b = h(key);
	//cerar la entrada con solo la clave
    TableEntry<V> probe(key);
    for (int i = 0; i < table[b]->size(); ++i) {
        const auto& te = table[b]->get(i);	//obtiene el elemento i de la cubeta
        if (te == probe) return te.value;	//si la clave coincide se devuelve el valor asociado
    }//si no coincide-> lanzar excepción
    throw std::runtime_error("Key '" + key + "' not found!");
}

};

#endif
