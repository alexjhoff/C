#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
  int i;
  int bytes = 1048576;

  
  srand((unsigned int) time(NULL));
  for(i=0; i<bytes-1; i++){		
    printf("%c", (rand()%256)); //assign random bytes to each char 
  }
  return 0;
}
