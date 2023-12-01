#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct Edge {
    int src, dest, weight;
};


struct DisjointSet {
    int* parent;
    int* rank;
};


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


void kruskal(int** graph, int vertices, int edges) {
    struct Edge* result = (struct Edge*)malloc((vertices - 1) * sizeof(struct Edge));
    struct Edge* edgesArray = (struct Edge*)malloc(edges * sizeof(struct Edge));

    for (int i = 0, k = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (graph[i][j] != 0 && i < j) {
                edgesArray[k].src = i;
                edgesArray[k].dest = j;
                edgesArray[k].weight = graph[i][j];
                k++;
            }
        }
    }

    
    qsort(edgesArray, edges, sizeof(struct Edge), compareEdges);

    
    struct DisjointSet* set = createDisjointSet(vertices);

    int e = 0; 
    int i = 0; 

    
    while (e < vertices - 1 && i < edges) {
        struct Edge nextEdge = edgesArray[i++];

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
    free(edgesArray);
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

    kruskal(graph, vertices, edges);

    
    freeGraph(graph, vertices);

    return 0;
}
