#include <stdio.h>
#include <stdlib.h>

struct Tree{
    int data;
    struct Tree* left;
    struct Tree* right;
};

typedef struct Tree* node;

node createNode(int k){
    node newNode=(node)malloc(sizeof(struct Tree));
    newNode->data=k;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

node constructTree(int in[],int pre[],int beg,int end,int *index){
    if (beg>end) return NULL;
    node new=createNode(pre[(*index)++]);
    int i;
    for(i=beg;i<=end;i++){
        if (in[i]==new->data)
            break;
    }
    new->left=constructTree(in,pre,beg,i-1,index);
    new->right=constructTree(in,pre,i+1,end,index);
    return new;
}

void postorder(node  root){
    if (root==NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
    return;
}

node buildtree(int in[],int pre[],int length){
    int index = 0;
    return constructTree(in,pre,0,length-1,&index);
}

int max(int a,int b){
    return a>b? a:b;
}

int height(node tree){
    if (tree==NULL) return 0;
    int lheight=height(tree->left);
    int rheight=height(tree->right);
    return 1+max(lheight,rheight);
}

void printlevel(node tree,int level,int direction){
    if (tree==NULL) return;
    if (level==1)
        printf("%d ",tree->data);
    if (direction==1){
        printlevel(tree->left,level-1,direction);
        printlevel(tree->right,level-1,direction);
    }
    else{
        printlevel(tree->right,level-1,direction);
        printlevel(tree->left,level-1,direction);
    }
    return;
}

void zigzag(node tree){
    int direction=1;
    if (tree==NULL) return;
    int ht=height(tree);
    for (int i=1;i<=ht;i++){
        printlevel(tree,i,direction);
        direction=-direction;
    }
    return;
}

int isLeaf(node tree){
    if (tree==NULL) 
        return 0;
    if  ((tree->left==NULL) && (tree->right==NULL)) 
        return 1;
    return 0;
}

int leftLeafSum(node tree){
    int sum=0;
    if (tree!=NULL){
        if (isLeaf(tree->left))
                sum+=tree->left->data;
            else{
                sum+=leftLeafSum(tree->left); 
                sum+=leftLeafSum(tree->right);
            }
    }
    return sum;
}

int diameter(node tree){
    if (tree==NULL)
        return 0;
    int lheight=height(tree->left);
    int rheight=height(tree->right);

    int ldiameter=diameter(tree->left);
    int rdiameter=diameter(tree->right);
    printf("%d %d\n",ldiameter, rdiameter);
    return max(lheight+rheight+1,max(ldiameter,rdiameter));
}

int main(){
    int n;
    scanf("%d",&n);
    int in[n];
    int pre[n];
    for(int i=0;i<n;i++){
        scanf("%d",&in[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&pre[i]);
    }
    node root = buildtree(in,pre,n);
    char c;
    while(1){
        scanf(" %c",&c);
        if (c=='p'){
            postorder(root);
            printf("\n");
        }
        else if (c == 'z'){
            zigzag(root);
            printf("\n");
        }
        else if (c == 's'){
            printf("%d\n",leftLeafSum(root));
        }
        else if (c == 'd'){
            printf("%d\n",diameter(root));
        }
        else if (c=='e') break;
    }
    return 0;
}