#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int size;
    struct Node** adjList;
};

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->size = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;
}

void printAllPathsUtil(struct Graph* graph, int s, int d, int* visited, int* path, int pathLen) {
    visited[s] = 1;
    path[pathLen] = s;
    pathLen++;

    if (s == d) {
        for (int i = 0; i < pathLen; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        struct Node* temp = graph->adjList[s];
        while (temp != NULL) {
            if (!visited[temp->data]) {
                printAllPathsUtil(graph, temp->data, d, visited, path, pathLen);
            }
            temp = temp->next;
        }
    }

    pathLen--;
    visited[s] = 0;
}

void printAllPaths(struct Graph* graph, int s, int d, int* visited, int* path, int pathLen) {
    for (int i = 0; i < graph->size; i++) {
        visited[i] = 0;
    }

    printAllPathsUtil(graph, s, d, visited, path, pathLen);
}

int isCyclicUtil(struct Graph* graph, int v, int parent, int* visited) {
    visited[v] = 1;

    struct Node* temp = graph->adjList[v];
    while (temp != NULL) {
        if (!visited[temp->data]) {
            if (isCyclicUtil(graph, temp->data, v, visited))
                return 1;
        } else if (temp->data != parent)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int isTree(struct Graph* graph) {
    int* visited = (int*)malloc(graph->size * sizeof(int));
    for (int i = 0; i < graph->size; i++) {
        visited[i] = 0;
    }
    if (isCyclicUtil(graph, 0, -1, visited))
        return -1;
    for (int u = 0; u < graph->size; u++) {
        if (!visited[u])
            return -1;
    }

    free(visited);
    return 1;
}

int main() {
    int n;
    char ch;
    scanf("%d", &n);
    struct Graph* graph = createGraph(n);

    for (int i = 0; i < n; i++) {
        int element = 0;
        int tri = 0;
        int u = 0;
        while (scanf("%d", &element)) {
            if (tri == 0) {
                u = element;
                tri++;
            } else {
                addEdge(graph, u, element);
            }
            if (getchar() == '\n') {
                break;
            }
        }
    }

    while (1) {
        int s, d;
        scanf(" %c", &ch);
        if (ch == 'a') {
            scanf("%d %d", &s, &d);
            int* visited = (int*)malloc(graph->size * sizeof(int));
            int* path = (int*)malloc(graph->size * sizeof(int));
            for (int i = 0; i < graph->size; i++) {
                visited[i] = 0;
            }
            printAllPaths(graph, s, d, visited, path, 0);
            free(visited);
            free(path);
        } else if (ch == 't') {
            printf("%d\n", isTree(graph));
        } else if (ch == 'x') {
            break;
        }
    }

    return 0;
}
