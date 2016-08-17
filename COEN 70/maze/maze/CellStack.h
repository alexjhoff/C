//
//  CellStack.h
//  maze
//
//  Created by Alex Hoff on 3/10/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#ifndef maze_CellStack_h
#define maze_CellStack_h

//Charles Mulloy
//Alex Hoff
//Eric Beckmann

//COEN 70 2:15 Lab
//Lab 10

#include <assert.h>

class CellStack{
public:
	CellStack(){
		head = NULL;
		size = 0;
	}
    
	class  node{
	public:
		int data;
		node* next;
	};
    
	void push(int item){
		node* temp = new node;
		temp->data = item;
		temp->next = head;
		head = temp;
		size++;
	}
    
	int pop(void){
		assert(head != NULL);
		
		node* temp = head;
		head = head->next;
        
		int popthis = temp->data;
		delete temp;
        
		size--;
        
		return popthis;
	}
    
	
	int size;
    
private:
	node* head;
};

#endif
