#include "init.h"

NODE *head = (NODE *)NULL;

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
                        case 5:  //print binary file
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


