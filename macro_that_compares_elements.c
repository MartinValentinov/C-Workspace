#include <stdio.h>
#define COMPARE(x,y) if(x>y)printf("A is greater"); \
else if(x==y)printf("A is equal to B"); \
else printf("B is greater");
int main(void)
{
 int a=5,b=9;
  COMPARE(a, b);
  return 0;
}
