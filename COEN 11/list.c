#include "init.h"


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

