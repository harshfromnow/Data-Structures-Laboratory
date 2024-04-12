#include <stdio.h>
#include <stdlib.h>
int n;

void printGraph(int graph[n][n]){
    for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                printf("%d ",graph[i][j]);
            }
            printf("\n");
        }
    return;
}

void floydwarshall(int graph[n][n]){
    int i, j, k;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if ( graph[i][j] > graph[i][k] + graph[k][j])
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
        }
    }
    printGraph(graph);
    return;
}

int main(){
    int num;
    scanf("%d",&n);
    int graph[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            scanf("%d",&num);
            if(num == -1)
                graph[i][j]=10000;
            else
                graph[i][j]=num;
        }
    }

    floydwarshall(graph);
    return 1;
}