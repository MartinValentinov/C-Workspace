#include <stdio.h>
#define MAX 5
#define ARR for(int i=0;i<MAX;i++){ \
scanf("%d",&arr[i]);}
#define PRINT for(int i=0;i<MAX;i++){ \
printf("%d",arr[i]);}
int main(void) {
  int arr[MAX];
  ARR
  PRINT
  return 0;
}
