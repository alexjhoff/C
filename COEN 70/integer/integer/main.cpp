//
//  main.cpp
//  integer
//
//  Created by Alex Hoff on 1/16/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//
//  Coen 70 MTW 11:45
//  Homework Assignment 2: Integer

#include "Header.h"
#include <iostream>
#include <locale>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

Integer::Integer()
{
    int integer1 = -1;
    int identifier = -1;
    char new_sign;

    while (identifier >= 0) {
        cout << "Please enter an a sign '+' or '-' of the integer" << endl << "Sign:";
        cin >> new_sign;
        if (strcmp(new_sign, "+") == 1) {
            identifier = 1;
        }
        if (strcmp(new_sign, "-") == 1) {
            identifier = 0;
        }
    }
    while (integer1 < 0){
        cout << "Please enter an integer" << endl << "Integer:";
        cin >> integer1;
        cout << endl;
    }
    set_array(int identifier, int integer1);
}


/*
 class node
 {
 typedef node * ptr = new node;
 
 node* init_head;
 node* init_tail;
 node* head;
 node* current;
 node* tail;
 node* next = current -> link();
 init_head = (linkedlist->first());
 head = init_head;
 current = head;
 while(next!=NULL)
 {
 
 current = current -> next;
 //once loop reaches end of list, terminate because next node is null
 
 }
 }
 
 class linkedlist
 {
 
 }
 }
 */


void Integer::set_array(int identifier,int new_integer)
{
    bool *sign;
    int* digit;
    int new_digit;
    int i=1, n=0;

    while(n <= 0){
        if (new_integer < (10^i)) {
            n = i;
        }
        i++;
    }
    
    digit = int array[n];
    digit = &identifier;
    digit++;
    
    
    for(i=0;i<n;i++) {
        new_digit = new_integer % 10;
        digit = &new_digit;
        new_integer /= 10;
        digit++;
    }
}

void Integer::get_array()
{
    
    
    delete p;
}


int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

/*
std::operator ostream & os (std::ostream & os, const & linkedlist)
{
    
}
*/
