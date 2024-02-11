#include <stdio.h>

int main(void) {
  int n;
  do{
    printf("Enter how much numbers do you want:");
    scanf("%d", &n);
  }while(n < 0);
  int arr[n];
  for(int i = 0; i < n; i ++){
    printf("Enter a number:");
    scanf("%d", &arr[i]);
  }
  #ifdef _WIN32
  for(int i = 0; i < n - 1; i ++){
    int ok = 1;
    for(int j = 0; j < n - i -1; j ++){
      if(arr[j] > arr[j + 1]){
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        ok = 0;
      }
    }
    if(ok)break;
  }
  #elif defined __linux__
  for(int i = 0; i < n; i ++){
    int min = arr[i];
    int mini = i;
    for(int k = i + 1; k < n; k ++){
      if(arr[k] < min){
        min = arr[k];
        mini = k;
      }
    } 
    arr[mini] = arr[i];
    arr[i] = min;
  }
  #elif defined __APPLE__
  for (int i = 1; i < n; i++) {
      int temp = arr[i];
      int j = i - 1;
      while (j >= 0 && arr[j] > temp) {
          arr[j + 1] = arr[j];
          j --;
      }
      arr[j + 1] = temp;
  }
  #else
  for(int i = 0; i < n/2; i ++){
    int temp = arr[i];
    arr[i] = arr[n - i - 1];
    arr[n - i - 1] = temp;
  }
  #endif
  for(int i = 0; i < n; i ++){
    printf("%d\n", arr[i]);
  }
  return 0;
}