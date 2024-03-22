#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    int height;
    struct Node* left;
    struct Node* right;
};

typedef struct Node* node;

node createnode(int k){
    node newnode= malloc(sizeof(struct Node));
    newnode->data =k;
    newnode->height=1;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}

int max(int a, int b){
    return a>b? a:b;
}

int height(node x){
    if (x==NULL)
        return -1;
    int lh= height(x->left);
    int rh= height(x->right);
    return 1+max(lh,rh);
}

int balanceFactor(node x){
    if (x==NULL)
        return 0;
    return height(x->left)-height(x->right);
}

node rightRotate(node p){
    node pl=p->left;
    node plr=pl->right;

    p->left=plr;
    pl->right=p;

    p->height=height(p);
    pl->height=height(pl);

    return pl;
}

node leftRotate(node p){
    node  pr=p->right;
    node prl=pr->left;

    p->right =prl;
    pr->left=p;

    p->height=height(p);
    pr->height=height(pr);

    return pr;
}

node insert(node root,node z,int *lr,int *rr){
    if (root==NULL){
        return z;
    }
    if(root->data>z->data)
    {
        root->left=insert(root->left,z,lr,rr);
    }
    else if(root->data<z->data)
    {
        root->right=insert(root->right,z,lr,rr);
    }
    root->height=height(root);
    int bf=balanceFactor(root);
    if(bf>1&& z->data < root->left->data)
    {
        (*rr)++;
        return rightRotate(root);
    }
    if(bf>1&& z->data > root->left->data)
    {
        (*lr)++;
        (*rr)++;
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if(bf<-1&& z->data > root->right->data)
    {
        (*lr)++;
        return leftRotate(root);
    }
    
    if(bf<-1&& z->data < root->right->data)
    {
        (*lr)++;
        (*rr)++;
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preorder(node root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void printPath(int path[], int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int findPath(node root, int k, int path[], int pathLen) {
    if (root == NULL) {
        return 0;
    }
    path[pathLen] = root->data;
    pathLen++;
    if (root->data == k) {
        printPath(path, pathLen);
        return 1;
    }
    if (findPath(root->left, k, path, pathLen) ||
        findPath(root->right, k, path, pathLen)) {
        return 1;
    }
    return 0;
}

void calculateRotations(node x, int *leftRotations, int *rightRotations) {
    if (x == NULL) {
        return;
    }

    int bf = balanceFactor(x);

    if (bf > 0) {
        *leftRotations += bf;
    } else {
        *rightRotations += -bf;
    }

    calculateRotations(x->left, leftRotations, rightRotations);
    calculateRotations(x->right, leftRotations, rightRotations);
}


int main(){
    node root = NULL;
    char ch;
    int k;
    int leftRotations = 0, rightRotations = 0;
    int path[100];
    int pathLen = 0;
    while (1){
        scanf("%c", &ch);
        if (ch == 'i'){
            scanf("%d",&k);
            node z = createnode(k);
            root=insert(root,z,&leftRotations,&rightRotations);
        }
        else if (ch == 's') {
            printf("%d %d\n", leftRotations, rightRotations);
        }
        else if (ch=='p'){
            preorder(root);
            printf("\n");
        }
        else if (ch=='x'){
            scanf("%d", &k);
            if (!findPath(root, k, path, pathLen)) {
                printf("-1\n");
            }
        }
        else if (ch=='e'){
            break;
        }
    }
    return 1;
}