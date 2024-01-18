#include <stdio.h>
#include <stdlib.h>
#define max 100

struct Stack {
    char arr[max];
    int top;
};

typedef struct Stack* stack;

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

int STACK_FULL(stack s, int n) {
    if (s->top == n - 1) {
        return -1;
    } else {
        return 1;
    }
}

void push(stack s, char c, int n) {
    if (STACK_FULL(s, n) == -1) {
        printf("-1\n");
    } else {
        s->top = s->top + 1;
        s->arr[s->top] = c;
    }
    return;
}

int main() {
    int n;
    scanf("%d", &n);
    char ch[n];
    stack s = (stack)malloc(sizeof(struct Stack));  
    s->top = -1;
    scanf("%s", ch);
    for (int i = 0; i < n; i++) {
        if (ch[i] == '(' || ch[i] == ')' || isOperator(ch[i])) {
            push(s, ch[i], n);
        }
    }
    for (int j = 0; j < s->top + 1; j++) {
        if (s->arr[j] == ')') {
            while (s->arr[s->top] != '(') {
                s->top = s->top - 1;
            }
            if (s->arr[s->top] == '(' && s->arr[s->top + 1] == ')') {
                printf("1\n");
                free(s);  
                return 1;
            }
        }
    }
    printf("0\n");
    free(s); 
    return 0;
}	
