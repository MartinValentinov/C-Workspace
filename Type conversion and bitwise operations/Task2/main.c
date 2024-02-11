#include <stdio.h>
#include <string.h>

int main(void) {
  int room;
  
  unsigned char light = 0;
  unsigned char lights = 0;
  
  unsigned char room1 = 1<<0;
  unsigned char room2 = 1<<1;
  unsigned char room3 = 1<<2;
  unsigned char room4 = 1<<3;
  unsigned char room5 = 1<<4;
  unsigned char room6 = 1<<5;
  unsigned char room7 = 1<<6;
  unsigned char room8 = 1<<7;
  
  char command[100];
  printf("Chose an option:\n");
  printf("Switch lights, Print state or Stop if you want to stop the program\n");
  do{
    printf("Enter a command: ");
    gets(command);
    if(strcmp(command, "Switch lights") == 0){
      do{
        printf("Enter a room: ");
        scanf("%d", &room);
      }
      while(room < 1 || room > 8);
      
      lights = lights ^ (1 << (room-1));
      
    }
    if(strcmp(command, "Print state") == 0){
      printf("The lights are on in rooms: ");
      if(room1 == (lights & room1)) printf("1 ");
      if(room2 == (lights & room2)) printf("2 ");
      if(room3 == (lights & room3)) printf("3 ");
      if(room4 == (lights & room4)) printf("4 ");
      if(room5 == (lights & room5)) printf("5 ");
      if(room6 == (lights & room6)) printf("6 ");
      if(room7 == (lights & room7)) printf("7 ");
      if(room8 == (lights & room8)) printf("8 ");
      printf("\n");
    }
    if(strcmp(command, "Stop") == 0)break;
  }while(1);
}