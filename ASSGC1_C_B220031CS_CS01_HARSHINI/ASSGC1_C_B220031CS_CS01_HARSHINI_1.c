#include <stdio.h>
#include <stdlib.h>

struct Hash {
    int key;
    int isOccupied;
};
typedef struct Hash hashtable;

int hashIndex(int k, int tableSize) {
    return (k % tableSize);
}

void insert(int k, hashtable table[], int tableSize) {
    int index = hashIndex(k, tableSize);
    while (table[index].isOccupied == 1 && table[index].key != k) {
        index = (index + 1) % tableSize;
    }
        table[index].key = k;
        table[index].isOccupied = 1;
}

int maxnum(int m, int n) {
    return (m > n) ? m : n;
}

void intersection(int a[], int b[], int m, int  n) {
    int tableSize = 2 * maxnum(m, n);
    hashtable table[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i].isOccupied = 0;      
    }
    for (int i = 0; i < n; i++) {
        insert(b[i], table, tableSize);
    }
    int found = 0;
    for (int i = 0; i < m; i++) {
        if (table[hashIndex(a[i], tableSize)].isOccupied && a[i] == table[hashIndex(a[i], tableSize)].key) {
            printf("%d ", a[i]);
            found = 1;
            table[hashIndex(a[i], tableSize)].isOccupied = 0; 
        }
    }
    if (!found) {
        printf("-1");
    }
}

void unionset(int a[], int b[], int m, int n) {
    int tableSize = 2 * maxnum(m, n);
    hashtable table[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i].isOccupied = 0;
    }
    int found = 0;
    for (int i = 0; i < m; i++) {
        if (!table[hashIndex(a[i], tableSize)].isOccupied) {
            printf("%d ", a[i]);
            insert(a[i], table, tableSize);
            found = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!table[hashIndex(b[i], tableSize)].isOccupied) {
            printf("%d ", b[i]);
            insert(b[i], table, tableSize); 
            found = 1;
        }
    }
    if (!found) {
        printf("-1");
    }
}

void diff(int a[], int b[], int m, int n) {
    int tableSize = 2 * maxnum(m, n);
    hashtable table[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i].isOccupied = 0;
    }
    for (int i = 0; i < n; i++) {
        insert(b[i], table, tableSize);
    }
    int found = 0;
    for (int i = 0; i < m; i++) {
        if (!table[hashIndex(a[i], tableSize)].isOccupied) {
            printf("%d ", a[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("-1");
    }
}


int main() {
    int m, n;

    scanf("%d %d", &m, &n);

    int A[m], B[n];
    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    char operation, array1, array2;
    while (1) {
        scanf(" %c", &operation);

        if (operation == 'e') {
            break;
        }

        if (operation == 'u') {
            scanf(" %c %c", &array1, &array2);
            if (array1 == 'A' && array2 == 'B') {
                unionset(A, B, m, n);
            } else {
                unionset(B, A, n, m);
            }
            printf("\n");
        } else if (operation == 'i') {
            scanf(" %c %c", &array1, &array2);
            if (array1 == 'A' && array2 == 'B') {
                intersection(A, B, m, n);
            } else {
                intersection(B, A, n, m);
            }
            printf("\n");
        } else if (operation == 's') {
            scanf(" %c %c", &array1, &array2);
            if (array1 == 'A' && array2 == 'B') {
                diff(A, B, m, n);
            } else {
                diff(B, A, n, m);
            }
            printf("\n");
        }
    }
    return 0;
}
