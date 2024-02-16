#include <stdio.h>

int compareasc(const void * const a, const void * const b){
    if(*(int*)a < *(int*)b){
        return -1;
    }
    if(*(int*)a > *(int*)b){
        return 1;
    }
    return 0;
}

int comparedesc(const void * const a, const void * const b){
    if(*(int*)a < *(int*)b){
        return 1;
    }
    if(*(int*)a > *(int*)b){
        return -1;
    }
    return 0;
}

int swap(void * a, void * b){
    int temp = *(int*)a;
    *(int*)a = *(int*)b;
    *(int*)b = temp;
}

int bubblesort(int arr[], int arrlen, int (* compare)(const void * const, const void * const), int (* swapelements)(void * , void *)){
    for(int i = 0; i < arrlen - 1; i++){
        for(int j = 0; j < arrlen - i - 1; j++){
            if(compare(&arr[j], &arr[j+1]) == 1){
                swapelements(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main(void) {
    int arr[5] = {3, 2, 5, 4, 1};
    bubblesort(arr, 5, compareasc, swap);
    printf("With compareasc:\n");
    for(int i = 0; i<5; i++){
        printf("%d, ", arr[i]);
    }
    printf("\n");
    bubblesort(arr, 5, comparedesc, swap);
    printf("With comparedesc:\n");
    for(int i = 0; i<5; i++){
        printf("%d, ", arr[i]);
    }
    return 0;
}