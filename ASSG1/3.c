#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node* node;

node createnode(int k){
    node newnode = (node)malloc(sizeof(struct Node));
    newnode->data = k;
    newnode->left = newnode->right = NULL;
    return newnode;
}

node buildTree(const char* str, int* index) {
    if (str[*index] == '\0' || str[*index] == ')') {
        return NULL;
    }

    int num = 0;
    while (str[*index] >= '0' && str[*index] <= '9') {
        num = num * 10 + (str[*index] - '0');
        (*index)++;
    }

    node root = createnode(num);

    if (str[*index] == '(') {
        (*index)++;
        root->left = buildTree(str,index);
        (*index)++; 
    }

    if (str[*index] == '(') {
        (*index)++; 
        root->right = buildTree(str, index);
        (*index)++; 
    }
    return root;
}

int ancestor(node root, int value){
    if (root == NULL) 
        return 0;;
    if (root->data==value || ancestor(root->left,value) || ancestor(root->right,value)){
        printf("%d ",root->data);
        return 1;}
    return 0;
}

void printRangeValues(node root, int k1, int k2) {
    if (root == NULL)
        return;

    printRangeValues(root->left, k1, k2);

    if (root->data >= k1 && root->data <= k2) {
        printf("%d ", root->data);
    }

    printRangeValues(root->right, k1, k2);
}

int main() {
    char input[1000];
    scanf("%s", input);

    int index = 0;
    node root = buildTree(input, &index);
    int k1,k2;
    char choice;
    do {
        scanf(" %c", &choice);

        switch (choice) {
            case 'p':
                scanf("%d",&k1);
                scanf("%d",&k2);
                printRangeValues(root,k1,k2);
                printf("\n");
                break;
            case 'a':
                scanf("%d",&k1);
                ancestor(root,k1);
                printf("\n");
                break;
        }

    } while (choice != 'e');

    return 1;
}