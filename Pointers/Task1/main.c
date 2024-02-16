#include <stdio.h>

int main(void){
    double first_one;
    double second_one;
    printf("Enter the first number: ");
    scanf("%lf", &first_one);
    printf("Enter the second number: ");
    scanf("%lf", &second_one);
    double * pnt1 = &first_one;
    double * pnt2 = &second_one;
    printf("The adress of the first one is: %p\n", pnt1);
    printf("The value of the first one is: %lf\n", *pnt1);
    printf("The adress of the second one is: %p\n", pnt2);
    printf("The value of the second one is: %lf\n", *pnt2);
    return 0;
}