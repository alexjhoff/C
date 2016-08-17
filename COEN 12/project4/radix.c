/* Main File
 *
 * This file uses a radix search to sort numbered inputs.
 * This file uses an array of deques and a single deque.
 * This deque is a doubly-ended queue, so items can be 
 * added or removed from either side.
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "deque.h"
#define NODE struct node


/*Funtion: Main
 *
 * Description: Radix search uses a final deque and an array of
 * deques called buckets. This search takes the least siginificant
 * digit of each number and puts the element into its respective
 * bucket based on its least significant digit. Once all numbers
 * have been placed into the buckets, the program will copy the
 * numbers back into the final deque in order. Then the program
 * repeats this process on the next most significant digit untill
 * all digits have been processed.
 *
 */
int main(void){
	int i, j, newElt, max, maxDigit, temp, placement, divisor=1;
	
	/*initializes the array of deques(buckets) and the final deque
	 will be the final sorted list*/
	DEQUE *array[10];
	DEQUE *final;
	/*allocate and return pointer to deques*/
	for(i=0;i<10; i++)
		array[i] = createDeque();
	final = createDeque();
	/*While loop scans all elements and inserts them into
	 the final deque*/
	while (scanf("%d", &newElt) == 1){
		//check if element is less than 0
		if (newElt < 0) {
			printf("Element is less than zero:\n");
			return 0;
		}//check if element is maximum
		if (newElt > max) {
			max = newElt;
		}
		addLast(final, newElt);
	}
	/*finds the max digits from the max number*/
	maxDigit = ceil(log(max+1)/log(10));
	/*for loop implements the radix search*/
	for (i=0; i<maxDigit; i++) {
		/*takes each element from the final deque into
		 their respective buckets*/
		while (numItems(final) > 0) {
			temp = removeFirst(final);
			placement = ((temp/divisor) % 10);
			//adds the elements to the last space in the bucket
			addLast(array[placement], temp);
		}
		/*this loop takes all sorted elements and puts them
		 into the final deque*/
		for (j=0; j<10; j++){
			while (numItems(array[j]) > 0){
				temp = removeFirst(array[j]);
				addLast(final, temp);
			}
		}
		divisor *= 10;
	}
	
	//prints out the final deque which is now sorted
	printf("The sorted numbers are:\n");
	while (numItems(final) > 0)
		printf("%d\n", removeFirst(final));
	return 1;
}