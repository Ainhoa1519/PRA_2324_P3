#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
        out << *(bs.tree);
        return out;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return this->search(key);
    }

    // Métodos heredados de Dict<V>

    int entries() override {
        return tree->size();
    }

    void insert(std::string key, V value) override {
        TableEntry<V> te(key, value);
        tree->insert(te);
    }

    V search(std::string key) override {
        TableEntry<V> te(key);
        return tree->search(te).value;
    }

    V remove(std::string key) override {
        TableEntry<V> te(key);
        V val = tree->search(te).value;
        tree->remove(te);
        return val;
    }
};

#endif

