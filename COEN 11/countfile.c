#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100

int main(int argc, char *argv[])
{

	char word[SIZE];
	int counter=0;
	FILE *fp;
	
	if (argc <= 1)	//Check if argument is specified
	{
		printf ("The file is not specified.\n");
		return 1;
	}
	else
	{
		fp = fopen (argv[1], "r");

		if (fp == NULL)
		{
			printf ("Cannot open the file\n");
			return 1;
		}

		while (fscanf (fp, "%s", word) == 1)	//count each time a string is scanned
		{
			counter++;
		}
	}
	printf ("%d total words.\n", counter);
	fclose (fp);
	return 1;
}
