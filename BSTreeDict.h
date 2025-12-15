#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "dict.h"
#include "BSTREE.h"
#include "tableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict() : tree(nullptr){}

        ~BSTreeDict(){
            clear(tree);
            tree = nullptr;
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            out << *(bs.tree);
            return out;
        }

        V operator[](std::string key){
            TableEntry<V> te(key, V());
            BSNode<TableEntry<V>>* nodo = tree->search(te);
            return nodo->elem.getValue();
        }
        
};

#endif