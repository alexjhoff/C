# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <cassert>
# include "deque.h"


struct node {
    int data;
    struct node *next;
    struct node *prev;
};


/*
 * Function: createDeque
 *
 * Description: Creates a new doubly ended deque setting
 *		the next and previous pointers to head.
 *
 *		O(1)
 */

Deque::Deque(){	
    count = 0;
    head = new struct node;
	
    head->next = head;
    head->prev = head;
}

/*
 * Function: destroyDeque
 *
 * Description: Completley destroys the deque by going
 *		down the deque deleting each node and then
 *		deleting the head.
 *
 *		O(n)
 */


Deque::~Deque(){
    struct node *np, *next;
	
    np = head;
	
    do {
		next = np->next;
		delete(np);
		np = next;
    } while (np != head);
}

/*
 * Function: addFirst
 *
 * Description: Adds a node to the first node in the deque
 *		and sets the next and prev pointers.
 *
 *		O(1)
 */


void Deque::addFirst(int x){
    struct node *np, *sentinel;
	
    np = new struct node;
    np->data = x;
	
    count ++;
    sentinel = head;
	
    np->prev = sentinel;
    np->next = sentinel->next;
	
    sentinel->next->prev = np;
    sentinel->next = np;
}

/*
 * Function: addLast
 *
 * Description: Adds a node to the last node in the deque
 *		and sets the next and prev pointers.
 *
 *		O(1)
 */


void Deque::addLast(int x){
    struct node *np, *sentinel;
	
	
    np = new struct node;
    np->data = x;
	
    sentinel = head;
    count ++;
	
    np->prev = sentinel->prev;
    np->next = sentinel;
	
    sentinel->prev->next = np;
    sentinel->prev = np;
}

/*
 * Function: removeFirst
 *
 * Description: Removes the first node in the deque and returns its data.
 *
 *		O(1)
 */


int Deque::removeFirst(){
    int x;
    struct node *np, *sentinel;
	
	
    assert(count > 0);
    sentinel = head;
    count --;
	
    np = sentinel->next;
    sentinel->next = np->next;
    np->next->prev = sentinel;
	
    x = np->data;
    delete(np);
    return x;
}

/*
 * Function: removeLast
 *
 * Description: Removes the last node in the deque and returns the its data.
 *
 *		O(1)
 */


int Deque::removeLast(){
    int x;
    struct node *np, *sentinel;
	
	
    assert(count > 0);
    sentinel = head;
    count --;
	
    np = sentinel->prev;
    sentinel->prev = np->prev;
    np->prev->next = sentinel;
	
    x = np->data;
    delete(np);
    return x;
}

/*
 * Function: getFirst
 *
 * Description: Returns the first value in the deque.
 *
 *		O(1)
 */


int Deque::getFirst(){
    assert(count > 0);
    return head->next->data;
}

/*
 * Function: getLast
 *
 * Description: Returns the last value in the deque.
 *
 *		O(1)
 */


int Deque::getLast(){
    assert(count > 0);
    return head->prev->data;
}

/*
 * Function: numItems
 *
 * Description: Reterns the number of items in the deque.
 *
 *		O(1)
 */


int Deque::size(){
    return count;
}
