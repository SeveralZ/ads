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


struct MinHeapNode {
    int vertex;
    int key;
};


struct MinHeap {
    int capacity;
    int size;
    struct MinHeapNode** array;
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

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}


struct MinHeapNode* createMinHeapNode(int vertex, int key) {
    struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    if (newNode != NULL) {
        newNode->vertex = vertex;
        newNode->key = key;
    }
    return newNode;
}


struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    if (minHeap != NULL) {
        minHeap->capacity = capacity;
        minHeap->size = 0;
        minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    }
    return minHeap;
}


void swapMinHeapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}


void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key) {
        smallest = right;
    }

    if (smallest != idx) {
        swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}


int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}


struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
    }

    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->size--;

    minHeapify(minHeap, 0);

    return root;
}


void decreaseKey(struct MinHeap* minHeap, int vertex, int key) {
    int i;
    for (i = 0; i < minHeap->size; i++) {
        if (minHeap->array[i]->vertex == vertex) {
            break;
        }
    }

    minHeap->array[i]->key = key;

    while (i != 0 && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        swapMinHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


int isInMinHeap(struct MinHeap* minHeap, int vertex) {
    for (int i = 0; i < minHeap->size; i++) {
        if (minHeap->array[i]->vertex == vertex) {
            return 1;
        }
    }
    return 0;
}


void printMST(int parent[], struct Graph* graph) {
    printf("Edge   Weight\n");
    for (int i = 1; i < graph->vertices; i++) {
        printf("%d - %d    %d\n", parent[i], i, graph->array[i].head->weight);
    }
}


void primMST(struct Graph* graph) {
    int parent[graph->vertices];
    int key[graph->vertices];
    struct MinHeap* minHeap = createMinHeap(graph->vertices);

    for (int i = 1; i < graph->vertices; i++) {
        parent[i] = -1;
        key[i] = INT_MAX;
        minHeap->array[i] = createMinHeapNode(i, key[i]);
        minHeap->size++;
    }

    key[0] = 0;
    minHeap->array[0] = createMinHeapNode(0, key[0]);

    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        struct Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            if (isInMinHeap(minHeap, v) && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            temp = temp->next;
        }
    }

    printMST(parent, graph);
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

    printf("Enter the edges and weights (format: source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        addEdge(graph, source, destination, weight);
    }

    printf("Minimum Spanning Tree (MST) using Prim's Algorithm:\n");
    primMST(graph);

    
    freeGraph(graph);

    return 0;
}
