#include <stdio.h>
#include "mystrings.h"

int main(void){
  char str1[100];
  char str2[100];
  int error = 0;
  int count_elements1 = 0;
  int count_elements2 = 0;
  do{
    count_elements1 = 0;
    printf("Enter the string to which you want to add another string:\n ");
    scanf("%s", str1);
    for(int i=0; str1[i] != '\0'; i++){
      if((str1[i] >= 48 && str1[i] <= 57) || (str1[i] >= 65 && str1[i] <= 90) || (str1[i] >= 97 && str1[i] <= 122))error = 0;
      else error = 1;
    }
    if(error == 1)printf("Invalid string. Please try again.\n");
    for(int i=0; str1[i] != '\0'; i++)count_elements1 ++;
    if(count_elements1 > 50)printf("Your string should not be over 50 symbols. Please try again. ");
  }while(error == 1 || count_elements1 > 50);
  do{
    count_elements2 = 0;
    printf("Enter the string you want to add: \n");
    scanf("%s", str2);
    for(int i=0; str2[i] != '\0'; i++){
      if((str2[i] >= 48 && str2[i] <= 57) || (str2[i] >= 65 && str2[i] <= 90) || (str2[i] >= 97 && str2[i] <= 122))error = 0;
      else error = 1;
    }
    if(error == 1)printf("Invalid string. Please try again.\n");
    for(int i=0; str2[i] != '\0'; i++)count_elements2 ++;
    if(count_elements2 > 50)printf("Your string should not be over 50 symbols. Please try again. ");
  }while(error == 1 || count_elements2 > 50);
  strconcat(str1, str2);
}