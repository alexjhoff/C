//
//  prisoner.h
//  prisoner
//
//  Created by Alex Hoff on 1/28/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//


#ifndef postfix_Header_h
#define postfix_Header_h

#include <iostream>
#include <cassert>

using namespace std;

class Prisoner
{
public:
    /* Function: Constructors */
    Prisoner();
    /* Function: Destructor */
    ~Prisoner();
    void insert(const int&);
    void print();
    void move(int);
    void eliminate();
/*    class node
    {
    public:
        node(int, node*);
        int data;
        node* next;
    };  */
private:
    class node
    {
    public:
        node(int, node*);
        int data;
        node* next;
    };
    node *first, *temp;
};



//Default constructor
//Postcondition: Dummy node pointing back to itself
Prisoner::Prisoner()
{
	first = new node(0, NULL); //dummy
	first->next = first; // points back to dummy
	temp = first; // cursor on dummy
}

//Destructor
//Postcondition: All memory will be dealocated and the link list will be destroyed
Prisoner::~Prisoner()
{
	node* prev = first->next;
	node* next = prev->next;
	while( next != first) // while the next isnt the dummy
	{
		delete prev;
		prev = next;
		next = next->next;
	}
	delete first; // delete the dummy
}

// Adds the variable into the first spot of the linked list
// Precondition: Data is a number
// Postcondition: Node is at the head of the list with the prisoners
//        number stored in data
void Prisoner::insert(const int& var)
{
    //assert(isdigit(var) == 1);
    node* ptr;
    ptr = new node(var,first);  //this new node has data and points to first
    ptr->next = first->next;
    first->next = ptr;
}

//Displays the list of existing Prisoners
//Postcondition: Returns the Prisoners in the output
void Prisoner::print()
{
    temp = first->next;
	while(temp != first)
	{
		cout << "Prisoner #" << temp->data << endl;
		temp = temp->next;
    }
}

//Traverses through the prisoners
//Precondition: The int n must be greater than 0
//Postcondition: The temp will be set to the prisoner before
// the prisoner to be deleted
void Prisoner::move(int n)
{
    int i;
    for (i=0; i<n; i++){
        temp = temp->next;
        if(temp == first){
            temp = temp->next;
        }
    }
}

//Deletes the next node
//Postcondition: The node after temp is deleted and memory is deallocated
void Prisoner::eliminate()
{
    int output;
    node* ptr;
    if (temp->next == first) {
        temp = temp->next;
    }
    ptr = temp->next;
    output = ptr->data;
    temp->next = ptr->next;
    delete ptr;
    cout << "Prisoner #" << output << " has been deleted" << endl;
}

//Defines a node
//Preconditions: var must be a digit and dummy must be the first node in the list
//Postcondition: Node is created with data stored and is pointing to the dummy
Prisoner::node::node(int var, node* dummy)
{
	data = var;
	next = dummy;
}

#endif
