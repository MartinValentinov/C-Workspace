#include "processes.h"
#include <string.h>
#include <stdio.h>

int arr[5];

struct Process processes[5];

int processcount = 0;

struct Process process;

static int nextprocessid(){
  static int id = 0;
  id++;
  if(id <= 5){
    return id;
  }
  else{
    return 0;
  }
}

int createnewprocess(char *name){
  static int i = 0;
  static int br = 0;
  br++;
  i++;
  strcpy(processes[i].name, name);
  process.ID = nextprocessid();
  arr[br] = process.ID;
  if(processcount <= 5){
    processcount ++;
    return process.ID;
  }
  else return 0;
}

int stopprocess(int number){
  int sorting_the_processes = 0;
  if(number > 0 && number <= processcount){
    number = arr[number];
    if(number != 0){
      strcpy(processes[number].name, "");
      for(int j = 1; j <= processcount; j++){
        if(strcmp(processes[j].name, "") == 0){
          sorting_the_processes = 1;
        }
        if(sorting_the_processes == 1){
          if(j+1 > processcount){
            strcpy(processes[j].name, "");
            arr[j] = 0;
          }
          else{
            strcpy(processes[j].name, processes[j+1].name);
            arr[j] = arr[j+1];
          }
        }
      }
    }  
  }
  processcount--;
}

void printprocess(){
  if(processcount != 0){
    for(int i = 1; i <= processcount; i++){
      if(strcmp(processes[i].name, "") != 0){
        printf("The name of the process is %s, with id: %d \n", processes[i].name, arr[i]);
      }
    }
  }
  else printf("There are no running processes!\n");
}