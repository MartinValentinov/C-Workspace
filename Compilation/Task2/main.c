#include <stdio.h>

int main(void) {
  int a, b;
  int result;
  printf("Enter a number: ");
  scanf("%d", &a);
  printf("Enter a number: ");
  scanf("%d", &b);
  for(int i=1; i>0; i++){
    if(i%a == 0 && i%b == 0){
      result = i;
      break;
    }
  }
  printf("Result -> %d", result);
  return 0;
}