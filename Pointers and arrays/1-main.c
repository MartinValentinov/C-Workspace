#include <stdio.h>

int find_strlen(char str[])
{
    int len = 0;
    for(int i = 0; *(str + i) != '\0'; i++)
        len++;
    return len;
}

int main(void)
{
    char  str[] = "Hello";
    int len;
    len = find_strlen(str);
    printf("The length of the entered string is %d\n", len);
    return 0;
}