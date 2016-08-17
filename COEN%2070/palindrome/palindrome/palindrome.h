//
//  palindrome.h
//  palindrome
//
//  Created by Alex Hoff on 2/3/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#ifndef palindrome_palindrome_h
#define palindrome_palindrome_h

#include <iostream>
#include <ctype.h>
#include <cassert>

using namespace std;

class Stack
{
public:
    /* Function: Constructors */
    Stack();
    /* Function: Destructor */
    ~Stack();
	// Function: Copy constructor
    Stack(const Stack&);
    // Function: Insert an item to the front list
    void push(const char&);
    char pop();
private:
    class node
    {
    public:
        node(double, node*);
        char data;
        node* next;
    };
    int size;
    node *first;
};

Stack::Stack()
{
	first = new node(0, NULL); //dummy
	first->next = first; // points back to dummy
	size = 0;
}


Stack::~Stack()
{
	node* prev = first->next;
	node* next = prev->next;
	while( next != first ) // while the next isnt the dummy
	{
		delete prev;
		prev = next;
		next = next->next;
	}
	delete first; // delete the dummy
}

Stack::Stack(const Stack& other)
{
	first = new node(0, NULL); //dummy
	first->next = first; // points back to dummy
	size = 0;
	
	node* otherDummy = other.first;    // get other dummy node
	node* otherNext = otherDummy->next;    // get other next
	
	while( otherNext != otherDummy )
	{
		push( otherNext->data );
		otherNext = otherNext->next;
	}
}

// Adds the variable into the first spot of the linked list
// Precondition: Data is a number
// Postcondition: Node is at the head of the list
void Stack::push(const char& var)
{
    assert(isalpha(var) == 1);
    node* temp;
    temp = new node(var,first);
    temp->next = first->next;
    first->next = temp;
    size++;
}

char Stack::pop()
{
    node *temp;
    char output;
    temp = first->next;
    first->next = temp->next;
    output = temp->data;
    size--;
    return output;
}

Stack::node::node(double var, node* dummy)
{
	data = var;
	next = dummy;
}

#endif
