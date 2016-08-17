/*Main File
 
 This file contains all of the implimentation for the the interface.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

/*defines the structure SET:*/
struct set{
	int count;
	int length;
	char* *elts;
	char *flags;
};


/*returns a pointer to a new empty set with a maximum capacity of maxElts
 while also allocating memory for the elts and flags array  O(n)*/
SET *createSet(int maxElts){
	SET *sp;
	int i;
	
	sp=malloc(sizeof(SET));
	assert (sp != NULL);
	
	sp -> count = 0;
	sp -> length = maxElts;
	//allocates memory
	sp -> elts = malloc (sizeof(char*)*maxElts);
	assert (sp -> elts != NULL);
	
	//allocates memory
	sp->flags = malloc (sizeof(char)*maxElts);
	assert (sp->flags != NULL);
	
	//flags are all empty
	for (i=0; i < sp->length-1; i++) {
		sp->flags[i] = EMPTY;
	}
	
	return sp;
}

/*deallocate memory associated with the set pointed by sp O(n)*/
void destroySet(SET *sp){
	int i;
	
	assert(sp != NULL);
	
	//frees all filled elements
	for(i=0; i<sp->length-1; i++) {
		if (sp->flags[i] == FILLED) {
			free(sp->elts[i]);
		}
		//all elements are empty
		sp->flags[i] = EMPTY;
	}
	free(sp);
	return;
	
}

/*creates and returns an unsigned hash value of the string O(1)*/
static unsigned hashString(char *s){
	unsigned hash = 0;
	
	while (*s != '\0') {
		//hash value
		hash = 31 * hash + *s ++;
	}
	return hash;
}

/*uses a hash function to search and return position of the element 
or returns the position where it can be inserted O(n)[worst]/O(1)[best]*/
static int findElement(SET *sp, char *elt, bool *found){ 
	int i,x,y,z;
	
	assert (sp != NULL);
	
	//creates hash value of element
	x = hashString(elt)%sp->length;
	z = -1;
	
	//position in the array
	for (i=0; i<sp->length-1; i++) {
		y = (x+i)%sp->length;
		
		//if empty, the string is not in the array
		if (sp->flags[y] == EMPTY) {
			*found = false;
			//checks for earlier deleted slot
			if(z != -1)
				return z;
			return y;
		}
		if (sp->flags[y] == FILLED) {
			//checks if strings are the same and returns its position
			if (strcmp(elt, sp->elts[y]) == 0) {
				*found = true;
				return y;
			}
		}
		else {
			if (z == -1) {
				//z = first deleted slot
				z = y;
			}
		}

	}
	//if elt is not found returns first deleted slot or first empty slot
	*found = false;
	if(z != -1)
		return z;
	return y;
}

/*return wheter elt is a member of the set pointed to by sp O(n)[worst]/O(1)[best]*/
bool hasElement(SET *sp, char *elt){
	bool pool;
	
	assert (sp != NULL && elt != NULL);
	
	findElement(sp, elt, &pool);
	
	//if the element is found pool will be true
	if(pool)
		return true;
	return false;	
}

/*return the number of elements in the set pointed to by sp O(1)*/
int numElements(SET *sp){
	assert(sp != NULL);
	
	return sp->count;	
}

/*add elt to the set pointed by sp, and return whether the set changed O(n)[worst]/O(1)[best]*/
bool addElement(SET *sp, char *elt){
	bool found;
	int x;
	
	assert (sp != NULL && elt != NULL);
	
	if (sp->count == sp->length)
		return false;
	
	//position of string
	x = findElement(sp, elt, &found);
	
	//if bool is true, a duplicate string exists
	if (found)
		return false;
	
	elt = strdup(elt);
	
	//checks for empty string
	assert(elt != NULL);
	
	//adds element
	sp->elts[x] = elt;
	sp->flags[x] = FILLED;
	sp->count++;
	return true;
	
}

/*remove elt from the set pointed by sp, and return whether the set changed O(n)[worst]/O(1)[best]*/
bool removeElement(SET *sp, char *elt){
	bool found;
	int locn;
	
	assert(sp != NULL && elt != NULL);
	//returns location of element to be deleted
	locn = findElement(sp, elt, &found);
	
	//return false if element is not found in the array
	if(!found)
		return false;
	
	//deletes element
	sp->flags[locn] = DELETED;
	sp->count--;
	free(sp->elts[locn]);
	return true;
}
