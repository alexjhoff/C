#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

int dvr;
int quo;
int dvd;
int ans;
int divide (int, int);

int main(void)
{
	srand((int)time(NULL));
	int x;
	int i;
	int counter = 0;
	
	for(i=0;i<SIZE;i++)
	{
		dvr = rand()%12+1;
       		quo = rand()%13;
       		dvd = dvr*quo;

		printf("What is the answer to %d / %d?\n", dvd, dvr);

			scanf ("%d", &ans);

		x = divide (ans,quo);
		
		if(x == 1)
			counter++;
	}
	printf("Your final score is %d0 out of 100\n", counter);
	
	return;
}


int divide (int ans, int quo)
{
	if(ans == quo)
	{
		printf("You are correct! Try another one!\n");
		return 1;
	}
	else
	{
		printf("Your answer is incorrect. The correct answer is %d.\n", quo);
		return 0;
	}
}
