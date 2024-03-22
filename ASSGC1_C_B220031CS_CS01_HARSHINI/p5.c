#include <stdio.h>
#include <stdlib.h>
#define maxsize 200

typedef struct{
    int key;
    int isOccupied;
} hashtable;

int hashIndex(int k,int size){
    return k%size;
}

void distinctWindow(int arr[],int n, int k){
    int distinctcount=0;
    hashtable table[maxsize]={0};
    int result[n-k+1];
    for(int i=0;i<k;i++){
        int index=hashIndex(arr[i],n);
        if (table[index].isOccupied==0)
            distinctcount++;
        table[index].key=arr[i];
        table[index].isOccupied++;
    }
    result[0]=distinctcount;
    for(int i=k;i<n;i++){
        int index=hashIndex(arr[i-k],n);
        table[index].isOccupied--;
        if (table[index].isOccupied==0)
            distinctcount--;

        index=hashIndex(arr[i],n);
        if (table[index].isOccupied==0)
            distinctcount++;
        table[index].key=arr[i];
        table[index].isOccupied++;
        result[i-k+1]=distinctcount;
    }
    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return;

}

int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    distinctWindow(arr, n, k);
    return 1;
}