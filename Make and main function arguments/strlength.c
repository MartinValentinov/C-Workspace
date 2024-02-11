#include <stdio.h>
#include "mystrings.h"

int main(void){
  char str[100];
  int error = 0;
  do{
    printf("Enter the string that you want the length of:\n ");
    scanf("%s", str);
    for(int i=0; str[i] != '\0'; i++){
      if((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))error = 0;
      else error = 1;
    }
    if(error == 1)printf("Invalid string. Please try again.\n");
  }while(error == 1);
  int result_length = strlength(str);
  printf("%d\n", result_length);
}