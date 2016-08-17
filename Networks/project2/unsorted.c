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

int findElement(SET *sp, char *elt) //returns position of the element 0(n)
{
	int i;
	
	assert (sp != NULL);
	
	for (i=0; i<sp->count; i++)
		if (strcmp (sp->elts[i], elt) == 0)
			return i;
	return -1;
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
	assert (sp != NULL);
	
	if (findElement(sp, elt)<0)
		return false;
	return true;
}


bool addElement(SET *sp, char *elt) //add elt to the set pointed by sp, and return whether the set changed 0(1)
{
	assert (sp != NULL);
	
	if (sp->count == sp->length )
		return false;

	if (hasElement(sp, elt)==true) //use has element function to check for duplicate string
		
		return false;
	
	elt = strdup(elt);
	
	assert(elt != NULL);
		
	sp->elts[sp->count] = elt;
	
	sp->count++;
	return true;
}

bool removeElement(SET *sp, char *elt) //remove elt from the set pointed by sp, and return whether the set changed 0(1)
{
	int x;

	assert (sp != NULL);
	
	x = findElement(sp, elt);
	
	if (x==-1)
		return false;
	
	strcpy (sp->elts[x], sp->elts[--sp->count]);
	
	free(sp->elts[sp->count]);

	return true;
}