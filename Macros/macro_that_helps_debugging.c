#include <stdio.h>
#define DEBUG(x) printf(#x"\n"); \
printf("%d",__LINE__); \
printf("%s\n"__FILE__);
int main(void) {
  int k=5;
  DEBUG(k)
}
