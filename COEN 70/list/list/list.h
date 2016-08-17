//
//  list.h
//  list
//
//  Created by Alex Hoff and Aaron Chung on 1/20/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//
//  Lab: Mon 2:15
//  Coen 70

#ifndef list_list_h
#define list_list_h

#include <iostream>

using namespace std;

class List
{
public:
    /* Function: Constructors */
    List();
    /* Function: Destructor */
    ~List();
	// Function: Copy constructor
    List(const List&);
    // Function: Assignment operator
    const List& operator=(const List&);
    // Function: output operator
    friend ostream& operator<<(ostream&, const List&);
    // Function: Insert an item to the list
    // Postcondition: insert after the pointer and
    // move the pointer to the new item
    void insert(const int&);
    class node
    {
    public:
        node(int, node*);
        int data;
        node* next;
    };
private:
    node* list;
    int size;
    node* cursor;
};

List::List()
{
	list = new node(0, NULL); //dummy
	list->next = list; // points back to dummy
	size = 0;
	cursor = list; // cursor on dummy
}


List::~List()
{
	node* prev = list->next;
	node* next = prev->next;
	while( next != list ) // while the next isnt the dummy
	{
		delete prev;
		prev = next;
		next = next->next;
	}
	delete list; // delete the dummy
}

List::List(const List& other)
{
	list = new node(0, NULL); //dummy
	list->next = list; // points back to dummy
	size = 0;
	cursor = list; // cursor on dummy
	
	node* otherDummy = other.list;    // get other dummy node
	node* otherNext = otherDummy->next;    // get other next
	
	while( otherNext != otherDummy )
	{
		insert( otherNext->data );
		otherNext = otherNext->next;
	}
}

void List::insert(const int& var)
{
    cursor = list->next;
    while (cursor->next != list) {
        cursor = cursor->next;
    }
    cursor->next = new node(var,list);
    cursor = cursor->next;
    cursor->next = list;
	size++;
}

List::node::node(int var, node* dummy)
{
	data = var;
	next = dummy;
}

ostream& operator<<(ostream& out, const List& listObject)
{
    List::node* temp = listObject.list->next;
	while( temp != listObject.list )
	{
		out << temp->data << ", ";
		temp = temp->next;
    }
    return out;
}

const List& List::operator=(const List &rhs)
{
	if (this == &rhs) return *this;  // Check for Self Assignment
	
	// delete old stuff
	node* prev = list->next;
	node* next = prev->next;
	while( next != list ) // while the next isnt the dummy
	{
		delete prev;
		prev = next;
		next = next->next;
	}
	delete list; // delete the dummy
    
	// add new stuff
	list = new node(0, NULL); //dummy
	list->next = list; // points back to dummy
	size = 0;
	cursor = list; // cursor on dummy
	
	node* otherDummy = rhs.list;    // get other dummy node
	node* otherNext = otherDummy->next;    // get other next
	
	while( otherNext != otherDummy )
	{
		insert( otherNext->data );
		otherNext = otherNext->next;
	}
    return *this;
}



#endif
