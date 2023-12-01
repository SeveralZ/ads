#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findMinKeyVertex(int key[], int mstSet[], int vertices) {
    int minKey = INT_MAX, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (!mstSet[v] && key[v] < minKey) {
            minKey = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}


void printMST(int parent[], int** graph, int vertices) {
    printf("Edge   Weight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d    %d\n", parent[i], i, graph[i][parent[i]]);
    }
}


void primMST(int** graph, int vertices) {
    int parent[vertices]; 
    int key[vertices];    
    int mstSet[vertices]; 

    
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    
    key[0] = 0;       
    parent[0] = -1;   

    
    for (int count = 0; count < vertices - 1; count++) {
        
        int u = findMinKeyVertex(key, mstSet, vertices);

        
        mstSet[u] = 1;

        
        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    
    printMST(parent, graph, vertices);
}


void freeGraph(int** graph, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(graph[i]);
    }
    free(graph);
}

int main() {
    int vertices, edges;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

   
    int** graph = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    printf("Enter the edges and weights (format: source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        
        graph[source][destination] = weight;
        graph[destination][source] = weight;
    }

    printf("Minimum Spanning Tree (MST) using Prim's Algorithm:\n");
    primMST(graph, vertices);

    
    freeGraph(graph, vertices);

    return 0;
}
