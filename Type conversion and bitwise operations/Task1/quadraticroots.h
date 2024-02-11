#ifndef QUADRATICROOTS_H
#define QUADRATICROOTS_H

struct  QuadraticRootsResult{
  long double x1;
  long double x2;
  char norealroods;
  char everyx;
};

long double findroots(long double a, long double b, long double c);

#endif