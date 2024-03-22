#include <stdio.h>
#include <stdlib.h>
#define maxSize 100

typedef struct{
    int key;
    int isOccupied;
} hashtable;

int hashIndex(int k,int size){
    return k%size;
}

int distinctWindow(int arr[], int n, int k){
    hashtable table[maxSize]={0};
    int distinctcount=0;
    int result[n-k+1];
    for (int i = 0; i < k; i++){
        int index=hashIndex(arr[i],n);
        if(table[index].isOccupied==0){
            distinctcount++;}
        table[index].key=arr[i];
        table[index].isOccupied++;
    }
    result[0]=distinctcount;
    for (int i=k; i<n; i++){
        int index=hashIndex(arr[i-k],n);
        table[index].isOccupied--;
        if (table[index].isOccupied==0){
            distinctcount--;
        }
        index= hashIndex(arr[i],n);
        if (table[index].isOccupied==0){
            distinctcount++;
        }
        table[index].key=arr[i];
        table[index].isOccupied++;

        result[i-k+1]=distinctcount;
    }
    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return distinctcount;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    distinctWindow(arr, n, k);
    return 1;
}











/*
#define MAX_SIZE 100

// Hash table structure to store counts of integers
typedef struct {
    int key;
    int count;
} HashTable;

int hash(int key, int size) {
    return key % size;
}

int count_distinct_in_windows(int arr[], int N, int K) {
    // Initialize a hash table to store counts of integers
    HashTable table[MAX_SIZE] = {0};
    
    // Initialize a variable to store the count of distinct integers
    int distinct_count = 0;
    
    // Initialize a result array to store counts of distinct integers in each window
    int result[N - K + 1];
    
    // Process the first window
    for (int i = 0; i < K; i++) {
        int index = hash(arr[i], MAX_SIZE);
        if (table[index].count == 0) {
            distinct_count++;
        }
        table[index].key = arr[i];
        table[index].count++;
    }
    result[0] = distinct_count;
    
    // Process the remaining windows
    for (int i = K; i < N; i++) {
        // Remove the first element of the previous window
        int index = hash(arr[i - K], MAX_SIZE);
        table[index].count--;
        if (table[index].count == 0) {
            distinct_count--;
        }
        
        // Add the current element to the hash table
        index = hash(arr[i], MAX_SIZE);
        if (table[index].count == 0) {
            distinct_count++;
        }
        table[index].key = arr[i];
        table[index].count++;
        
        result[i - K + 1] = distinct_count;
    }
    
    // Print the counts of distinct integers in each window
    for (int i = 0; i < N - K + 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int N, K;
    
    // Read input size N and window size K
    scanf("%d %d", &N, &K);
    
    // Read input array
    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Find count of distinct integers in all windows of size K
    count_distinct_in_windows(arr, N, K);
    
    return 0;
}
*/