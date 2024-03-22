#include <stdio.h>
#include <stdlib.h>

struct Node{
    int key;
    char color;
    struct Node *left,*right,*parent;
};

typedef struct Node* node;

node createnode(int k){
    node newNode=(node)malloc(sizeof(struct Node));
    newNode->key=k;
    newNode->color='R';
    newNode->left = newNode->parent = newNode->right = NULL;
    return newNode;
}

void rotateLeft(node root, node x) {
    node y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x; 
    y->parent = x->parent;
    if (x->parent == NULL) root= y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(node root, node x) {
    node y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void fixViolation(node root, node z){
    while (z!= root && z->parent->color=='R'){
        if (z->parent==z->parent->parent->left){
            node y=z->parent->parent->right;
            if (y!=NULL && y->color=='R'){
                y->color='B';
                z->parent->color='B';
                z->parent->parent->color='R';
                z=z->parent->parent;
            }
            else{
                if (z==z->parent->right){
                    z=z-> parent;
                    rotateLeft(root,z);
                }
                z->parent->color='B';
                z->parent->parent->color='R';
                rotateRight(root,z->parent->parent);
            }
        }
        else{
            node y=z->parent->parent->left;
            if (y!=NULL && y->color=='R'){
                y->color='B';
                z->parent->color='B';
                z->parent->parent->color='R';
                z=z->parent->parent;
            }
            else{
                if (z==z->parent->left){
                    z=z-> parent;
                    rotateRight(root,z);
                }
                z->parent->color='B';
                z->parent->parent->color='R';
                rotateLeft(root,z->parent->parent);
            }
        }
    }
    root->color='B';
}

node insert(node root, int key) {
    node z = createnode(key);
    node y = NULL;
    node x = root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == NULL) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    fixViolation(root, z);

    return root;
}

void printParenthesis(node root){
    if (root==NULL){
        printf("() ");
        return;
    }
    printf("(%d %c ",root->key,root->color);
    printParenthesis(root->left);
    printParenthesis(root->right);
    printf(") ");
    return;
}

int main() {
    node root = NULL;
    char choice;
    int key;

    while (1) {
        if (scanf("%d", &key) != 1) {
            break; 
        }
        root = insert(root, key);
        printParenthesis(root);
        printf("\n");
    }
    return 1;
}