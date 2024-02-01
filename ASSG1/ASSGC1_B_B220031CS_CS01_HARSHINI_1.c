#include <stdio.h>
#include <stdlib.h>
 
struct node {
    int data;
    struct node* left;
    struct node* right;
};

int search(int arr[], int start, int end, char value)
{
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
}

struct node* newNode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return (node);
}

struct node* buildTree(int in[], int pre[], int beg, int end)
{
    static int preIndex = 0;
 
    if (beg > end)
        return NULL;
 
    struct node* temp = newNode(pre[preIndex++]);
 
    if (beg == end)
        return temp;
 
    int index = search(in, beg, end, temp->data);
 
    temp->left = buildTree(in, pre, beg, index - 1);
    temp->right = buildTree(in, pre, index + 1, end);
 
    return temp;
}

void postorder(struct node* node)
{
    if (node == NULL)
        return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

void swap(struct node*** a, struct node*** b) {
    struct node** temp = *a;
    *a = *b;
    *b = temp;
}

void zigzagtraversal(struct node* root) {
    if (root==NULL)
        return;

    struct node** currentlevel = (struct node**)malloc(sizeof(struct node*) * 1000);
    struct node** nextlevel = (struct node**)malloc(sizeof(struct node*) * 1000);

    int currenttop = -1;
    int nexttop = -1;

    int lefttoright = 1;

    currentlevel[++currenttop] = root;

    while (currenttop >= 0) {
        struct node* temp = currentlevel[currenttop--];

        if (temp) {
            printf("%d ", temp->data);

            if (lefttoright) {
                if (temp->left)
                    nextlevel[++nexttop] = temp->left;
                if (temp->right)
                    nextlevel[++nexttop] = temp->right;
            } else {
                if (temp->right)
                    nextlevel[++nexttop] = temp->right;
                if (temp->left)
                    nextlevel[++nexttop] = temp->left;
            }
        }

        if (currenttop < 0) {
            lefttoright = !lefttoright;
            swap(&currentlevel, &nextlevel);
            currenttop = nexttop;
            nexttop = -1;
        }
    }

    free(currentlevel);
    free(nextlevel);
}

int max(int a, int b) { return (a > b) ? a : b; }


int height(struct node* node)
{
    if (node == NULL)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

int diameter(struct node* tree)
{
    if (tree == NULL)
        return 0;
 
    int leftheight = height(tree->left);
    int rightheight = height(tree->right);
 
    int leftdiameter = diameter(tree->left);
    int rightdiameter = diameter(tree->right);
 
    return max(leftheight + rightheight + 1,
               max(leftdiameter, rightdiameter));
}

int isLeaf(struct node *node)
{
  if (node == NULL)
    return 0;
  if (node->left == NULL && node->right == NULL)
    return 1;
  return 0;
}

int leftLeafSum(struct node *root)
{
  int result = 0;
  if (root != NULL)
  {
    if (isLeaf(root->left))
      result += root->left->data;
    else 
      result += leftLeafSum(root->left);
    result += leftLeafSum(root->right);
  }
  return result;
}

void level(int result[], struct node* root, int d, int* size) {
    if (root==NULL)
        return;

    if (d >= *size) {
        result[d] = root->data;
        *size = d + 1;
    } else {
        result[d] = result[d] > root->data ? result[d] : root->data;
    }

    level(result, root->left, d + 1, size);
    level(result, root->right, d + 1, size);
}

int* levelMax(struct node* root, int* size) {
    int* result = NULL;
    int maxSize = 0;
    level(result, root, 0, &maxSize);
    *size = maxSize;
    return result;
}

int main() {
    struct node* root = NULL;

    int n, value;
    scanf("%d", &n);

    int inorder[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    int preorder[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    int len = sizeof(inorder) / sizeof(inorder[0]);
    root = buildTree(inorder, preorder, 0, len - 1);  

    int size;  
    int result[size];  

    char choice;
    do {
        scanf(" %c", &choice);

        switch (choice) {
            case 'p':
                postorder(root);
                printf("\n");
                break;
            case 'm':
                size = height(root);
                level(result, root, 0, &size);
                for (int i = 0; i < size; i++) {
                    printf("%d ", result[i]);
                }
                printf("\n");
                break;
            case 'z':
                zigzagtraversal(root);
                printf("\n");
                break;
            case 'd':
                printf("%d\n", diameter(root));
                break;
            case 's':
                printf("%d\n", leftLeafSum(root));  
                break;
            case 'e':
                break;
        }

    } while (choice != 'e');

    return 1;
}
