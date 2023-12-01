#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int minDistance(int distance[], int sptSet[], int vertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++) {
        if (!sptSet[v] && distance[v] < min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}


void printShortestDistances(int distance[], int vertices) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d        %d\n", i, distance[i]);
    }
}


void dijkstra(int** graph, int src, int dest, int vertices) {
    int* distance = (int*)malloc(vertices * sizeof(int));
    int* sptSet = (int*)malloc(vertices * sizeof(int));

   
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        sptSet[i] = 0;
    }

    
    distance[src] = 0;

    
    for (int count = 0; count < vertices - 1; count++) {
        
        int u = minDistance(distance, sptSet, vertices);

        
        sptSet[u] = 1;

        
        for (int v = 0; v < vertices; v++) {
            if (!sptSet[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

  
    printf("Shortest Distance from Source Vertex %d to Destination Vertex %d: %d\n", src, dest, distance[dest]);

    free(distance);
    free(sptSet);
}


void freeGraph(int** graph, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(graph[i]);
    }
    free(graph);
}

int main() {
    int vertices, edges, src, dest;

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

    printf("Enter the source and destination vertices for Dijkstra's algorithm: ");
    scanf("%d %d", &src, &dest);

    dijkstra(graph, src, dest, vertices);

    
    freeGraph(graph, vertices);

    return 0;
}
