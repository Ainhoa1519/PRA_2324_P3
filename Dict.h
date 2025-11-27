#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V>
class Dict {
public:
    // Inserta un par clave->valor en el diccionario
    virtual void insert(std::string key, V value) = 0;

    // Busca el valor correspondiente a la clave 
    virtual V search(std::string key) = 0;

    // Elimina el par clave->valor si se encuentra en el diccionario y devuelve el valor eliminado
    virtual V remove(std::string key) = 0;

    // Devuelve el número de elementos en el diccionario
    virtual int entries() = 0;

    // Destructor virtual para permitir herencia segura
    virtual ~Dict() {}
};

#endif

