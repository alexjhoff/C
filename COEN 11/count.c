#include <stdio.h>
#include <string.h>
#define SIZE 100

char string[SIZE];
int start(char*);
int count(char*);
int counter=0;
int upper=0;
int lower=0;
int digit=0;
int even=0;
int small=0;
int sum=0;

int main(void)
{
	printf("stuff\n");
	{
		while(scanf("%99s", string) == 1)
		{
			start (string);
			count (string);
		}
	}
	sum /= counter;

	printf("The total number of strings is: %d.\n", counter);
        printf("There are %d strings starting with an upper case letter.\n", upper);
        printf("There are %d strings starting with a lower case letter.\n", lower);
        printf("There are %d strings starting with a digit.\n", digit);
	printf("There are %d strings with an even size.\n", even);
        printf("There are %d strings with size between 3 to 5 characters\n", small);
        printf("The average size of the strings is %d.\n", sum);

	return;
}

int start(char*string)
{

	{	
		counter++;
		if(*string >= 'A' && *string <= 'Z')
			upper++;
		if(*string >= 'a' && *string <= 'z')
			lower++;
		if(*string >= '0' && *string <= '9')
			digit++;
	}

	return;
}

int count(char*string)
{
	int temp;

	{
		temp = strlen(string);
		sum += temp;
		if(temp%2==0)
			even++;
		if(temp >= 3 && temp <= 5)
			small++;
	}

	return;	
}
