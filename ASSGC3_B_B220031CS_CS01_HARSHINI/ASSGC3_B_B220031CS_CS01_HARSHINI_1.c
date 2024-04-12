#include <stdio.h>
#include <stdlib.h>
#define intmax 10000
int n;

int minimumkey(int key[], int vertexset[])
{
    int min = intmax;
    int min_index;
    for (int v = 0; v < n; v++)
        if (vertexset[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void totalWeight(int graph[n][n]){
    int parent[n];
    int minweight[n];
    int vertexset[n];
    for (int i=0;i<n;i++){
        minweight[i]=intmax;
        vertexset[i]=0;
    }
    minweight[1]=0;
    parent[1]=-1;
    int edgecount=0; 
    int totweight = 0;
    for (int count = 0; count < n ; count++) {
        int u = minimumkey(minweight, vertexset);
        vertexset[u] = 1;   
        totweight+=minweight[u];    
        for (int v = 0; v < n; v++)
            if (graph[u][v] != 0  && vertexset[v] == 0 ){
                if( graph[u][v] < minweight[v] ){
                    minweight[v] = graph[u][v];
                    parent[v] = u;
                }
            }
    }
    printf("%d\n",totweight);
}

void prims(int graph[n][n], int start){
    int parent[n];
    int minweight[n];
    int vertexset[n];
    for (int i=0;i<n;i++){
        minweight[i]=intmax;
        vertexset[i]=0;
    }
    minweight[start]=0;
    parent[start]=-1;
    int edgecount=0;
    int totweight = 0;
    for (int count = 0; count < n ; count++) {
        int u = minimumkey(minweight, vertexset);    
        if( count != 0 ){
            printf("%d %d ",parent[u],u);
        }
        vertexset[u] = 1;   
        totweight+=minweight[u];
        for (int v = 0; v < n; v++)
            if (graph[u][v] != 0  && vertexset[v] == 0 ){
                if( graph[u][v] < minweight[v] ){
                    minweight[v] = graph[u][v];
                    parent[v] = u;
                }
            }
    }
}

int main(){
    int num;
    scanf("%d",&n);
    int graph[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            scanf("%d",&num);
            graph[i][j]=num;
        }
    }
    char ch;
    char st1;
    char st2;
    int parent[n];
    while (1){
        scanf(" %c",&ch);
        if (ch=='s'){
            int start;
            scanf("%c%d%c",&st1,&start,&st2);
            prims(graph,start);
            printf("\n");
        }
        else if (ch=='t'){
            totalWeight(graph);
        }
        else if (ch=='x')
            break;
        
    }
    return 1;
}