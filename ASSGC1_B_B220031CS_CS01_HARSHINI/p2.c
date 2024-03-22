#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node* node;

node createNode(int x){
    node new=(node)malloc(sizeof(struct Node));
    new->data=x;
    new->left=NULL;
    new->right=NULL;
    return new;
}

int max(int a, int b){
    return a>b? a:b;
}

int height(node  root){
    if (root==NULL) return 0;
    int lheight=height(root->left);
    int rheight=height(root->right);
    return 1+ max(lheight,rheight);
}

void printlevel(node root, int level){
    if (root == NULL) return;
    if (level==1)
        printf("%d ",root->data);
    else if (level>1){
        printlevel(root->left,level-1);
        printlevel(root->right,level-1);
    }
}

void level(node root){
    int ht=height(root);
    int i;
    for(i=1;i<=ht;i++){
        printlevel(root,i);
    }
}

node buildtree(char arr[], int *i){
    if (arr[*i] == '\0' || arr[*i] == ')')
        return NULL;
    int num=0;
    if (arr[*i]>= '0' && arr[*i] <= '9'){
        num=num*10 + (arr[*i]-'0');
        (*i)++;
    }
    node root=createNode(num);

    if (arr[*i]=='('){
        (*i)++;
        root->left=buildtree(arr,i);
        (*i)++;
    }

    if (arr[*i]=='('){
        (*i)++;
        root->right=buildtree(arr,i);
        (*i)++;
    }
    return root;
}

void rightview(node root, int level, int maxlevel){
    if (root==NULL)
        return;
    if (maxlevel<level){
        printf("%d ",root->data);
        maxlevel=level;
    }
    rightview(root->right, level+1, maxlevel);
}

void right(node root){
    rightview(root,1,0);
}

int maxsum(node root, int* result) {
    if (root == NULL) {
        return 0;
    }

    int lsum = maxsum(root->left, result);
    int rsum = maxsum(root->right, result);

    // Calculate the sum of the current subtree rooted at 'root'
    int subtreeSum = lsum + rsum + root->data;

    // Update the 'result' if the sum of the current subtree is greater
    *result = max(*result, subtreeSum);

    // Return the sum of the subtree rooted at 'root'
    return max(0, max(lsum, rsum) + root->data);
}




int findMaxSum(node root) {
    int result;
    maxsum(root, &result);
    return result;
}



int main(){
    int index=0;
    char arr[1000];
    int sum;
    scanf("%s",arr);
    char ch;
    int len = strlen(arr);
    node root = buildtree(arr,&index);
    while (1){
        scanf(" %c",&ch);
        if (ch=='l'){
            level(root);
            printf("\n");
        }
        else if (ch=='r'){
            right(root);
            printf("\n");
        }
        else if (ch=='m'){
            printf("%d\n",findMaxSum(root));
        }
        else if (ch=='e')
            break;
    }
    return 0;
}