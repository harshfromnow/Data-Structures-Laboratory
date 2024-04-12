#include <stdio.h>
#include <stdlib.h>
#define MAX_EDGES 100
#define MAX_NODES 100

struct Node {
    int source;
    int destination;
    int weight;
};

typedef struct Node* node;

// Comparator function to use in sorting
int comparator(const void* p1, const void* p2) {
    const struct Node* x = p1;
    const struct Node* y = p2;

    return x->weight - y->weight;
}

// Initialization of parent[] and rank[] arrays
void makeSet(int parent[], int rank[], int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Function to find the parent of a node
int findParent(int parent[], int component) {
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

// Function to unite two sets
void unionSet(int u, int v, int parent[], int rank[], int n) {
    // Finding the parents
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

// Function to find the MST
void kruskal(int n, struct Node edge[]) {
    qsort(edge, n, sizeof(struct Node), comparator);

    int parent[MAX_NODES];
    int rank[MAX_NODES];

    // Function to initialize parent[] and rank[]
    makeSet(parent, rank, n);

    // To store the minimum cost
    int minCost = 0;

    for (int i = 0; i < n; i++) {
        int v1 = findParent(parent, edge[i].source);
        int v2 = findParent(parent, edge[i].destination);
        int wt = edge[i].weight;

        if (v1 != v2) {
            unionSet(v1, v2, parent, rank, n);
            minCost += wt;

        }
    }
    printf("%d\n", minCost);
}

int main() {
    int n;
    int count=0;
    scanf("%d",&n);
    struct Node edge[MAX_EDGES] = {0};
    for (int i = 0; i < n; i++) {
        int node, adjNode;
        scanf("%d", &node);
        while (scanf("%d", &adjNode) == 1) {
                edge[count].source = node;
                edge[count].destination = adjNode;
                edge[count].weight=1;
                count++;
            char delimiter;
            scanf("%c", &delimiter);
            if (delimiter == '\n')
                break;
        }
    }
    int w=0;
    for (int i = 0; i < n; i++) {
        int node, adjNode;
        scanf("%d", &node);
        while (scanf("%d", &adjNode) == 1) {
            if (edge[w].weight==1){
                edge[w].weight = adjNode;
                w++;
            }
            char delimiter;
            scanf("%c", &delimiter);
            if (delimiter == '\n')
                break;
        }
    }
    kruskal(count, edge);
    return 1;
}