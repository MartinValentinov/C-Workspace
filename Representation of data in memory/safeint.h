#ifndef SAFEINT_H
#define SAFEINT_H

struct SafeResult {
  int value;
  char errorflag;
};

int safeadd(int fst_number, int snd_number);

int safesubtract(int fst_number, int snd_number);

int safemultiply(int fst_number, int snd_number);

int safedevide(int fst_number, int snd_number);

int safestrtoint(char *symbols);

#endif