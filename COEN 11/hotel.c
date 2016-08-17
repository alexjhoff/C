#include <stdio.h>
#include <string.h>
#define SIZE 10
#define SIZE2 20


int counter;
char rooms[SIZE][SIZE2];
int reserve (char*, int);
int cancel (char*);
void list (void);
char *ptr;
int num;
char name[SIZE2];
char id[SIZE2];

int main(void)

{

	int i;
	int z;
	counter = 0;

	 for(i=0;i<SIZE;i++)
                        strcpy(rooms[i], "\0");

	while(1)
	{
		printf("Enter 0 to reserve a room, 1 to cancel a reservation, 2 to list all reservations, and any other number to quit.\n");
		scanf ("%d", &z);
		switch(z)
		{
			case 0:
			{
				printf("Please enter your desired reservation name and your desired number of rooms to reserve:\n");
                                        scanf ("%s", name);
                                        scanf ("%d", &num);

				reserve (name,num);
				break;
			}
			case 1:
			{
				printf("Please enter your reservation name:\n");
                                        scanf ("%s",id);

				cancel (id);
				break;
			}
			case 2:
			{
				list ();
				break;
			}
			default:
			{
				printf("\n");
				return 1;
			}
		}
	}
}



int reserve (char*name,int num)
{
	int i;
	int j;
	int n;
	ptr = rooms[0];
				if(counter == SIZE)
                                        printf("All rooms are full\n");
                                else
                                {	
					for(j=0;j<SIZE;j++)
                                        {
						if(strcmp(rooms[j], name) == 0)
                                                {
     	                                           printf("Reservation name is taken. Please try again\n");
                                                    return;
                                                }
                                        }
                                        for(i=0;i<SIZE;i++)
                                        {
						if(strcmp(rooms[i], "\0") == 0)
                                                {
                                                        if(counter+num > SIZE)
							{
								num=SIZE-counter;
								printf("Not enough rooms available. Only %d rooms will be reserved\n", num);
							}
							for(n=0;n<num;n++)
							{
								strcpy(ptr,name);
								ptr+=SIZE2;
							}
                                                        counter+=num;
                                                        printf("%d rooms have been reserved\n", num);
                                                        break;
                                                }
						ptr+=SIZE2;
                                        }
                                }
	return;
}

int cancel (char*id)
{
	int i;
	int j;
	int z;
	int q;
	int a;
	char *w;
	char *n;
	int counter2 = 0;
	int counter3 = 0;
				if(counter == 0)
                                        printf("All rooms are empty\n");
                                else
                                {
                                        for(i=0;i<SIZE;i++)
                                        {
                                                if(strcmp(rooms[i], id) == 0)
                                                {
                                                        strcpy(rooms[i],"\0");
                                                        counter = counter-1;
							counter2++;
                                                }
                                        }
		
					for(j=0;j<SIZE;j++)
					{
						if(strcmp(rooms[j], "\0") == 0)
						{
							break;
						}
					}
					
					w = rooms[j+counter2];
					n = rooms[j];
					for(z=(j+counter2);z<SIZE;z++)
					{
						strcpy(n, w);
						strcpy(w, "\0");
						n += SIZE2;
					}
					for(q=(SIZE-counter2);q<SIZE;q++)
					{
						strcpy(rooms[q], "\0");
					}

					printf("Your reservations have been cancelled\n");
                                }
	return;
}

void list (void)
{
	int i;
				if(counter == 0)
                                        printf("All rooms are empty\n");
                                else
                                {
                                        for(i=0;i<SIZE;i++)
                                        {
                                               // if(strcmp(rooms[i], "\0") != 0)
                                                {
                                                        printf("Reserved room names:%s\n", rooms[i]);
                                                }
                                        }
                                }
	return;
}
