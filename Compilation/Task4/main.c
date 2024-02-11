#include <stdio.h>

int main(void){
  long arr[5] = {1, 2, 3, 4, 5};
  for(int i=0; i<5; i++){
    int c = pow(arr[i], 4);
    arr[i] = c;
    c = 0;
  }
  for(int i=0; i<5; i++){
    printf("%ld\n", arr[i]);
  }
  return 0;
}