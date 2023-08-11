#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct {
    int vertices[MAX_VERTICES];
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int vertexCount;
} Graph;

// Function to initialize the graph
void initializeGraph(Graph* graph, int vertexCount) {
    graph->vertexCount = vertexCount;

    for (int i = 0; i < vertexCount; i++) {
        graph->vertices[i] = 0;
        for (int j = 0; j < vertexCount; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = 1;
    graph->adjacencyMatrix[dest][src] = 1;
}

// Function to perform DFS traversal recursively
void DFS(Graph* graph, int vertex) {
    printf("%d ", vertex);
    graph->vertices[vertex] = 1;

    for (int i = 0; i < graph->vertexCount; i++) {
        if (graph->adjacencyMatrix[vertex][i] == 1 && graph->vertices[i] == 0) {
            DFS(graph, i);
        }
    }
}

int main() {
    Graph graph;
    int vertexCount, edges, src, dest;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertexCount);

    initializeGraph(&graph, vertexCount);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(&graph, src, dest);
    }

    int startVertex;
    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);

    printf("DFS traversal starting from vertex %d: ", startVertex);
    DFS(&graph, startVertex);
    printf("\n");

    return 0;
}
