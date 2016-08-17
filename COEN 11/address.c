#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20


int counter;
char name[SIZE];
char  num[SIZE];
int insert (char*, char*);
int delete (char*);
int duplicate (char*, char*);
void list (void);
char id[SIZE];

struct addres  //struct declarations
{
	char names[SIZE];
	char numbers[SIZE];
};
struct address address[SIZE];


int main(void)
{

	int i;
	int z;
	int x;
	counter = 0;

	struct address *p;   //basic struct call
		p = address;

	for(i=0;i<SIZE;i++,p++)
	{
		strcpy(p->names, "\0");
		strcpy(p->numbers, "\0");
	}

	while(1)
	{
		printf("Welcome to Address Book!\nChoose the corresponding number to:\n1  Create an entry\n2  Delete an entry\n3  List all entries\n4  Quit\n");
		scanf("%d", &z);
		switch(z)
		{
			case 1: //add an entry 
			{
				printf("Please enter the Name and Number for your new entry:\n");
					scanf ("%s", name);
					scanf ("%s", num);
				
				x = duplicate (name,num);	
				if(x == 1)
					insert (name,num);
				break;
			}
			case 2:    //delete entry
			{
				printf("Please enter the entry name you would like to delete:\n");
					scanf ("%s", id);
	
				delete (id);
				break;
			}
			case 3:   //show the entries
			{
				list ();
				break;
			}
			default:  //quit
			{
				printf("\n");
				return 1;
			}
		}
	}
}


int duplicate (char*name, char*num)
{
	int i;
	struct address *p;
		p = address;

	for(i=0;i<SIZE;i++,p++)
	{
		if(strcmp(p->names, name) == 0)
		{
			printf("This entry name already exists\n");
			return 0;
		}
		if(strcmp(p->numbers, num) == 0)
		{
			printf("This entry number already exists\n");
			return 0;
		}
	}
	return 1;
}



int insert (char*name, char*num)
{
	int i;
	struct address *p;
		p = address;

	for(i=0;i<SIZE;i++,p++)
	{
		if(strcmp(p->names, "\0") == 0)
		{
			strcpy(p->names,name);
			strcpy(p->numbers,num);
			counter++;
			printf("Your entry has been added\n");
			break;
		}
	}
	return;
}


int delete (char*id)
{
	int i;
	struct address *p;
		p = address;

	if(counter == 0)
		printf("There are no entries\n");
	else
	{
		for(i=0;i<SIZE;i++,p++)
		{
			if(strcmp(p->names, id) == 0)
			{
				counter = counter-1;
				strcpy(p->names, address[counter].names);
				strcpy(p->numbers, address[counter].numbers);
				strcpy(address[counter].names, "\0");
				strcpy(address[counter].numbers, "\0");
				printf("%d\n", counter);
			}
		}
		printf("Your entry has been deleted\n");
	}
	return;
}


void list (void)
{
	int i;
	struct address *p;
		p = address;

	if(counter == 0)
		printf("You have no entries\n");
	else
	{
		for(i=0;i<SIZE;i++,p++)
		{
			printf("Names: %s  Numbers: %s\n", p->names, p->numbers);
		}
	}
	return;
}














