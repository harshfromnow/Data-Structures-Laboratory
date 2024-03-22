#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char name[100];
    char roll[100];
    int age;
    struct Node *next;
};

typedef struct Node* node;

struct HashTable {
    int groupNo;
    node* table;
};

typedef struct HashTable* hashtable;

node createNode(char name[], char roll[], int age) {
    node newStudent = (node)malloc(sizeof(struct Node));
    if (newStudent != NULL) {
        strcpy(newStudent->name, name);
        strcpy(newStudent->roll, roll);
        newStudent->age = age;
        newStudent->next = NULL;
    }
    return newStudent;
}

hashtable createHashTable(int V) {
    hashtable hashTable = (hashtable)malloc(sizeof(struct HashTable));
    hashTable->groupNo = V;
    hashTable->table = (node*)malloc(V * sizeof(node));
    for (int i = 0; i < V; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

int hValue(char name[], int age) {
    int sum = 0;
    for (int j = 0; name[j] != '\0'; j++) {
        sum += name[j];
    }
    sum += age;
    return sum % 4;
}

void insertItem(hashtable hashTable, char name[], char roll[], int age) {
    int index = hValue(name, age);
    node newNode = createNode(name, roll, age);
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
        return;
    }
    node temp = hashTable->table[index];
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void displayGroup(hashtable student,int group) {
    int count = 0;
    node temp = student->table[group]; 
    while (temp != NULL) {
        count++; 
        temp = temp->next;
    }
    printf("%d ", count); 
    temp = student->table[group]; 
    while (temp != NULL) {
        printf("%s ", temp->name); 
        temp = temp->next;
    }
    printf("\n");
}

void displayBranch(hashtable student, int group, char branch[]) {
    node temp = student->table[group];
    int flag = 0;
    while (temp != NULL) {
        if (temp->roll[7] == toupper(branch[0]) && temp->roll[8] == toupper(branch[1])) {
            printf("%s ", temp->name);
            flag = 1;
        }
        temp = temp->next;
    }
    if (flag == 0) {
        printf("-1");
    }
    printf("\n");
}



int main() {
    int n;
    scanf("%d", &n);
    hashtable student = createHashTable(n);
    for (int i = 0; i < n; i++) {
        char name[100];
        char roll[50];
        int age;
        scanf("%s %s %d", name, roll, &age);
        insertItem(student, name, roll, age);
    }
    char ch;
    int group;
    char branch[2];
    while (1){
        scanf(" %c",&ch);
        if (ch=='c'){
            scanf("%d",&group);
            if (group>=0 && group<n && group<=3)
                displayGroup(student,group);
            else{
                printf("-1\n");
            }
        }
        else if (ch >= '0' && ch <= '3'){ 
            group = ch - '0'; 
            scanf("%s", branch);
            displayBranch(student, group, branch);
        }
        else if (ch=='e') break;
    }
    for (int i = 0; i < student->groupNo; i++) {
        node head = student->table[i];
        while (head != NULL) {
            node temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(student->table);
    free(student);
    return 0;
}
