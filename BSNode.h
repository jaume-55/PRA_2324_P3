#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        // miembros públicos
        T elem;
        BSNode<T> *left;
        BSNode<T> *right;

        //Método constructor
        
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
            : elem(elem), left(left), right(right) {}


        //sobrecarga del operador << (imprimir el elemento por pantalla)
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
            out << "Valor del elemento: " << bsn.elem;

            return out;
        }
};

#endif