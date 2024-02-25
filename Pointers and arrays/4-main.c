#include <stdio.h>

int arr2d(int arr[][4], int rows) {
    for(int i = 0; i < rows; i++)
    {
        printf("\n");
        for(int j = 0; j <= rows; j++)
        {
            printf("%-3d ", *(*(arr + i) + j));
        }
    }
}

int main()
{
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    arr2d(arr, 3);
}