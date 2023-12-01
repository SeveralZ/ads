#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};


struct AdjList {
    struct Node* head;
};


struct Graph {
    int vertices;
    struct AdjList* array;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
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


void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

   
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}


void DFS(struct Graph* graph, int vertex, int* visited) {
    printf("%d ", vertex);
    visited[vertex] = 1;

    struct Node* temp = graph->array[vertex].head;
    while (temp != NULL) {
        if (!visited[temp->data]) {
            DFS(graph, temp->data, visited);
        }
        temp = temp->next;
    }
}


void BFS(struct Graph* graph, int startVertex, int* visited) {
    int* queue = (int*)malloc(graph->vertices * sizeof(int));
    int front = 0, rear = 0;

    printf("BFS Traversal: ");
    printf("%d ", startVertex);
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];

        struct Node* temp = graph->array[currentVertex].head;
        while (temp != NULL) {
            if (!visited[temp->data]) {
                printf("%d ", temp->data);
                visited[temp->data] = 1;
                queue[rear++] = temp->data;
            }
            temp = temp->next;
        }
    }

    printf("\n");

    free(queue);
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
    int vertices, edges;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    
    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    printf("Enter the edges (format: source destination):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination;
        scanf("%d %d", &source, &destination);
        addEdge(graph, source, destination);
    }

 
    int* visited = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0; 
    }

    int startVertex;

    printf("Enter the starting vertex for DFS and BFS: ");
    scanf("%d", &startVertex);

    printf("\nDFS Traversal: ");
    DFS(graph, startVertex, visited);
    printf("\n");

   
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }

    BFS(graph, startVertex, visited);

    
    freeGraph(graph);
    free(visited);

    return 0;
}
