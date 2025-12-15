#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "dict.h"
#include "tableEntry.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        //Atributos privados de la clase
        int n;
        int max;
        TableEntry<V> * table;

    public:
        //métodos virtuales de dict.h
        void insert(std::string key, V value) override {
            int index = h(key);
            int start = index;
            bool found = false;
            do {
                if (table[index].key == key) {
                    throw std::runtime_error("Key already exists");
                }
                if (table[index].key == "") {
                    table[index] = TableEntry<V>(key, value);
                    n++;
                    return;
                }
                index = (index + 1) % max;
            } while (index != start);
            throw std::runtime_error("Hash table is full");
        }

        V search(std::string key) override {
            int index = h(key);
            int start = index;
            do {
                if (table[index].key == key) {
                    return index;
                }
                if (table[index].key == "") {
                    break;
                }
                index = (index + 1) % max;
            } while (index != start);
            throw std::runtime_error("Elemento no encontrado");
        }

        V remove(std::string key) override {
            int index = h(key);
            int start = index;
            do {
                if (table[index].key == key) {
                    V value = table[index].value;
                    table[index] = TableEntry<V>();
                    n--;
                    return value;
                }
                if (table[index].key == "") {
                    break;
                }
                index = (index + 1) % max;
            } while (index != start);
            throw std::runtime_error("Elemento no encontrado");
        }



        int entries() override { return n; }

        //Función hash
        int h(std::string key){
            int sum = 0;
            for(int i = 0; i < key.size(); ++i){
                sum += static_cast<int>(key.at(i));
            }
            return sum % max;
        }

        //Método constructor
        HashTable(int size){
            max = size;
            n = 0;
            table = new TableEntry<V>[max];
        }

        //Método destructor
        ~HashTable(){
            delete[] table;
        }

        //Devuelve el número total de cubetas
        int capacity(){
            return max;
        }

        //Sobrecarga del operador << (devolver la tabla hash entera)
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
            for(int i = 0; i < th.max; ++i){
                if (th.table[i].key != "") {
                    out << "[" << i << "] ";
                    out << th.table[i] << "\n";
                }
            }
            return out;
        }

        V operator[](std::string key){
            int index = h(key);
            int start = index;
            do {
                if (table[index].key == key) {
                    return table[index].value;
                }
                if (table[index].key == "") {
                    break;
                }
                index = (index + 1) % max;
            } while (index != start);
            throw std::runtime_error("Elemento no encontrado");
        }

};

#endif