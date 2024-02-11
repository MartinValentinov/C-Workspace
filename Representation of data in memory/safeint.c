#include "safeint.h"
#include <stdio.h>

struct SafeResult safe;

int safeadd(int fst_number, int snd_number) {
  int value = fst_number + snd_number;
  safe.errorflag = '0';
  if (fst_number >= 0 && snd_number >= 0) {
    if (value < 0) {
      safe.errorflag = '1';
    }
  }
  if (safe.errorflag == '0')
    return value;
}

int safesubtract(int fst_number, int snd_number) {
  int value = fst_number - snd_number;
  safe.errorflag = '0';
  if (fst_number < 0 && snd_number < 0) {
    if (value > 0) {
      safe.errorflag = '1';
    }
  }
  if (safe.errorflag == '0')
    return value;
}

int safemultiply(int fst_number, int snd_number) {
  int value = fst_number * snd_number;
  safe.errorflag = '0';
  if ((fst_number > 0 && snd_number < 0) ||
      (fst_number < 0 && snd_number > 0)) {
    if (value > 0) {
      safe.errorflag = '1';
    }
  } else if (fst_number > 0 && snd_number > 0) {
    if (value < 0) {
      safe.errorflag = '1';
    }
  } else if (fst_number < 0 && snd_number < 0) {
    if (value < 0) {
      safe.errorflag = '1';
    }
  }
  if (safe.errorflag == '0')
    return value;
}

int safedevide(int fst_number, int snd_number) {
  int value = fst_number / snd_number;
  safe.errorflag = '0';
  if (fst_number % snd_number != 0) {
    safe.errorflag = '1';
  }
  if (fst_number < snd_number) {
    safe.errorflag = '1';
  }
  if (snd_number == 0) {
    safe.errorflag = '1';
  }
  if (safe.errorflag == '0')
    return value;
}
int safestrtoint(char *symbols) {
  int positive = 0;
  safe.errorflag = '0';
  safe.value = 0;
  int count = 0;
  for (int i = 0; symbols[i] != '\0'; i++) {
    if (symbols[i] < 48 && symbols[i] > 57) {
      safe.errorflag = '1';
      break;
    }
    count ++;
    safe.value = safeadd(safe.value, symbols[i] - 48);
    if(safe.value == 0){
      safe.errorflag = '1';
      break;
    }
    int check_num = safe.value;
    safe.value = safemultiply(safe.value, 10);
    if(check_num == safe.value){
      safe.errorflag = '1';
      break;
    }
    check_num = 0;
    if(safe.value > 0){
      positive = 1;
    }
  }
  int final_num = safe.value;
  int num_count = 0;
  while(final_num != 0){
    num_count ++;
    final_num /= 10;
  }
  while (num_count != count){
    safe.value /= 10;
    num_count --;
  }
  if(safe.value < 0 && positive == 1){
    safe.errorflag = '1';
  }
  if(safe.value > 0 && positive == 0){
    safe.errorflag = '1';
  }
  if (safe.errorflag == '0') {
    return safe.value;
  } else
    printf("This operation overflowed or underflowed!\n");
}