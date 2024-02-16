#include <stdio.h>
#include <string.h>

int main(void){
    char string[255];
    printf("Enter a string: ");
    fgets(string, 255, stdin); 
    char * p = strchr(string, '\n'); 
    if(p != NULL){ 
        *p = '\0';  
    } 
    puts(string);
    puts("!");
    return 0;
}