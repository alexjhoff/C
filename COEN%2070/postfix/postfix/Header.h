//
//  Header.h
//  postfix
//
//  Created by Alex Hoff on 1/27/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#ifndef postfix_Header_h
#define postfix_Header_h

#include <iostream>
#include <cassert>

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
    void insert(const double&);
    double pop();
    class node
    {
    public:
        node(double, node*);
        double data;
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
// Adds the variable into the first spot of the linked list
// Precondition: Data is a number
// Postcondition: Node is at the head of the list
void List::insert(const double& var)
{
    assert(isdigit(var) == 1);
    node* ptr;
    ptr = list->next;
    list->next = new node(var,list);
    cursor = list->next;
    cursor->next = ptr;
	size++;
}

double List::pop()
{
    double output;
    cursor = list->next;
    list->next = cursor->next;
    output = cursor->data;
    delete cursor;
    return output;
}

List::node::node(double var, node* dummy)
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
