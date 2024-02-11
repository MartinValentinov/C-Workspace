#include <stdio.h>
#include <string.h>
#include "transformation.h"

int main(void) {
  char test[100];
  printf("Enter a string:");
  scanf("%s", test);
  printf("%d", function(test));
  return 0;
}