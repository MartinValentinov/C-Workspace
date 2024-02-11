#include <stdio.h>
#define SWAP(x,y,TYPE) TYPE c=x; \
x=y; \
y=c;
int main(void) {
  int a=8, b=10;
  SWAP(a ,b, int);
    printf("a=%d b=%d",a, b);
}