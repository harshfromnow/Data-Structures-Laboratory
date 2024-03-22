#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} *node;

typedef struct HashTable {
    int size;
    node* table;
} *hashTable;


int hq(int key, int size) {
    return key % size;
}

node createNode(int key) {
    node newNode = (node)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = key;
        newNode->next = NULL;
    }
    return newNode;
}

hashTable createHashTable(int size) {
    hashTable ht = (hashTable)malloc(sizeof(struct HashTable));
    if (ht != NULL) {
        ht->size = size;
        ht->table = (node*)malloc(size * sizeof(node));
        if (ht->table != NULL) {
            for (int i = 0; i < size; i++) {
                ht->table[i] = NULL;
            }
        }
    }
    return ht;
}

void insert(hashTable ht, int key) {
    int index = hq(key, ht->size);
    node newNode = createNode(key);
    if (newNode == NULL) {
        printf("-1\n");
        return;
    }
    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } 
    else {
        node current = ht->table[index];
        node prev = NULL;
        //in between
        while (current != NULL && current->data < key) {
            prev = current;
            current = current->next;
        }
        if (current != NULL && current->data == key) {
            printf("-1\n");
            free(newNode);
            return;
        }
        //ex l: 15, we insert 5, l: 5->15, smaller number
        if (prev == NULL) {
            newNode->next = ht->table[index];
            ht->table[index] = newNode;
        } 
        //at the end
        else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
    return;
}

void search(hashTable ht, int key) {
    int index = hq(key, ht->size);
    node current = ht->table[index];
    int position = 1;
    while (current != NULL) {
        if (current->data == key) {
            printf("%d %d\n", index, position);
            return;
        }
        current = current->next;
        position++;
    }
    printf("-1\n");
}

void delete(hashTable ht, int key) {
    int index = hq(key, ht->size);
    node current = ht->table[index];
    node prev = NULL;
    int position = 1;
    while (current != NULL) {
        if (current->data == key) {
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("%d %d\n", index, position);
            return;
        }
        prev = current;
        current = current->next;
        position++;
    }
    printf("-1\n");
}

void update(hashTable ht, int oldKey, int newKey) {
    int oldIndex = hq(oldKey, ht->size);
    int newIndex = hq(newKey, ht->size);
    node current = ht->table[oldIndex];
    while (current != NULL) {
        if (current->data == oldKey) {
            node temp = ht->table[newIndex];
            while (temp != NULL) {
                if (temp->data == newKey) {
                    printf("-1\n");
                    return;
                }
                temp = temp->next;
            }
            delete(ht, oldKey);
            insert(ht, newKey);
            return;
        }
        current = current->next;
    }
    printf("-1\n");
}


void printElementsInChain(hashTable ht, int index) {
    if (index < 0 || index >= ht->size) {
        printf("-1\n");
        return;
    }
    if (ht->table[index]==NULL){
        printf("-1\n");
        return;
    }
    node current = ht->table[index];
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int tableSize;
    scanf("%d", &tableSize);
    hashTable ht = createHashTable(tableSize);
    char choice;
    int key, oldKey, newKey, index;
    while (1) {
        scanf(" %c", &choice);
        if (choice == 'i') {
            scanf("%d", &key);
            insert(ht, key);
        } 
        else if (choice == 'd') {
            scanf("%d", &key);
            delete(ht, key);
        } 
        else if (choice == 'u') {
            scanf("%d %d", &oldKey, &newKey);
            update(ht, oldKey, newKey);
        } 
        else if (choice == 's') {
            scanf("%d", &key);
            search(ht, key);
        } 
        else if (choice == 'p') {
            scanf("%d", &index);
            printElementsInChain(ht, index);
        } 
        else if (choice == 'e') {
            break;
        }
    }
    return 0;
}