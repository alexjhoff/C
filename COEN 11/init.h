#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 26
#define NODE struct node

struct node  //struct declarations
{
        char names[SIZE];
        char phone[SIZE];
        NODE *next;
};

extern NODE *head;
extern NODE *array[SIZE];

extern pthread_mutex_t mutex;
extern pthread_t thr;

void insert (char*, char*);
int delete (char*);
void list (void);
int letter(char*);
void read_file (char*);
void save_file (char*);
void read_binary (void);
void* save_binary (void *);

