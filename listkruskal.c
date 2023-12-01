#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct Node {
    int dest;
    int weight;
    struct Node* next;
};


struct DisjointSet {
    int* parent;
    int* rank;
};


struct Edge {
    int src, dest, weight;
};


struct Graph {
    int vertices, edges;
    struct Node** array;
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


struct Graph* createGraph(int vertices, int edges) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph != NULL) {
        graph->vertices = vertices;
        graph->edges = edges;
        graph->array = (struct Node**)malloc(vertices * sizeof(struct Node*));
        if (graph->array == NULL) {
            free(graph);
            return NULL;
        }

        for (int i = 0; i < vertices; i++) {
            graph->array[i] = NULL;
        }
    }
    return graph;
}


void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}


struct DisjointSet* createDisjointSet(int vertices) {
    struct DisjointSet* set = (struct DisjointSet*)malloc(sizeof(struct DisjointSet));
    if (set != NULL) {
        set->parent = (int*)malloc(vertices * sizeof(int));
        set->rank = (int*)malloc(vertices * sizeof(int));

        if (set->parent == NULL || set->rank == NULL) {
            free(set->parent);
            free(set->rank);
            free(set);
            return NULL;
        }

        for (int i = 0; i < vertices; i++) {
            set->parent[i] = i;
            set->rank[i] = 0;
        }
    }
    return set;
}


int find(struct DisjointSet* set, int i) {
    if (i != set->parent[i]) {
        set->parent[i] = find(set, set->parent[i]); 
    }
    return set->parent[i];
}


void unionSets(struct DisjointSet* set, int x, int y) {
    int rootX = find(set, x);
    int rootY = find(set, y);

    if (set->rank[rootX] < set->rank[rootY]) {
        set->parent[rootX] = rootY;
    } else if (set->rank[rootX] > set->rank[rootY]) {
        set->parent[rootY] = rootX;
    } else {
        set->parent[rootY] = rootX;
        set->rank[rootX]++;
    }
}


int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}


void kruskal(struct Graph* graph) {
    int vertices = graph->vertices;
    struct Edge* result = (struct Edge*)malloc((vertices - 1) * sizeof(struct Edge));
    int e = 0; 
    int i = 0; 

    
    struct Edge* edges = (struct Edge*)malloc(graph->edges * sizeof(struct Edge));
    for (int u = 0; u < vertices; u++) {
        struct Node* temp = graph->array[u];
        while (temp != NULL) {
            if (u < temp->dest) {
                edges[i].src = u;
                edges[i].dest = temp->dest;
                edges[i].weight = temp->weight;
                i++;
            }
            temp = temp->next;
        }
    }

    qsort(edges, graph->edges, sizeof(struct Edge), compareEdges);

   
    struct DisjointSet* set = createDisjointSet(vertices);

   
    while (e < vertices - 1 && i < graph->edges) {
        struct Edge nextEdge = edges[i++];

        int x = find(set, nextEdge.src);
        int y = find(set, nextEdge.dest);

        
        if (x != y) {
            result[e++] = nextEdge;
            unionSets(set, x, y);
        }
    }

   
    printf("Minimum Spanning Tree (MST) using Kruskal's Algorithm:\n");
    for (int j = 0; j < e; j++) {
        printf("Edge %d - %d   Weight %d\n", result[j].src, result[j].dest, result[j].weight);
    }

   
    free(set->parent);
    free(set->rank);
    free(set);
    free(result);
    free(edges);
}


void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        struct Node* temp = graph->array[i];
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

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    
    struct Graph* graph = createGraph(vertices, edges);

    printf("Enter the edges and weights (format: source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        addEdge(graph, source, destination, weight);
    }

   
    kruskal(graph);

    
    freeGraph(graph);

    return 0;
}
