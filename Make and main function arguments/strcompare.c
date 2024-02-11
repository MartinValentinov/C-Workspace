#include <stdio.h>
#include "mystrings.h"

int main(void){
  char str1[100];
  char str2[100];
  int error = 0;
  do{
    printf("Enter the first string you want to compare:\n ");
    scanf("%s", str1);
    for(int i=0; str1[i] != '\0'; i++){
      if((str1[i] >= 48 && str1[i] <= 57) || (str1[i] >= 65 && str1[i] <= 90) || (str1[i] >= 97 && str1[i] <= 122))error = 0;
      else error = 1;
    }
    if(error == 1)printf("Invalid string. Please try again.\n");
  }while(error == 1);
  do{
    printf("Enter the second string you want to compare:\n ");
    scanf("%s", str2);
    for(int i=0; str2[i] != '\0'; i++){
      if((str2[i] >= 48 && str2[i] <= 57) || (str2[i] >= 65 && str2[i] <= 90) || (str2[i] >= 97 && str2[i] <= 122))error = 0;
      else error = 1;
    }
    if(error == 1)printf("Invalid string. Please try again.\n");
  }while(error == 1);
  int result_compare = strcompare(str1, str2);
  printf("%d\n", result_compare);
}