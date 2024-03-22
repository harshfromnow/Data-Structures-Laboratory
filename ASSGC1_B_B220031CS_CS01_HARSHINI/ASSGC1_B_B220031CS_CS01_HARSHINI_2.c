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

int max(int a, int b) { return (a > b) ? a : b; }

int height(node root)
{
    if (root == NULL)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

void currentLevel(node root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        currentLevel(root->left, level - 1);
        currentLevel(root->right, level - 1);
    }
    return;
}

void levelOrder(node root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        currentLevel(root, i);
    return;
}

void rightcheck(node root, int level, int currentLevel) {
    if (root == NULL)
        return;

    if (currentLevel < level) {
        printf("%d ", root->data);
        currentLevel = level;
    }

    rightcheck(root->right, level + 1, currentLevel);
}

void rightView(node root) {
    rightcheck(root, 1, 0);
}

int checkBST(node root, node parent, int *sum){
    if (root==NULL) return 1;
    
    if (root->left && root->left->data >= root->data)
        return 0;

    if (root->right && root->right->data <= root->data)
        return 0;

    *sum+=root->data;

    return checkBST(root->left,root,sum) && checkBST(root->right,root,sum);
}

int maxSum(node root){
    if (root==NULL) return 0;
    int sum=0;

    if (checkBST(root,NULL,&sum)) return sum;

    int leftsum=maxSum(root->left);
    int rightsum=maxSum(root->right);

    return (leftsum>rightsum) ? leftsum : rightsum;
}

int main() {
    char input[1000];
    scanf("%s", input);

    int index = 0;
    node root = buildTree(input, &index);

    char command;
    while (1) {
        scanf(" %c", &command);

        switch (command) {
            case 'l':
                levelOrder(root);
                printf("\n");
                break;

            case 'm':
                printf("%d\n", maxSum(root));
                break;
            case 'r':
                rightView(root);
                printf("\n");
                break;

            case 'e':
                exit(0);
        }
    }

    return 0;
}