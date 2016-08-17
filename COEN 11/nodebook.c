#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20
#define NODE struct node


void insert (void);
int delete (char*);
void list (void);



struct node  //struct declarations
{
	char names[SIZE];
	char phone[SIZE];
	NODE *next;
};

NODE *head = NULL;



int main(void)
{
	int z;
	char id[SIZE];

	while(1)
	{
		printf("Welcome to Phone Book!\nChoose the corresponding number to:\n1  Create an entry\n2  Delete an entry\n3  List all entries\n4  Quit\n");
		scanf("%d", &z);
		switch(z)
		{
			case 1: //add an entry 
			{
				insert ();
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




void insert (void)
{
	char name[SIZE];
        char num[SIZE];
	NODE *p;
	NODE *q;
	NODE *temp;

	printf("Please enter a name and phone number:\n");
        	scanf ("%s", name);
                scanf ("%s", num);
        
		p = q = head;
		
		temp = (NODE*) malloc (sizeof (NODE));
		strcpy(temp->names, name);
		strcpy(temp->phone, num);

		if(head == NULL)
		{
			head = temp;
			temp->next = NULL;
                        printf("Your entry has been added!\n");
                        printf("\n");
                        return;

		}
		
	        while(p != NULL)
	        {
        	        if(strcmp(p->names, name) == 0)
        	        {
				printf("This name is already taken\n");
				return;
			}
			if(strcmp(p->names, name) > 0)
			{	
				if(q == p)
				{
					head = temp;
					temp->next = p;
					printf("Your entry has been added!\n");
                        	        printf("\n");
                        	        return;
				}
				else
				{
					temp->next = p;
					q->next = temp; 
					printf("Your entry has been added!\n");
					printf("\n");
					return;
				}
			}
			q = p;
			p = p->next;
		}
		
		if(p == NULL)
		{
			temp->next = NULL;
        	        q->next = temp;
        	        printf("Your entry has been added!\n");
        	        printf("\n");
        	        return;
		}
}


int delete (char*id)
{
	NODE *p;
	NODE *q;

	if(head == NULL)
	{
		printf("There are no entries\n");
		return;
	}
	p = q = head;

	while (p != NULL)
	{
		if(strcmp(p->names, id) == 0)
		{
			break;
		}
		q = p;
		p = p->next;
	}
	if(p == head)
		head = p->next;
	else
	{
		q->next = p->next;
	}
	if(p == NULL)
	{
		printf ("The entry you entered does not exist.\n");	
		return;
	}
	printf("Your entry has been deleted.\n");
	free(p);
	return;
}


void list (void)
{
	NODE *p;
		
	if(head == NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	
	printf("The names and numbers are:\n");
	p = head;
	while(p != NULL)
	{
		printf("%s	%s\n", p->names, p-> phone);
		p = p->next;
	}
	printf("\n");
	return;
}














