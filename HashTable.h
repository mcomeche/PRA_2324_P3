#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h" 

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        
	int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	
	int h(std::string key){
		int suma = 0;
		for(int i = 0; i < key.length(); i++){
			char letra = key.at(i);
			suma += int(letra);
		}

		return suma % max;
	}

    public:
	
	HashTable(int size){
		n = 0;
		max = size;
		table = new ListLinked<TableEntry<V>>[size];
	}
	~HashTable()
	{
		for(int i = 0; i < max; i++)
			table[i].~ListLinked();
		
		delete[] table;
	}
	int capacity(){
		return max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		out << "HashTable [Entries: " << th.n << ", Capacity: " << th.max << "]\n" << "\n";
		for(int i = 0; i < th.max; i++){

			out << "Cubeta : " << i << " \n";
	
			out<<th.table[i]<<std::endl;
		}
			return out;
	}
	V operator[](std::string key){
		
		int pos = table[h(key)].search(key);

		if(pos < 0)
			throw std::runtime_error("No encontrado");
		
		V aux = table[h(key)].get(pos).value;
		return aux;
	}
	
        void insert(std::string key, V value) override{	

		int pos = table[h(key)].search(key);

                if(pos >= 0)
                        throw std::runtime_error("Ya introducido");

		TableEntry<V> aux(key, value);
		table[h(key)].prepend(aux);
		n++;
	}	

	V search(std::string key) override{
		
		int hash = h(key);
		int pos = table[h(key)].search(key);

                if(pos < 0)
                        throw std::runtime_error("No encontrado");

                V aux = table[hash].get(pos).value;
                return aux;
	}

	V remove(std::string key) override{
		
		int pos = table[h(key)].search(key);

                if(pos > max || pos < 0)
                        throw std::runtime_error("No encontrado");

		V aux = table[h(key)].remove(pos).value;
		n--;
		return aux;
	}

	int entries() override{
		return n;
	}
        
};

#endif
