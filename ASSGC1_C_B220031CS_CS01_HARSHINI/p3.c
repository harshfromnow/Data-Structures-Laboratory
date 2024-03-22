#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char* name;
    char* roll;
    int age;
    struct Node* next;
};

typedef struct Node person;

int hvalue(person* p){
    int len=strlen(p->name);
    int sum=0;
    for(int i=0;i<len;i++){
        sum+=p->name[i];
    }
    sum+=p->age;
    return sum%4;
}

void insert_person (person* hash_table[], person* p)      //Inserts a person's details into the hash table
{
    int index = hash_function(p);
    if (hash_table[index] == NULL)
    {
        hash_table[index] = p;
        p->next = NULL;
    }
    else
    {
        person* current = hash_table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = p;
        p->next = NULL;
    }
}

void displayBranch(person* student, int group, char branch[]) {
    person* temp = student;
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

void displayGroup(person* student,int group) {
    int count = 0;
    person* temp = student; 
    while (temp != NULL) {
        count++; 
        temp = temp->next;
    }
    printf("%d ", count); 
    temp = student[group]; 
    while (temp != NULL) {
        printf("%s ", temp->name); 
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d",&n);
    person* students = (person*)malloc(n * sizeof(person));
    person* hash_table[4];
    initialize_hash (hash_table, 4);
    for (int i = 0; i < n; i++)
    {
        students[i].name = (char*)malloc(50 * sizeof(char));
        scanf ("%s", students[i].name);

        students[i].roll = (char*)malloc(9 * sizeof(char));
        scanf ("%s", students[i].roll);

        scanf ("%d", &students[i].age);
        insert_person (hash_table, &students[i]);
    }
    char choice;
    int k;
    char branch[3];
    while (1)
    {
        scanf (" %c", &choice);

        if (choice == 'c')
        {
            scanf ("%d", &k);
            displayGroup (hash_table, k);
        }
        else if (choice >= '0' && choice <= '3')
        {
            scanf ("%s", branch);
            if (branch[0] >= 'a' && branch[0] <= 'z')
                branch[0] -= 32;
            if (branch[1] >= 'a' && branch[1] <= 'z')
                branch[1] -= 32;
            int group=choice-'0';
            displayBranch (hash_table[group],group, branch);
        }
        else if (choice == 'e')
           break;
    }
    return 0;
}
