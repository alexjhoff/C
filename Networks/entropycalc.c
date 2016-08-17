#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define ALPHABETSIZE 256

int main(void)
{
  int i, k, counter = 0;
  double prob, entropy = 0;
  unsigned char buf[99];
  int fa[ALPHABETSIZE]={0};
  
  while(i=read(0, &buf, sizeof(buf))){
    for(k=0; k<i; k++){
      fa[buf[k]]++;	//steps through file buffer and records number of times it sees each byte
      counter++;
    }
  }
  
  for(i=0; i<ALPHABETSIZE; i++){
    if(fa[i]){
      prob = (double)fa[i]/(double)counter; //algs to calculate entropy from cisco document
      entropy += prob * log2(1/prob);
    }
  }
  printf("Entropy is %lf\n", entropy);
  return 0;
}
