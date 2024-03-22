#include <stdio.h>
#include <stdlib.h>
#define maxsize 500

struct Node{
    int key;
    int color;
    struct Node *right, *left;
};

typedef struct Node* node;

node createnode(int key, int c)
{
    node newnode=(node)malloc(sizeof(struct Node));
    newnode->key=key;
    newnode->color=c;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}

node createtree(char str[], int* i)
{
    int num=0; int c=0;
    node root=NULL;
    while(str[*i]!='\0')
    {
        if(str[*i]=='(') 
        {
            (*i)+=2;
            if(str[*i]==')')
            {
                (*i)++;
                return NULL;
            }
            int sign=1;
            if(str[*i]=='-')
            {
                sign=-1;
                (*i)++;
            }
            while(str[*i]>='0'&&str[*i]<='9')
            {
                num=num*10+(str[*i]-'0');
                (*i)++;
            }
            num*=sign;
            (*i)++;
            if(str[*i]=='R')
            {
                c=0;
                (*i)+=2;
                
            }
            if(str[*i]=='B')
            {
                c=1;
                (*i)+=2;
                
            }
            root=createnode(num,c);
            root->left=createtree(str,i);
            root->right=createtree(str,i);
        }
        else if (str[*i]==')')
        {
            (*i)++;
            return root;
        }
        else (*i)++;
        
    }
    return root;
}

int redblack(node root,int count, int *value)
{
    if(root==NULL)
        return count;
    if(root->color==1) 
        count++;
    if(root->color==0 &&((root->left && root->left->color==0)||(root->right &&root->right->color==0))) 
        *value=0;
    int l=redblack(root->left,count,value);
    int r=redblack(root->right,count,value);
    if(l!=r) *value=0;
    return l;
}

int main()
{
    char str[maxsize];
    fgets(str,maxsize,stdin);
    node root=NULL;
    int index=0;
    root=createtree(str,&index);
    int value=1;
    int count=0;
    if(root->color==0) value=0;
    else
    {
        redblack(root,count,&value);
    }
    if(value){
        printf("1\n");
    }
    else printf("0\n");
    return 1;
}