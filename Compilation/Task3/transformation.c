#include <stdio.h>
#include <string.h>
#include "transformation.h"
int function(char* symbols){
  struct transformation transform;
  int working = 1;
  for(int i=0; symbols[i] != '\0'; i++) {
    if(symbols[i] < 48 || symbols[i] > 57){
      transform.result = 0;
      strcpy(transform.error, "Invalid input string");
      working = 0;
      break;
    }
  }
  if(working == 1){
    int num = 0;
    for(int i=0; symbols[i] != '\0'; i++){
      num = num*10 + (symbols[i]-48);
    }
    transform.result = num;
    strcpy(transform.error, "\0");
  }
  printf("Result -> %ld, String -> %s", transform.result, transform.error);
  return 0;
}