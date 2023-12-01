#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int dest;
    int weight;
    struct Node* next;
};


struct AdjList {
    struct Node* head;
};


struct Graph {
    int vertices;
    struct AdjList* array;
};


struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->dest = dest;
        newNode->weight = weight;
        newNode->next = NULL;
    }
    return newNode;
}


struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph != NULL) {
        graph->vertices = vertices;
        graph->array = (struct AdjList*)malloc(vertices * sizeof(struct AdjList));
        if (graph->array == NULL) {
            free(graph);
            return NULL;
        }

        for (int i = 0; i < vertices; i++) {
            graph->array[i].head = NULL;
        }
    }
    return graph;
}


void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}


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


void dijkstra(struct Graph* graph, int src) {
    int* distance = (int*)malloc(graph->vertices * sizeof(int));
    int* sptSet = (int*)malloc(graph->vertices * sizeof(int));

    
    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INT_MAX;
        sptSet[i] = 0;
    }

    
    distance[src] = 0;

    
    for (int count = 0; count < graph->vertices - 1; count++) {
        
        int u = minDistance(distance, sptSet, graph->vertices);

       
        sptSet[u] = 1;

        
        struct Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            if (!sptSet[v] && distance[u] != INT_MAX && distance[u] + temp->weight < distance[v]) {
                distance[v] = distance[u] + temp->weight;
            }
            temp = temp->next;
        }
    }

    
    printShortestDistances(distance, graph->vertices);

    free(distance);
    free(sptSet);
}


void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        struct Node* temp = graph->array[i].head;
        while (temp != NULL) {
            struct Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
    int vertices, edges, src;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    printf("Enter the edges and weights (format: source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        addEdge(graph, source, destination, weight);
    }

    printf("Enter the source vertex for Dijkstra's algorithm: ");
    scanf("%d", &src);

    printf("Shortest Distances from Source Vertex %d:\n", src);
    dijkstra(graph, src);

    freeGraph(graph);

    return 0;
}
