#include <stdio.h>
#include <stdlib.h>


#define MAX_VERTICES 100


struct Queue {
    int front, rear;
    int capacity;
    int* array;
};


struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue != NULL) {
        queue->front = 0;
        queue->rear = -1;
        queue->capacity = capacity;
        queue->array = (int*)malloc(capacity * sizeof(int));
        if (queue->array == NULL) {
            free(queue);
            return NULL;
        }
    }
    return queue;
}


int isEmpty(struct Queue* queue) {
    return queue->front > queue->rear;
}


void enqueue(struct Queue* queue, int item) {
    queue->array[++queue->rear] = item;
}


int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return -1; 
    }
    return queue->array[queue->front++];
}


void freeQueue(struct Queue* queue) {
    free(queue->array);
    free(queue);
}


void DFS(int vertex, int* visited, int** graph, int vertices) {
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && graph[vertex][i]) {
            DFS(i, visited, graph, vertices);
        }
    }
}


void BFS(int startVertex, int* visited, int** graph, int vertices) {
    struct Queue* queue = createQueue(vertices);
    if (queue == NULL) {
        return; 
    }

    printf("BFS Traversal: ");

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; i++) {
            if (!visited[i] && graph[currentVertex][i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }

    printf("\n");

    freeQueue(queue);
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

    printf("Enter the edges (format: source destination):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination;
        scanf("%d %d", &source, &destination);
        graph[source][destination] = 1;
        graph[destination][source] = 1;
    }

    
    int* visited = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0; 
    }

    int startVertex;

    printf("Enter the starting vertex for DFS and BFS: ");
    scanf("%d", &startVertex);

    printf("\nDFS Traversal: ");
    DFS(startVertex, visited, graph, vertices);
    printf("\n");

    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }

    BFS(startVertex, visited, graph, vertices);

   
    freeGraph(graph, vertices);
    free(visited);

    return 0;
}
