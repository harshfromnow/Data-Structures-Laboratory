#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node* node;

struct Graph {
    int size;
    node* adjlist;
};

typedef struct Graph* graph;

graph createGraph(int V) {
    graph g = (graph)malloc(sizeof(struct Graph));
    g->size = V;
    g->adjlist = (node*)malloc(V * sizeof(struct Node));
    for (int i = 0; i < V; i++) {
        g->adjlist[i] = NULL;
    }
    return g;
}

void addEdge(graph g, int u, int v) {
    node newnode = (node)malloc(sizeof(struct Node));
    newnode->data = v;
    newnode->next = g->adjlist[u];
    g->adjlist[u] = newnode;
}

int DFSUtil(graph graph, int v, int* visited, int* size) {
    (*size)++;
    visited[v] = 1;

    node temp = graph->adjlist[v];
    while (temp) {
        if (!visited[temp->data]) {
            DFSUtil(graph, temp->data, visited, size);
        }
        temp = temp->next;
    }
    return *size;
}

int connected(graph graph) {
    int count = 0;
    int* visited = (int*)malloc(graph->size * sizeof(int));
    for (int v = 0; v < graph->size; v++) {
        visited[v] = 0;
    }
    for (int v = 1; v < graph->size; v++) {
        if (!visited[v]) {
            int size = 0;
            DFSUtil(graph, v, visited, &size);
            if (size > 0) {
                count++;
            }
        }
    }
    free(visited);
    return count;
}

void sizeofcomp(graph g) {
    int* visited = (int*)malloc(g->size * sizeof(int));
    for (int v = 0; v < g->size; v++) {
        visited[v] = 0;
    }
    for (int v = 0; v < g->size; v++) {
        if (!visited[v]) {
            int size = 0;
            DFSUtil(g, v, visited, &size);
            if (size > 1) {
                printf("%d ", size);
            }
        }
    }
    printf("\n");
    free(visited);
}

int main() {
    int m;
    scanf("%d", &m);
    graph g = createGraph(m);
    for (int i = 0; i < m; i++) {
        int e = 0;
        int first = 0;
        int u = 0;
        while (scanf("%d", &e)) {
            if (first == 0) {
                u = e;
                first++;
            } else {
                addEdge(g, u, e);
            }
            if (getchar() == '\n') {
                break;
            }
        }
    }

    char ch;
    while (1) {
        scanf("%c", &ch);
        if (ch == 'n') {
            printf("%d\n", connected(g));
        } else if (ch == 's') {
            sizeofcomp(g);
        } else if (ch == 'b') {
            // printf("%d\n", bridges(g));
        } else if (ch == 'a') {
            // articulation();
        } else if (ch == 't') {
            break;
        }
    }
    return 0;
}
