#include <stdio.h>

char strhalf(char str[], char **p){
    char *strptr = str;
    int strlen = 0;
    while(*strptr != 0)
    {
        strlen++;
        strptr++;
    }
    *p = str + strlen / 2;
}

int main()
{
    char str[6] = "Hello!";
    char *ptr;
    strhalf(str, &ptr);
    printf("Half of string: %s", ptr);
}