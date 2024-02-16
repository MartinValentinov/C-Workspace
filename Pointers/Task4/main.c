#include <stdio.h>

int compareasc(const void * const a, const void * const b){
    if(*(int*)a < *(int*)b){
        return -1;
    }
    if(*(int*)a > *(int*)b){
        return 1;
    }
    if(*(int*)a == *(int*)b){
        return 0;
    }
}

int comparedesc(const void * const a, const void * const b){
    if(*(int*)a < *(int*)b){
        return 1;
    }
    if(*(int*)a > *(int*)b){
        return -1;
    }
    if(*(int*)a == *(int*)b){
        return 0;
    }
}

int main(void){
    int a = 7;
    int b = 7;
    printf("Compareasc -> %d, comparedesc -> %d", compareasc(&a, &b), comparedesc(&a, &b));
}