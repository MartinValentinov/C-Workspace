#include <stdio.h>
#include <limits.h>

// Radix sort
// Radix Sort processes each digit of the number from the least significant to the most significant.
// When sorting by the first digit, it will be faster if the array given has only one digit numbers
// Also you don't need to find the amount of digits in the max element so that you start from there


void print(int arr[], int n) {
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("Arr[%d] is %d \n", i, arr[i]);
    }
}

int maxEl(int arr[], int n) {
    int max = arr[0];
    for(int i = 1; i < n; i ++){
        if(max < arr[i])
            max = arr[i];
    }
    return max;
}

void countSort(int arr[], int n, int curDig) {
    int count[10] = {0};
    int outcome[n];

    for(int i = 0; i < n; i ++) {
        count[(arr[i] / curDig) % 10] ++;
    }

    for(int i = 1; i < 10; i ++) {
        count[i] += count[i-1];
    }

    for(int i = n - 1; i >= 0; i --) {
        outcome[count[(arr[i] / curDig) % 10] - 1] = arr[i];
        count[(arr[i] / curDig) % 10] --;
    }

    for(int i = 0; i < n; i ++) {
        arr[i] = outcome[i];
    }
}

void radixSortR(int arr[], int n, int curDig, int max) {
    if (max / curDig > 0) {
        countSort(arr, n, curDig);
        radixSortR(arr, n, curDig * 10, max);
        printf("\nThe array after sorting it by the %d\n", curDig);
        print(arr, n);
    }
}

void radixSort(int arr[], int n) {
    if (n == 0) return;

    int negCount = 0;
    int posCount = 0;
    int if_int_min = 0;

    // Counting the amount of negative numbers

    for(int i = 0; i < n; i ++) {
        if(arr[i] < 0)
            negCount ++;
        else
            posCount ++;
    }

    // Creating the arrays that will hold the numbers

    int negArr[negCount];
    int posArr[posCount];

    negCount = 0;
    posCount = 0;

    // Turning the negative numbers positive to sort them and

    for(int i = 0; i < n; i++) {
        if(arr[i] == INT_MIN) {
            if_int_min += 1;
            arr[i] ++;
        }
        
        if(arr[i] < 0) {
            negArr[negCount ++] = -arr[i];
        }
        else {
            posArr[posCount ++] = arr[i];
        }
    }

    printf("\nNegative array before sorting:\n");
    print(negArr, negCount);
    printf("\nPositive array before sorting:\n");
    print(posArr, posCount);

    // Finding the max element
    
    int posMax = maxEl(posArr, posCount), negMax = maxEl(negArr, negCount);

    // Sorting the two arrays

    radixSortR(negArr, negCount, 1, negMax);
    radixSortR(posArr, posCount, 1, posMax);
    
    printf("\nNegative array after sorting:\n");
    print(negArr, negCount);
    printf("\nPositive array after sorting:\n");
    print(posArr, posCount);

    // Putting the arrays in the main array
    
    int index = 0;

    for(int i = negCount - 1; i >= 0; i --) {
        arr[index ++] = -negArr[i];
    }

    for(int i = 0; i < posCount; i ++) {
        arr[index ++] = posArr[i];
    }

    for(int i = 0; i < if_int_min; i ++) {
        arr[i] --;
    }

    printf("\nMain array after sorting:\n");

}

int main(void) {
    // Test 1 - small numbers
    int arr1[] = {32, -99, 15, 12, 11, -15, -9, 7, 23, -45};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("\nTest 1 (for small numbers):\n");

    radixSort(arr1, n1);
    print(arr1, n1);

    printf("\n");
    printf("\n");
    
    // Test 2 - big numbers
    int arr2[] = {2146483637, 2047483641, 2137483643, 2147283644, 2147481645, 2147473646, 2147433647, 2140483628, 2144483633, 2117483639};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("\nTest 2 (for big numbers):\n");

    radixSort(arr2, n2);
    print(arr2, n2);

    printf("\n");
    printf("\n");
    
    // Test 3 - combination of negative and positive
    int arr3[] = {987654321, -123456789, 2147483000, -2147483000, 345678912, 
                  -987654321, 1000000000, -1500000000, 2147483647, -2147483648};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("\nTest 3 (for combination of negative and positive numbers):\n");
    
    radixSort(arr3, n3);
    print(arr3, n3);

    printf("\n");
    printf("\n");

    // Test 4 - empty
    int arr4[] = {};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("\nTest 4 (for empty array):\n");

    radixSort(arr4, n4);
    print(arr4, n4);

    printf("\n");
    printf("\n");
    
    // Test 5 - reversed
    int arr5[] = {99, 45, 32, 23, 15, 12, 11, 7, -9, -15};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("\nTest 5 (for reversed array):\n");

    radixSort(arr5, n5);
    print(arr5, n5);

    printf("\n");
    printf("\n");
    
    // Test 6 - repeting
    int arr6[] = {32, 45, 32, 11, 45, 12, 12, 32, 45, 11};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);

    printf("\nTest 6 (for repeting numbers):\n");

    radixSort(arr6, n6);
    print(arr6, n6);

    printf("\n");
    printf("\n");
    
    // Test 7 - only negatives
    int arr7[] = {-32, -45, -11, -7, -99, -15, -23, -32, -45, -12};
    int n7 = sizeof(arr7) / sizeof(arr7[0]);

    printf("\nTest 7 (for only negatives):\n");

    radixSort(arr7, n7);
    print(arr7, n7);

    printf("\n");
    printf("\n");
    
    return 0;
}