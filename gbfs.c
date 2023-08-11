#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 20

typedef struct {
    int vertices[MAX_VERTICES];
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int heuristicValues[MAX_VERTICES];
    int vertexCount;
} Graph;

void initializeGraph(Graph* graph, int vertexCount) {
    graph->vertexCount = vertexCount;
    for (int i = 0; i < vertexCount; i++) {
        graph->vertices[i] = 0;
        graph->heuristicValues[i] = 0;
        for (int j = 0; j < vertexCount; j++)
            graph->adjacencyMatrix[i][j] = 0;
    }
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = 1;
    graph->adjacencyMatrix[dest][src] = 1;
}

void setHeuristicValue(Graph* graph, int vertex, int heuristicValue) {
    graph->heuristicValues[vertex] = heuristicValue;
}

int getNextVertex(Graph* graph) {
    int minHeuristic = INT_MAX, nextVertex = -1;
    for (int i = 0; i < graph->vertexCount; i++)
        if (graph->vertices[i] == 0 && graph->heuristicValues[i] < minHeuristic) {
            minHeuristic = graph->heuristicValues[i];
            nextVertex = i;
        }
    return nextVertex;
}

void GBFS(Graph* graph, int startVertex, int goalVertex) {
    int currentVertex, parentVertex[MAX_VERTICES] = { -1 };
    bool found = false;
    graph->vertices[startVertex] = 1;

    printf("GBFS traversal from vertex %d to vertex %d: ", startVertex, goalVertex);

    while (!found) {
        currentVertex = getNextVertex(graph);
        if (currentVertex == -1)
            break;

        printf("%d ", currentVertex);

        if (currentVertex == goalVertex) {
            found = true;
            break;
        }

        graph->vertices[currentVertex] = 1;

        for (int i = 0; i < graph->vertexCount; i++)
            if (graph->adjacencyMatrix[currentVertex][i] == 1 && graph->vertices[i] == 0)
                parentVertex[i] = currentVertex;
    }

    if (found) {
        printf("\nPath found: ");
        int path[MAX_VERTICES], pathLength = 0;
        int vertex = goalVertex;
        while (vertex != -1) {
            path[pathLength++] = vertex;
            vertex = parentVertex[vertex];
        }
        for (int i = pathLength - 1; i >= 0; i--)
            printf("%d ", path[i]);
    } else {
        printf("\nPath not found.");
    }

    printf("\n");
}

int main() {
    Graph graph;
    int vertexCount, edges, src, dest;
    int startVertex, goalVertex;

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

    printf("Enter the starting vertex for GBFS: ");
    scanf("%d", &startVertex);

    printf("Enter the goal vertex for GBFS: ");
    scanf("%d", &goalVertex);

    printf("Enter the heuristic values for each vertex:\n");
    for (int i = 0; i < vertexCount; i++) {
        int heuristic;
        scanf("%d", &heuristic);
        setHeuristicValue(&graph, i, heuristic);
    }

    GBFS(&graph, startVertex, goalVertex);

    return 0;
}
