#include "init.h"


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
                        fprintf (fp, "%s                %s\n", p->names, p-> phone);
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

