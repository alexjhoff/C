/* Main File
 
 This file initializes and implements a deque. This deque is
 a doubly-ended queue, so items can be added or removed
 from either side.
 
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "deque.h"
#define NODE struct node

struct node{
	int x;
	NODE *next;
	NODE *prev;
};

/* defines the struct*/
struct deque{
	int count;
	NODE *head;
};

/*Allocates memory for a new deque and returns pointer
 to a new deque*/
DEQUE *createDeque(void){
	struct deque *dp;
	//allocate memory and make sure dp is not empty
	dp = malloc(sizeof(struct deque));
	assert (dp != NULL);
	dp->count=0;
	dp->head = malloc(sizeof(struct node));
	assert (dp->head != NULL);
	//sets next and prev to head
	dp->head->next = dp->head;
	dp->head->prev = dp->head;
	return dp;
}

/* deallocate memory associated with the deque pointed by dp*/
void destroyDeque(DEQUE *dp){
	assert (dp != NULL);
	//while loop takes each node next to head and deletes it
	while (dp->count != 0) {
		NODE *temp;
		temp = dp->head->next;
		dp->head->next = temp->next;
		dp->count--;
		free(temp);
		}
	free(dp);
	return;
}

/* returns the number of items in the deque pointed to by dp*/
int numItems(DEQUE *dp){
	assert (dp != NULL);
	return dp->count;
}

/* Allocates memory for and then adds x as the last item
 in the deque pointed by dp */
void addFirst(DEQUE *dp, int x){
	NODE *sp;
	assert (dp != NULL);
	//adds new node after dummy and adds x to it
	sp = malloc(sizeof(struct node));
	sp->next = dp->head->next;
	sp->prev = dp->head;
	sp->next->prev = sp;
	dp->head->next = sp;
	dp->count++;
	sp->x = x;
	return;
}

/* add x as the last item in the deque pointed to by dp */
void addLast(DEQUE *dp, int x){
	NODE *sp;
	assert (dp != NULL);
	//adds new node before dummy and adds x
	sp = malloc(sizeof(struct node));
	sp->prev = dp->head->prev;
	sp->next = dp->head;
	sp->prev->next = sp;
	dp->head->prev = sp;
	dp->count++;
	sp->x = x;
	return;
}

/* remove and return the first item in the deque pointed
 to by dp*/
int removeFirst(DEQUE *dp){
	NODE *temp;
	int x;
	//the deque cannot be empty
	assert (dp != NULL && dp->count > 0);
	//sets temp equal to first item and then deletes
	temp = dp->head->next;
	temp->next->prev = dp->head;
	dp->head->next = temp->next;
	dp->count--;
	x = temp->x;
	free(temp);
	return x;
}

/* remove and return the last item in the deque pointed
 to by dp*/
int removeLast(DEQUE *dp){
	NODE *temp;
	int x;
	//the deque cannot be empty
	assert (dp != NULL && dp->count > 0);
	//sets temp equal to last item and then deletes
	temp = dp->head->prev;
	temp->prev->next = dp->head;
	dp->head->prev = temp->prev;
	dp->count--;
	x = temp->x;
	free(temp);
	return x;
}	

/*return the first item in the deque pointed to by dp*/
int getFirst(DEQUE *dp){
	assert (dp != NULL && dp->count > 0);
	return dp->head->next->x;
}
/*return the last item in the deque pointed to by dp*/
int getLast(DEQUE *dp){
	assert (dp != NULL && dp->count > 0);
	return dp->head->prev->x;
}
