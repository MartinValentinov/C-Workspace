#include <stdio.h>
#define SWAP(x,y,TYPE) TYPE c=x; \
x=y; \
y=c;
#define SORT(ARRAY, SIZE, TYPE, COMPARE) \
for(int i=1;i<SIZE;i++){ \
  for(int j=0;j<SIZE-i;j++){ \
    if(ARRAY[j] COMPARE ARRAY[j+1]){ \
      SWAP(ARRAY[j], ARRAY[j+1], TYPE); \
    } \
  } \
}
int main(void) {
  int n;
  printf("Enter how much numbers do you want:\n");
  scanf("%d",&n);
  int array[n];
  printf("Enter a number:\n");
  for(int i=0;i<n;i++)scanf("%d",&array[i]);
  SORT(array, n, int, >);
  printf("Sorted numbers:\n");
  for(int i=0;i<n;i++)printf("%d\n",array[i]);
    return 0;
}