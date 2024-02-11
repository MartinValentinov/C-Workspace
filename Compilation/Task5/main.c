#include <stdio.h>
#include "math.h"

int main(void) {
  int num;
  printf("Enter a number: ");
  scanf("%d", &num);
  int result = factoriel(num);
  printf("%d", result);
  return 0;
}