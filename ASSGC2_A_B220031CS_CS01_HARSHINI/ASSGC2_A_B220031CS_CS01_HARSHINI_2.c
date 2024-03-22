#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    int height;
    int value;
    struct Node* left;
    struct Node* right;
};

typedef struct Node* node;

node createnode(int k,int v){
    node newnode= malloc(sizeof(struct Node));
    newnode->data =k;
    newnode->value= v;
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

void updateHeight(node x) {
    if (x != NULL) {
        x->height = max(height(x->left), height(x->right)) + 1;
    }
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

node balance(node x){
    int bf=balanceFactor(x);
    if (bf>1 && balanceFactor(x->left)>=0)
        return rightRotate(x);

    else if (bf<-1 && balanceFactor(x->right)<0)
        return leftRotate(x);

    else if (bf>1 && balanceFactor(x->left)<0){
        x->left=leftRotate(x->left);
        return rightRotate(x);
    }

    else if (bf<-1 && balanceFactor(x->right)>=0){
        x->right=rightRotate(x->right);
        return leftRotate(x);
    }
    return x;
}

int size(node root) {
    if (root == NULL) return 0;
    return 1 + size(root->left) + size(root->right);
}

int empty(node root) {
    return root == NULL ? 1 : 0;
}

node insert(node root, int key, int value){
    if (root == NULL) {
        return createnode(key,value);
    } 
    else if (key < root->data) {
        root->left = insert(root->left, key, value);
    } 
    else if (key > root->data) {
        root->right = insert(root->right, key, value);
    } 
    else if (key == root->data) {
        root->value=value;
        return root;
    }
    else {
        return root;
    }
    updateHeight(root);
    return balance(root);
}

void find(node root, int key){
    node temp=root;
    while (temp!=NULL){
        if (temp->data==key){
            printf("%d %d\n",temp->data,temp->value);
            return ;
        }
        if (temp->data<key) temp=temp->right;
        else temp=temp->left;
    }
    printf("-1\n");
    return;
}

void lowerBound(node root, int key) {
    if (root == NULL) {
        printf("-1\n");
        return;
    }
    node bound = NULL;
    while (root != NULL) {
        if (root->data >= key) {
            bound = root;
            root = root->left;
        } 
        else {
            root = root->right;
        }
    }
    if (bound != NULL) {
        printf("%d %d\n", bound->data, bound->value);
    } 
    else {
        printf("-1\n");
    }
}

void inorder(node root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void printElements(node root) {
    if (root == NULL) {
        printf("-1\n");
        return;
    }
    inorder(root);
    printf("\n");
}

int main(){
    char ch;
    int key, value;
    node root = NULL;
    while(1){
        scanf("%c", &ch);
        if (ch=='i'){
            scanf("%d %d",&key,&value);
            root=insert(root, key, value);
        }
        else if (ch=='l'){
            scanf("%d",&key);
            lowerBound(root,key);
        }
        else if (ch=='f'){
            scanf("%d",&key);
            find(root,key);
        }
        else if (ch=='s'){
            printf("%d\n",size(root));
        }
        else if (ch=='e'){
            printf("%d\n",empty(root));
        }
        else if (ch=='p'){
            printElements(root);
        }
        else if (ch=='t'){
            break;
        }
    }
    return 1;
}