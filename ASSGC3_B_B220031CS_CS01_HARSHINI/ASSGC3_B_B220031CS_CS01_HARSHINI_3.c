#include <stdio.h>
#include <stdlib.h>
#define maxint 10000
int V;

int minDistance(int dist[], int shortestpath[])
{
    int min = maxint;
    int min_index;
    for (int v = 0; v < V; v++)
        if (shortestpath[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}
 
void printSolution(int dist[])
{
    for (int i = 1; i < V; i++)
        printf("%d ", dist[i]);
}

void dijkstra(int graph[V][V], int source){
    int dist[V];
    int shortestpath[V];
    for (int i = 0; i < V; i++){
        dist[i] = maxint;
        shortestpath[i] = 0;
    }
    dist[source] = 0;
     for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, shortestpath);
        shortestpath[u] = 1;
        for (int v = 0; v < V; v++)
            if (!shortestpath[v] && graph[u][v]
                && dist[u] != maxint
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

int main(){
    int n;
    scanf("%d",&n);
    V=n+1;
    int graph[V][V];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            graph[i][j] = 0;
        }
    }
    int weight;
    int edgemarking = 1;
    int weightmarking = 0;
    for(int i=1;i<=2*n;i++){ 
        if( i > n ){
            edgemarking = 0;
            weightmarking = 1;
        }
        int weight;
        int tri = 0;
        int u = -1;
        while( scanf("%d",&weight) ){
            if( edgemarking ){
                
                if( tri == 0 ){
                    u = weight;
                    tri++;
                }
                else{
                    graph[u][weight] = -1;
                }
                 
            }
            else{
                if( tri == 0 ){
                    u = weight;
                    tri++;
                }
                else{
                    for(int v=0;v<=n;v++){
                        if( graph[u][v] == -1 ){
                            graph[u][v] = weight;
                            break;
                        }
                    }
                } 
            }
            if( getchar() == '\n' ){
                break;
            }
        }
    }
    int source;
    scanf("%d",&source);
    dijkstra(graph, source);
    printf("\n");
    return 0;
}