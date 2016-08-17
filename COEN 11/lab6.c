#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 26
#define NODE struct node


void insert (void);
int delete (char*);
void list (void);
int letter(char*);



struct node  //struct declarations
{
	char names[SIZE];
	char phone[SIZE];
	NODE *next;
};

NODE *head = NULL;
NODE *array[SIZE];


int main(void)
{
	int z;
	char id[SIZE];
	char let[SIZE];

	while(1)
	{
		printf("Welcome to Phone Book!\nChoose the corresponding number to:\n1  Create an entry\n2  Delete an entry\n3  List all entries\n4  List a specific lettter\n5 Quit\n");
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
			case 4:    //list by letter
			{
				printf("Please enter the letter of the names you would like to list:\n");
					scanf ("%s", let);
				letter(let);
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
	int i;


	printf("Please enter a name and phone number:\n");
        	scanf ("%s", name);
                scanf ("%s", num);
		
	temp = (NODE*) malloc (sizeof (NODE));
	strcpy(temp->names, name);
	strcpy(temp->phone, num);
	temp->next = NULL;

	i=name[0]-'a';
	head = array[i];
	p = q = head;

	        while(p != NULL)
	        {
        	        if(strcmp(p->names, name) == 0)
        	        {
				printf("This name is already taken\n");
				return;
			}
			if(strcmp(p->names, name) > 0)
			{
				break;
			}
			q = p;
			p = p->next;
		}
		
		if(p == array[i])
		{
			temp->next = array[i];
			array[i] = temp;
			printf("Your entry has been added\n");
			return;
		}

		if(p == NULL)
		{
        	        q->next = temp;
        	        printf("Your entry has been added!\n");
        	        printf("\n");
        	        return;
		}
		
		q->next = temp;
		temp->next = p;
                printf("Your entry has been added!\n");
                printf("\n");
                return;

}


int delete (char* id)
{
	NODE *p;
	NODE *q;
	int i;

	i=id[0]-'a';
	head=array[i];
	p = q = head;
	
	if(head == NULL)
	{
		printf("There are no entries\n");
		return;
	}

	while (p != NULL)
	{
		if(strcmp(p->names, id) == 0)
		{
			break;
		}
		q = p;
		p = p->next;
	}

	if(p == NULL)
        {
                printf ("The entry you entered does not exist.\n");
                return;
        }

	if(p == array[i])
	{
		array[i] = p->next;
		printf("Your entry has been deleted.\n");
		free(p);
		return;
	}
	
	q->next = p->next;
	
	printf("Your entry has been deleted.\n");
	free(p);
	return;
}


void list (void)
{
	NODE *p;
	int i;
	int counter;

	for(i=0;i<SIZE;i++)
	{
		head = array[i];
		
		if(head == NULL)
		{
			counter++;
			if(counter == 26)
			{
				printf("The list is empty.\n");
				return;
			}
		}
	}
	
	printf("The names and numbers are:\n");
	for(i=0;i<SIZE;i++)
	{
		head = array[i];
		
		p = head;
		while(p != NULL)
		{
			printf("%s	%s\n", p->names, p-> phone);
			p = p->next;
		}
	}
	printf("\n");
	return;
}



int letter (char*let)
{
	NODE *p;
	int i;

	i=let[0]-'a';
	head = array[i];

	if(head == NULL)
        {
                printf("The list is empty.\n");
                return;
        }

        printf("The names and numbers are:\n");
        p = head;
        while(p != NULL)
        {
        	printf("%s      %s\n", p->names, p-> phone);
                p = p->next;
        }
	
	printf("\n");
	return;
}








