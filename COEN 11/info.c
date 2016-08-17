#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20


int counter;
void insert (void);
int delete (char*);
void list (void);

union mystatus
{
	 char school[SIZE];
         float salary;
         int retirement;

};


struct info  //struct declarations
{
	char names[SIZE];
	int ages;
	union mystatus status;
};

struct info information[SIZE];



int main(void)
{

	int i;
	int z;
	int x;
	char id[SIZE];
	counter = 0;

	struct info *p;   //basic struct call
		p = information;

	for(i=0;i<SIZE;i++,p++)
	{
		strcpy(p->names, "\0");
	}

	while(1)
	{
		printf("Welcome to Info Book!\nChoose the corresponding number to:\n1  Create an entry\n2  Delete an entry\n3  List all entries\n4  Quit\n");
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
	int i;
	char name[SIZE];
        char sch[SIZE];
        int sal;
        int ret;
	int age;

	struct info *p;
		p = information;


	printf("Please enter your name and age:\n");
        	scanf ("%s", name);
                scanf ("%d", &age);
        
	        for(i=0;i<SIZE;i++,p++)
	        {
        	        if(strcmp(p->names, "\0") == 0)
        	        {
	                      strcpy(p->names,name);
         	              p->ages = age;
			      counter++;	

			      if(age <= 21)
                   	      {
                        	      printf("Please enter the name of your school:\n");
                        		      scanf ("%s", sch);
					      strcpy(information[i].status.school, sch);
			      }
                	      else if(age > 21 && age <65)
               		      {       
                       		      printf("Please enter your salary per month:\n");
                                	      scanf ("%d", &sal);
					      information[i].status.salary = sal;
                    	      }
                  	      else
                  	      {       
                  	              printf("Please enter your year of retirement:\n");
                  	                      scanf ("%d", &ret);
					      information[i].status.retirement = ret;
                  	      }
			      printf("Your entry has been added\n");
			      break;
			}
		}
		return;
}


int delete (char*id)
{
	int i;
	struct info *p;
		p = information;

	if(counter == 0)
		printf("There are no entries\n");
	else
	{
		for(i=0;i<SIZE;i++,p++)
		{
			if(strcmp(p->names, id) == 0)
			{
				*p = information[counter-1];
				counter = counter-1;
			}
		}
		printf("Your entry has been deleted\n");
	}
	return;
}


void list (void)
{
	int i;
	struct info *p;
		p = information;

	if(counter == 0)
		printf("You have no entries\n");
	else
	{
		for(i=0;i<counter;i++,p++)
		{
			if(p->ages <= 21)
				printf("Name: %s Age: %d School: %s\n", p->names, p->ages, information[i].status.school);
			else if(p->ages > 21 && p->ages < 65)
				printf("Name: %s Age: %d Salary: %f\n", p->names, p->ages, information[i].status.salary);
			else
				printf("Name: %s Age: %d Year of Retirement: %d\n", p->names, p->ages, information[i].status.retirement);
		}
	}
	return;
}














