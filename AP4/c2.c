#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int i;
  int a[10];
  for (i = 0; i < 9; i++) // NAO ATRIBUI O VALOR DE I PARA O ÚLTIMO ELEMENTO DO VETOR
    a[i] = i;
    
  for (i = 0; i < 10; i++){
    printf("%d ", a[i]);
  }
  printf("\n");
  return 0;
}


