#include <stdio.h>
#include "mystrings.h"

int strlength(char* str){
  int count = 0;
  for(int i=0; str[i] != '\0'; i++)count ++;
  return count;
}

char strconcat(char str1[100], char* str2){
  int count=0;
  for(int i=0; str1[i] != '\0'; i++)count ++;
  for(int i=0; str2[i] != '\0'; i++){
    str1[count + i] = str2[i];
  }
  printf("%s\n", str1);
}

int strcompare(char* str1, char* str2){
  int result;
  int count1 = 0;
  int count2 = 0;
  for(int i=0; str1[i] != '\0'; i++)count1 ++;
  for(int i=0; str2[i] != '\0'; i++)count2 ++;
  for(int i=0; str1[i] != '\0'; i++){
    if(str2[i] == '\0'){
      break;
    }
    if(str1[i] == str2[i]){
      result = 0;
    }
    else if(str1[i] < str2[i]){
      result = -1;
      break;
    }
    else{
      result = 1;
      break;
    }
  }
  if(count2 > count1 && result == 0)result = -1;
  if(count1 > count2 && result == 0)result = 1;
  return result;
}