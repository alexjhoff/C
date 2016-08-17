#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100


char *crypt (char *temp, int key);

int main (int argc, char *argv[])
{
	int i;
	int key;
	char temp[SIZE];
	char encrypt[SIZE];
	
	if (argc != 4)
	{
		printf("The file is not specified.\n");
		return 0;
	}
	FILE *fp1 = fopen (argv[2], "rb");
	FILE *fp2 = fopen (argv[3], "wb");
		
	if (fp1 == NULL || fp2 == NULL)
	{
		printf ("Cannot open file\n\n");
		return;
	}

	key = atoi(argv[1]);

	while (fread (temp, 1, SIZE, fp1)>0)
	{
		strcpy (temp, crypt(temp,key));
		fwrite (temp, 1, SIZE, fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return;
}

char *crypt (char *temp, int key)
{
	int i;
	while (temp[i] != '\0');
	{
		temp[i] ^= key;
		i++;
	}
	return temp;
}
