/*Main File
 
 This file contains all of the implimentation for the the interface.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

struct set{ //defines the structure SET:
	int count;
	int length;
	char* *elts;
};



SET *createSet(int maxElts) //returns a pointer to a new set with a maximum capacity of maxElts 0(1)
{
	SET *sp;
	
	sp=malloc(sizeof(SET));
	
	assert (sp != NULL);
	
	sp -> count = 0;
	sp -> length = maxElts;
	sp -> elts = malloc (sizeof(char*)*maxElts);
	assert (sp -> elts != NULL);
	return sp;
}

int numElements(SET *sp) //return the number of elements in the set pointed to by sp 0(1)
{	
	assert(sp != NULL);
	
	return sp->count;
}

int findElement(SET *sp, char *elt, bool *found) //returns position of the element or returns the position where it can be inserted 0(1)
{
	int x,lo=0,hi=sp->count-1,mid;
	
	assert (sp != NULL);
	
	while (lo <= hi) {
		mid = (lo+hi)/2;
		
		x = strcmp (elt, sp->elts[mid]);
		
		if (x > 0) {
			lo = mid + 1;
		}
		else if (x < 0) {
			hi = mid - 1;
		}
		else {
			*found = true;
			return mid;
		}

	}
	*found = false;
	return lo;
}

void destroySet(SET *sp) //deallocate memory associated with the set pointed by sp 0(n)
{
	int i;
	
	assert(sp != NULL);
	
	for(i=0; i<sp->count; i++)
		free (sp->elts[i]);
	free(sp->elts);
	free(sp);
	return;
}

bool hasElement(SET *sp, char *elt) //return wheter elt is a member of the set pointed to by sp 0(1)
{
	bool pool;
	
	assert (sp != NULL);
	
	findElement(sp, elt, &pool);
	
	if(pool)
		return true;
	return false;
}

bool addElement(SET *sp, char *elt) //add elt to the set pointed by sp, and return whether the set changed 0(n)
{
	bool pool;
	int x,i;
	
	assert (sp != NULL);
	
	if (sp->count == sp->length)
		return false;
	
	x = findElement(sp, elt, &pool);
	
	if (pool) //if bool is true, a duplicate string exists
		return false;
	
	elt = strdup(elt);
	
	assert(elt != NULL);
	
	for (i=sp->count; i>x; i--) {
		sp->elts[i] = sp->elts[i-1];
	}
	
	sp->elts[x] = elt;
	sp->count++;
	return true;
}

bool removeElement(SET *sp, char *elt) //remove elt from the set pointed by sp, and return whether the set changed 0(n)
{
	int x,i;
	bool pool;
	
	assert (sp != NULL);
	
	x = findElement(sp, elt, &pool);
	
	if (pool){
		free(sp->elts[x]);
		
		for (i=x+1; i<sp->count; i++) {
			sp->elts[i-1] = sp->elts[i];
		}
		sp->count--;
		return true;
	}
	return false;
}
