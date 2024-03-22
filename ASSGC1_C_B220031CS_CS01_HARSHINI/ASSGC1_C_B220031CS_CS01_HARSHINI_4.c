#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void linearProbe(int arr[], int size, int arrsize) {
    int HT[size];
    int collisions = 0;
    for (int i = 0; i < size; i++) {
        HT[i] = -1;
    }
    for (int i = 0; i < arrsize; i++) {
        int index = arr[i] % size;
        if (HT[index] == -1) {
            HT[index] = arr[i];
        } else {
            while (HT[index] != -1) {
                collisions++;
                index = (1 + index) % size;
            }
            HT[index] = arr[i];
        }
        printf("%d ", index);
    }
    printf("\n%d", collisions);
  return;
}

void quadraticProbe(int arr[], int size, int arrsize) {
    int HT[size];
    int collisions = 0;
    for (int i = 0; i < size; i++) {
        HT[i] = -1;
    }
    for (int i = 0; i < arrsize; i++) {
        int j=0;
        int index = (arr[i]+j*j) % size;
        if (HT[index] == -1) {
            HT[index] = arr[i];
        } else {
            while (HT[index] != -1) {
                collisions++;
                j++;
                index = (arr[i] + j*j) % size;
            }
            HT[index] = arr[i];
        }
        printf("%d ", index);
    }
    printf("\n%d", collisions);
  return;
}

int prime(int size){
    int num = size - 1;
    while (num >= 2) {
        int flag = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            return num;
        }
        num--;
    }
    return 2; 
}

int dhfunction(int k, int size, int i){
    int hone = k % size;
    int r = prime(size);
    int htwo = r - (k % r);
    int sum = hone + (i * htwo);
    return sum % size;
}

void doubleHashing(int arr[], int size, int arrsize){
    int HT[size];
    int collisions = 0;
    for (int i = 0; i < size; i++) {
        HT[i] = -1;
    }

    for (int i = 0; i < arrsize; i++) {
        int j = 0;
        int index = dhfunction(arr[i], size, j);
        while (HT[index] != -1) {
            collisions++;
            index = dhfunction(arr[i], size, ++j);
        }
        HT[index] = arr[i];
        printf("%d ", index); 
    }
    printf("\n%d", collisions);
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();  
    char str[1000];
    fgets(str, sizeof(str), stdin);

    int arr[n];
    int count = 0;
    char *token = strtok(str, " ");
    while (token != NULL && count < n) {
        arr[count++] = atoi(token);
        token = strtok(NULL, " ");
    }
    linearProbe(arr, n, count);
    printf("\n");
    quadraticProbe(arr, n, count);
    printf("\n");
    doubleHashing(arr, n, count);
    return 0;
}
