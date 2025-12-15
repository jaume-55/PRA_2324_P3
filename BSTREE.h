#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        //miembros privados
        int nelem;
        BSNode<T> *root;

        //métodos privados
        BSNode<T>* search(BSNode<T>* n, T e) const{
            if(n == NULL) return nullptr;
            else if (n->elem == e) return n;
            else if(n->elem > e) return search(n->left, e);
            else return search(n->right, e);
        }

        BSNode<T>* insertar_nodo(BSNode<T>* n, T e){
            if(n == NULL){
                nelem++;
                return new BSNode<T>(e);
            }
            else if(e < n->elem){
                n->left = insertar_nodo(n->left, e);
            } else if(e > n->elem){
                n->right = insertar_nodo(n->right, e);
            } else {
                throw std::runtime_error("Element already exists");
            }
            return n;
        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            if(n != nullptr){
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
        }

        BSNode<T>* remove(BSNode<T>* n, T e){
            if(n == nullptr) return n;
            else if(e < n->elem){
                n->left = remove(n->left, e);
            } else if(e > n->elem){
                n->right = remove(n->right, e);
            } else {
                if(n->left == nullptr){
                    BSNode<T>* temp = n->right;
                    delete n;
                    nelem--;
                    return temp;
                } else if(n->right == nullptr){
                    BSNode<T>* temp = n->left;
                    delete n;
                    nelem--;
                    return temp;
                }

                BSNode<T>* temp = min(n->right);

                n->elem = temp->elem;

                n->right = remove(n->right, temp->elem);
            }
            return n;
        }

        T max(BSNode<T>* n) const{
            while(n->right != nullptr){
                n = n->right;
            }
            return n->elem;
        }

        BSNode<T>* remove_max(BSNode<T>* n){
            if(n->right == nullptr){
                BSNode<T>* left = n->left;
                delete n;
                nelem--;
                return left;
            }
            n->right = remove_max(n->right);
            return n;
        }

        BSNode<T>* min(BSNode<T>* n) const{
            if(n == nullptr) return nullptr;
            while(n->left != nullptr){
                n = n->left;
            }
            return n;
        }

        void delete_cascade(BSNode<T>* n){
            if(n != nullptr){
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }


    public:
        // miembros públicos
        
        //Constructor
        BSTree() { nelem = 0; root = nullptr; }

        //Destructor
        ~BSTree() { delete_cascade(root); }

        int size() const{
            return nelem;
        }

        T search(T e) const{
            BSNode<T> *nodo = search(root, e);
            if(nodo == nullptr) throw std::runtime_error("Elemento no encontrado");
            return nodo->elem;
        }

        T operator[](T e) const{
            return search(e);
        }

        void insert(T e){
            root = insertar_nodo(root, e);
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;
        }

        void remove(T e){
            root = remove(root, e);
        }

};

#endif