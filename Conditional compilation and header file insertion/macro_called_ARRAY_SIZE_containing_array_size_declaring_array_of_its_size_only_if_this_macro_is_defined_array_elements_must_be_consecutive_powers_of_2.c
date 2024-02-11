#include <stdio.h>
#define ARRAY_SIZE 5


int main(void) {
  #if defined ARRAY_SIZE && ARRAY_SIZE > 0 && ARRAY_SIZE < 11
  int arr[ARRAY_SIZE];
  for(int i = 0; i < ARRAY_SIZE; i ++){
    arr[i] = 1;
    for(int j = 0; j < i; j ++){
      arr[i] = arr[i] * 2;
    }
    printf("%d\n", arr[i]);
  }
  #else
  printf("No array size supported by the application was entered!");
  #endif
  return 0;
}