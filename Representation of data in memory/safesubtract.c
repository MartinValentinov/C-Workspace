#include "safeint.h"
#include <stdio.h>

int main(int argc, char **argv) {
  int fst_number = safestrtoint(argv[1]);
  int snd_number = safestrtoint(argv[2]);
  int result = safesubtract(fst_number, snd_number);
  printf("%d", result);
  return 0;
}
