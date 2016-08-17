//
//  dictionary.h
//  dictionary
//
//  Created by Alex Hoff on 3/9/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#ifndef dictionary_dictionary_h
#define dictionary_dictionary_h

#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std;

template <class RecordType>
class table
{
public:
    // MEMBER CONSTANT
    static const size_t CAPACITY = 811;
    // CONSTRUCTOR
    table( );
    // MODIFICATION MEMBER FUNCTIONS
    void insert(const RecordType& entry);
    void remove(string key);
    // CONSTANT MEMBER FUNCTIONS
    bool is_present(string key) const;
    void find(string key, bool& found, RecordType& result) const;
    size_t size( ) const { return used; }
private:
    // MEMBER VARIABLES
    RecordType data[CAPACITY];
    size_t used;
    // HELPER FUNCTIONS
    size_t hash(string key) const;
    size_t next_index(size_t index) const;
    void find_index(string key, bool& found, size_t& index) const;
    bool never_used(size_t index) const;
    bool is_vacant(size_t index) const;
};

template <class RecordType>
table<RecordType>::table( )
{
    size_t i;
    
    used = 0;
    for (i = 0; i < CAPACITY; ++i)
        data[i].key = "NEVER_USED";  // Indicates a spot that's never been used.
}

template <class RecordType>
void table<RecordType>::insert(const RecordType& entry)
{
    bool already_present;   // True if entry.key is already in the table
    size_t index;        // data[index] is location for the new entry
    
    
    // Set index so that data[index] is the spot to place the new entry.
    find_index(entry.key, already_present, index);
    
    // If the key wasn't already there, then find the location for the new entry.
    if (!already_present)
    {
        assert(size( ) < CAPACITY);
        index = hash(entry.key);
        while (!is_vacant(index))
            index = next_index(index);
        ++used;
    }
    
    data[index] = entry;
}

template <class RecordType>
void table<RecordType>::remove(string key)
{
    bool found;        // True if key occurs somewhere in the table
    size_t index;   // Spot where data[index].key == key
    
    find_index(key, found, index);
    if (found)
    {   // The key was found, so remove this record and reduce used by 1.
        data[index].key = "PREVIOUSLY_USED"; // Indicates a spot that's no longer in use.
        --used;
    }
}

template <class RecordType>
bool table<RecordType>::is_present(string key) const
{
    bool found;
    size_t index;
    
    find_index(key, found, index);
    return found;
}

template <class RecordType>
void table<RecordType>::find(string key, bool& found, RecordType& result) const
{
    size_t index;
    
    find_index(key, found, index);
    if (found)
        result = data[index];
}

template <class RecordType>
size_t table<RecordType>::hash(const string key) const
{
    int result = 0;
    for (int i = 0; i < key.length(); ++i)
        result = result + static_cast<int>(key[i]);
    return (result % CAPACITY);
}

template <class RecordType>
size_t table<RecordType>::next_index(size_t index) const
{
    return ((index+1) % CAPACITY);
}

template <class RecordType>
void table<RecordType>::find_index(string key, bool& found, size_t& i) const
{
	size_t count; // Number of entries that have been examined
    
	count = 0;
	i = hash(key);
	while((count < CAPACITY) && (data[i].key.compare("NEVER_USED") != 0) && (hash(data[i].key) != hash(key)))
	{
	    ++count;
	    i = next_index(i);
	}
	found = (hash(data[i].key) == hash(key));
}

template <class RecordType>
bool table<RecordType>::never_used(size_t index) const
{
	if(data[index].key.compare("NEVER_USED") == 0){
        return true;
    }
    else
        return false;
}

template <class RecordType>
bool table<RecordType>::is_vacant(size_t index) const
{
	if(data[index].key.compare("NEVER_USED") == 0 || data[index].key.compare("PREVIOUSLY_USED") == 0){
        return true;
    }
    else
        return false;
}







#endif
