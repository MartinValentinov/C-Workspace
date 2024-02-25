#include <stdio.h>

int swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int arr[], int arrlen, int (*swap)(int *, int *))
{
    for(int i = 0; i < arrlen - 1; i++)
    {
        for(int j = 0; j < arrlen - i - 1; j++)
        {
            if(*(arr + j) > *(arr + j + 1))
            {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

int main()
{
    int arr[5] = {4, 2, 1, 5, 3};
    bubblesort(arr, 5, swap);
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", *(arr + i));
    }
    return 0;
}