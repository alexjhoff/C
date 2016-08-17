#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20

int rec (char*, char*);

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf ("The file is not specified.\n");
		return 0;
	}

	char buffer[SIZE];
	char new[SIZE];

	FILE *fp = fopen (argv[1], "r");
	FILE *fp1 = fopen (argv[2], "w");

	if (fp == NULL)
	{
		printf ("Cannot open the file\n\n");
		return;
	}

	while (fgets (buffer, SIZE, fp) > 0)
	{
		rec (buffer, buffer);
		fprintf (fp1, "%s", buffer);
	}
	printf("Your file has been reversed\n");
	close(fp);
	close(fp1);
	return;
}

int rec (char *old, char *new)
{
	int i;
	char temp;

	if(*old == '\n' || *old == '\0')
		return 0;
	
	temp = *old;

	i = rec (old + 1, new);

	new[i] = temp;
	return i+1;
}
