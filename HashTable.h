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
		ListLinked<TableEntry<V>>** table;	//array de listas encadenadas

		//función que suma los valores ASCII de la clave y el tamaño de la tabla hash
		int h(std::string key){
			int sum=0;
			for(size_t i=0; i<key.size(); i++){
				sum+= int(key.at(i));
			}
			return sum%max;
		}

	public:
		//constructor que reserva e inicializa
		HashTable(int size): n(0), max(size), table(nullptr){
			if(size<=0) throw std::runtime_error("Tamaño de la tabla invalido.");
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
			int b= h(key);
			TableEntry<V> probe(key);
			for(int i=0; i<table[b]->size(); i++){
				const auto& te= table[b]->get(i);
				if(te== probe){
					throw std::runtime_error("Key '"+key+" 'ya existe");
				}
			}
			table[b]->append(TableEntry<V>(key,value));
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
			out<<"HashTable [entries: "<<th.n<<", capacity: "<<th.max<<"]\n";
			out<<"===================\n\n";
			for(int b=0; b<th.max; b++){
				out<<"== Cubeta"<<b<<" ==\n\n";
				out<<"List=> [\n";
				for(int i=0; i<th.table[b]->size(); i++){
					const auto& te= th.table[b]->get(i);
					out<<" ('"<<te.key<<"' => "<<te.value<<")\n";
				}
				out<<"]\n\n";
			}
			out<<"=============\n";
			return out;
		}

		V remove(std::string key) override {
		    int b = h(key);
    			TableEntry<V> probe(key);
    			for (int i = 0; i < table[b]->size(); i++) {
        			const auto& te = table[b]->get(i);
        			if (te == probe) {
            				V val = te.value;
            				table[b]->remove(i);
            				n--;
            				return val;
        	}	
    }
    throw std::runtime_error("Key '" + key + "' not found!");
}


V search(std::string key) override {
    int b = h(key);
    TableEntry<V> probe(key);
    for (int i = 0; i < table[b]->size(); ++i) {
        const auto& te = table[b]->get(i);
        if (te == probe) return te.value;
    }
    throw std::runtime_error("Key '" + key + "' not found!");
}

};

#endif
