#include <stdio.h>

int swap(void *a, void *b) {
  int temp = *(int *)a;
  *(int *)a = *(int *)b;
  *(int *)b = temp;
}

int main(void) {
  int a = 7;
  int b = 5;
  swap(&a, &b);
  printf("First number - %d, second number - %d", a, b);
  return 0;
}