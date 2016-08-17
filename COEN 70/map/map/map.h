//
//  map.h
//  map
//
//  Created by Alex Hoff and Nathaniel Kragason 2/18/14.
//

#ifndef map_map_h
#define map_map_h

#include <list>
#include "Pair.h"
using namespace std;

template<typename K, typename V>
class Map
{
public:
    /**
     Inserts a value into the map.
     @param key the key to insert
     @param value the value to insert
     */
    void insert(K key, V value);
    /**
     Determines whether the map contains a given key.
     @param key the key to check for
     */
    bool contains_key(K key);
    /**
     Retrieves the value of a given key.
     @param key the key to find
     @return the value
     */
    V value_of(K key);
    /**
     Removes the key and value.
     @param key the key to find
     */
    void remove_key(K key);
    /*
     Prints out the contents of the map
     */
    void print();
    
private:
    list< Pair<K, V> > data;
};

template<typename K, typename V>
void Map<K,V>::insert (K key, V value){
    Pair<K,V> temp(key,value);
    data.push_back(temp);
}

template<typename K, typename V>
bool Map<K,V>::contains_key(K key){
    for (typename list< Pair<K, V> >::iterator it =data.begin(); it != data.end(); ++it){
        if (it->get_first() == key) {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
V Map<K,V>::value_of(K key){
    for (typename list< Pair<K, V> >::iterator it=data.begin(); it != data.end(); ++it){
        if (it->get_first() == key) {
            return it->get_second();
        }
    }
    cout << "This key does not exist" << endl;
    V temp;
    return temp;
}

template<typename K, typename V>
void Map<K,V>::remove_key(K key){
    for (typename list< Pair<K, V> >::iterator it=data.begin(); it != data.end(); ++it){
        if (it->get_first() == key) {
            data.erase(it);
            return;
        }
    }
    return;
}

template<typename K, typename V>
void Map<K,V>::print(){
    for (typename list< Pair<K, V> >::iterator it=data.begin(); it != data.end(); ++it){
        cout << "(" << it.get_first << "," << it.get_second << ")" << endl;
    }
}


#endif
