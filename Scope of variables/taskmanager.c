#include "processes.h"
#include <stdio.h>

int main(void){
  int option;
  int exit = 0;
  int count = 1;
  printf("Chose an option:\n");
  printf("'1' to create a process\n");
  printf("'2' to print all processes\n");
  printf("'3' to stop a process\n");
  printf("'4' to exit the program\n");
  do{
    printf("Enter the number of the option you want ");
    scanf("%d", &option);
    switch(option){
      case 1:
      {
        char name[30];
        printf("Enter a name for the new process ");
        scanf("%s", name);
        if(count > 5){
          printf("Limit reached! You need to stop a process if you want to create another one!\n");
        }
        else createnewprocess(name);
        count ++;
        break;
      }
      case 2:{
        printprocess();
        break;
      }
      case 3:{
        int number;
        printf("Enter the number of the process you want to stop ");
        scanf("%d", &number);
        stopprocess(number);
        break;
      }
      case 4:{
        exit = 1;
        break;
      }
    }
  }while(exit != 1);
}