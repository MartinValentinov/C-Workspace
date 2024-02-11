#include <stdio.h>
#define MAX 100
#define DEBUG

void sort(int *arr, int arrlen){
    for(int i = 0; i < arrlen - 1; i ++){
        int ok = 1;
        for(int j = 0; j < arrlen - i - 1; j ++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                ok = 0;
            }
        }
        if(ok)break;
    }
}
void print(int *arr, int arrlen){
    sort(arr, arrlen);
    int sum = 0;
    printf("Elements with specific index:\n");
    for(int i = 1; i < arrlen; i ++){
        if(i % 3 == 0){
            printf("%d,", arr[i]);
            sum += arr[i];
        }
    }
  printf("\n");
  printf("Sum of elements:\n");
    printf("%d\n", sum);
}
int main()
{
    int n;
    do{
        printf("Enter how much numbers do you want:");
        scanf("%d", &n);
    }while(n < 0);
    int arr[MAX];
    for(int i = 0; i < n; i ++){
        printf("Enter a number:");
        scanf("%d", &arr[i]);
    }
    #ifdef DEBUG
    sort(arr, n);
    printf("Sorted array:\n");
    for(int i = 0; i < n; i ++){
        printf("%d,", arr[i]);
    }
    printf("\n");
    print(arr, n);
    #endif
    return 0;
}
