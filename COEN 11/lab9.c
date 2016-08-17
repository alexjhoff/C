#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 26
#define NODE struct node


void insert (char*, char*);
int delete (char*);
void list (void);
int letter(char*);
void read_file (char*);
void save_file (char*);
void read_binary (void);
void* save_binary (void *);

struct node  //struct declarations
{
	char names[SIZE];
	char phone[SIZE];
	NODE *next;
};

NODE *head = NULL;
NODE *array[SIZE];

pthread_mutex_t mutex;
pthread_t thr;

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("The file is not specified.\n");
		return 0;
	}
	else
		read_file (argv[1]);
	int i;
	int z;
	char name[SIZE], num[SIZE];
	char id[SIZE];
	char let[SIZE];
	FILE *fp_autosave = fopen ("temp.bin", "wb");

	
	pthread_mutex_init (&mutex, NULL);
	pthread_create (&thr, NULL, save_binary, argv[2]);

	while(1)
	{
		printf("Welcome to Phone Book!\nChoose the corresponding number to:\n\n1---Create an entry\n2---Delete an entry\n3---List all entries\n4---List a specific lettter\n5---List the binary file\n6---Quit\n");
		scanf("%d", &z);
		switch(z)
		
		{
			case 1: //add an entry 
			{
				pthread_mutex_lock(&mutex);
				printf ("Please enter the name and number of your entry.\n");
					scanf ("%s", name);
					scanf ("%s", num);
				insert (name, num);
				pthread_mutex_unlock(&mutex);
				break;
			}
			case 2:    //delete entry
			{	
				pthread_mutex_lock(&mutex);
				printf("Please enter the entry name you would like to delete:\n");
					scanf ("%s", id);
	
				delete (id);
				pthread_mutex_unlock(&mutex);
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
			case 5:	 //print binary file
			{
				pthread_mutex_lock(&mutex);
				read_binary();
				pthread_mutex_unlock(&mutex);
				break;
			}
			case 6:  //quit
			{
				fclose (fp_autosave);
				save_file (argv[1]);
				printf("\n");
				return 1;
			}
			default:
			{
				printf("Invalid option\n");
				break;
			}
		}
	}
}




void insert (char *name, char *num)
{
       	NODE *p;
	NODE *q;
	NODE *temp;
	int i;

		
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
			printf("%s\t\t%s\n", p->names, p-> phone);
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


void read_file (char *arg)
{
	int i;

	FILE *fp = fopen (arg, "r");

	if (fp == NULL)
	{
		printf ("Cannot open the file\n\n");
		return;
	}
	fseek (fp, 47, SEEK_SET);
	char name[SIZE], num[SIZE];
	
	
	
	while (fscanf (fp, "%s %s", name, num) ==  2)
	{
		insert (name, num);
	}
	close(fp);
	return;
}


void save_file (char* arg)
{
	FILE *fp = fopen (arg, "w");
	NODE *p;
	int i;

	fprintf (fp,"Names\t\tNumber\n");
	fprintf (fp,"--------------------------------\n");

	for(i=0;i<SIZE;i++)
	{
		p = array[i];

		while (p != NULL)
		{
			fprintf (fp, "%s		%s\n", p->names, p-> phone);
			p = p->next;	
		}
	}
	close (fp);
	return;
}

void* save_binary (void *temp)
{
	int i;
	NODE *p;

	FILE *fp;
	
	while(1)
        {
                sleep(5);
                pthread_mutex_lock (&mutex);
            	fp = fopen ("temp.bin", "wb");
		for (i=0;i<SIZE;i++)
                {
			p = array[i];
                        while (p != NULL)
                        {       
                                fwrite (p, 1, sizeof(NODE), fp);
                        	p = p->next;
			}
                }
		fclose (fp);
                pthread_mutex_unlock (&mutex);
		//pthread_join (thr,NULL);
        }
}

void read_binary (void)
{
	int i;
	NODE temp;

	FILE *fp = fopen("temp.bin", "rb");	
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		fclose(fp);
		return;
	}
	while (fread (&temp, 1, sizeof(NODE), fp))
	{
		printf ("%s\t%s\n", temp.names, temp.phone);
	}
	fclose (fp);
	return;
}
