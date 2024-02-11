#include "quadraticroots.h"
#include <stdio.h>
#include <math.h>

struct QuadraticRootsResult result;

long double findroots(long double a, long double b, long double c){
  long double discriminant = b*b - 4*a*c;
  result.norealroods = '0';
  result.everyx = '0';
  if(a==0){
    if(b==0){
      if(c==0){
        result.x1 = result.x2;
        result.norealroods = '0';
        result.everyx = '1';
      }
      else result.norealroods = '1';
    }
    else{
      result.x1 = result.x2 = -c/b; 
    }
  }
  else{
    if(discriminant > 0){
      result.x1 = (-b - sqrtl(discriminant)) / (2*a);
      result.x2 = (-b + sqrtl(discriminant)) / (2*a);
    }
    else if(discriminant == 0){
      result.x1 = result.x2 = -b / (2*a);
    }
    else result.norealroods = '1';
  }
  if(result.norealroods == '0'){
    if(result.everyx == '1'){
      printf("Every x is answer!\n");
    }
    else{
      if(result.x1 == result.x2){
        printf("The answer is: %Lf\n", result.x1);
      }
      else{
        printf("The first answer: %Lf\n", result.x1);
        printf("The second answer: %Lf\n", result.x2);
      }
    }
  }
  if(result.norealroods == '1'){
    printf("No real answer!\n");
  }
}