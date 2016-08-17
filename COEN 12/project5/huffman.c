/*
 * File: huffman.c
 *
 *
 * Description:
 *
 *
 */

# include <assert.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "tree.h"
# include "pack.h"
# include <ctype.h>
#define NODE struct tree
#define END 256
#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)

static int count;
static struct tree *heap[END+1];
static struct tree *nodes[END+1];

void insert(struct tree *);
struct tree *delete(void);
void print(struct tree *);

/*
 * Function:	Main
 *
 * Description: Reads file and counts the number occurances of
 *		each character. Then adds the number of occurances to
 *		each characters respective node and then inserts the 
 * 		data into a priority queue. The program then goes down
 * 		the priority queue and deletes and combines the two
 *		trees untill there is only one tree left. Then the
 * 		program goes down the tree assigning a binary number
 * 		to each specific character and prints it out.
 *
 *		O(n)
 */

int main(int argc, char *argv[]){
	int c, total, counts[END];
	/*opens the file and checks to make sure its not empty*/
	assert(argc != 1);
	FILE *fp = fopen (argv[1], "r");
	assert(fp != NULL);
	/* counts how many times each character occurs */
	while ((c = getc(fp))!=EOF) {
		counts[c]++;
	}
	/* adds occurance count to node and inserts it*/
	for (c=0; c<END; c++) {
		if (counts[c] != 0) {
			nodes[c]=createTree(counts[c],NULL,NULL);
			insert(nodes[c]);
		}
	}
	insert(nodes[END]=createTree(0,NULL,NULL));
	
	struct tree *tr1, *tr2;
	/* deletes two trees and combines them into one tree*/
	while (count > 1) {
		tr1 = delete();
		tr2 = delete();
		total = getData(tr1)+getData(tr2);
		insert(createTree(total,tr2,tr1));
	}
	assert(count == getData(heap[0]));
	/*prints out the characters and then the binary value*/
	for (c=0; c<END; c++) {
		if (isprint(c)){
			printf("'%c' : %d", c, counts[c]);
		}
		else {
			printf("'%o' : %d", c, counts[c]);
		}
		print(nodes[c]);
		printf("\n");
	}	
	pack(argv[1],argv[2],nodes);
	return 0;
}

/*
 * Function:	insert
 *
 * Description:	Finds the index of the slot that the tree is to
 * 	be inserted in and then adds it to the heap.
 *
 *		O(1)
 */

void insert(struct tree *tr){
	int index = count++;
	/*finds the index by taking the index until the tree is no longer
	larger than the index*/ 
	while(index > 0 && getData(tr) < getData(heap[p(index)])){
		heap[index] = heap[p(index)];
		index = p(index);
	}
	heap[index] = tr;
	return;
}

/*
 * Function:	Delete
 *
 * Description: Takes the minimum value which is always the root and then
 *  	goes down the tree checking which child is the smallest and copies
 * 	it to the parent.
 *
 *		O(n)
 */

struct tree *delete(void){
	int i = 0, focus; struct tree *tr;

	tr = heap[i];
	/*checks if the left child is less than count so the loop can stop
	while still checking every leaf*/
	while (l(i) < count){
		focus=l(i);
		/*checks if the right child is the minimum*/
		if (getData(heap[l(i)]) > getData(heap[r(i)]) && r(i)<count){
			focus = r(i);
		}
		/*copies the child to the parent and then decrements
		i to check the child*/
		if (getData(heap[focus]) < getData(heap[count-1])){
			heap[i] = heap[focus];
			i = focus;
		}
	}
	heap[i]=heap[--count];
	return tr;
}

/*
 * Function:	Print
 *
 * Description:Recursively goes down the tree printing either a 0 for
 * the left and 1 for the right.
 */
		   
void print(struct tree *tr){
	/*makes sure the tree isnt empty*/
	if(getParent(tr) == NULL)
		return;
	print(getParent(tr));
	if (getLeft(getParent(tr)) == tr) {
		printf("0");
	}
	else {
		printf("1");
	}
	return;
}
