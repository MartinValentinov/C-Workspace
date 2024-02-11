#include <stdio.h>

#define SQUARE(A, B) (A + B) * (A + B)

int main(void) {
  int a, b;
  printf("Enter a number: ");
  scanf("%d", &a);
  printf("Enter a number: ");
  scanf("%d", &b);
  int result = SQUARE(a, b);
  printf("Result -> %d", result);
  return 0;
}