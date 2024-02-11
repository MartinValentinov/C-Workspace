#include <stdio.h>
#define COMMAND(NAME, TYPE) TYPE##_##NAME##_command
#define DEFINE_COMMAND(NAME, TYPE)void TYPE##_##NAME##_command(void)
DEFINE_COMMAND(quit, external){printf("Test number 1\n");}
DEFINE_COMMAND(second, external){printf("Test number 2");}

int main(void){
  external_quit_command();
  external_second_command();
}