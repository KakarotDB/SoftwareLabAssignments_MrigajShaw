#include "../../Assignment_6/AdjacencyList/AdjacencyList.h"
#include "../../Assignment_6/MinHeap/MinHeap.h"
#include <limits.h>
#include <stdio.h>
#include <time.h>

void dijkstraList(Node **adjList, int vertices, int startNode) {
    int dist[vertices];
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[startNode] = 0;

    MinHeap *pq = createMinHeap(200);
    insertMinHeap(pq, -1, startNode, 0);

    while (!isEmpty(pq)) {
        Edge current = extractMin(pq);
        int u = current.v;
        int d = current.weight;

        if (d > dist[u])
            continue;

        Node *temp = adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                insertMinHeap(pq, u, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\n[List] Shortest Distances from Source %d:\n", startNode);
    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INT_MAX)
            printf("Vertex %d: Unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
    freeMinHeap(pq);
}

void dijkstraMatrix(int vertices, int matrix[vertices][vertices],
                    int startNode) {
    int dist[vertices];
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[startNode] = 0;

    MinHeap *pq = createMinHeap(200);
    insertMinHeap(pq, -1, startNode, 0);

    while (!isEmpty(pq)) {
        Edge current = extractMin(pq);
        int u = current.v;
        int d = current.weight;

        if (d > dist[u])
            continue;

        for (int v = 0; v < vertices; v++) {
            if (matrix[u][v] != INT_MAX) {
                int weight = matrix[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    insertMinHeap(pq, u, v, dist[v]);
                }
            }
        }
    }

    printf("\n[Matrix] Shortest Distances from Source %d:\n", startNode);
    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INT_MAX)
            printf("Vertex %d: Unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
    freeMinHeap(pq);
}

int main() {
    int vertices = 10;
    int edges = 0;
    int u, v, w;
    clock_t start_time, end_time;
    double time_list, time_matrix;

    Node **AdjacencyList = createAdjacencyList(vertices);
    if (!AdjacencyList) {
        printf("[ERROR] Adjacency list initialization failed\n");
        return -1;
    }

    int AdjacencyMatrix[vertices][vertices];
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                AdjacencyMatrix[i][j] = 0;
            } else {
                AdjacencyMatrix[i][j] = INT_MAX;
            }
        }
    }

    printf("Enter number of edges (max 90): ");
    if (scanf("%d", &edges) != 1 || edges > 90) {
        printf("Invalid edge count.\n");
        return -1;
    }

    printf("Enter edges (u v w) where u, v < 10:\n");
    for (int i = 0; i < edges; i++) {
        if (scanf("%d %d %d", &u, &v, &w) != 3)
            break;
        if (u >= vertices || v >= vertices || u < 0 || v < 0 || w < 0) {
            printf("Invalid vertex index/negative weight! Skipping edge.\n");
            continue;
        }

        addEdgeAdjacencyListDirectedWithWeight(AdjacencyList, u, v, w);
        AdjacencyMatrix[u][v] = w;
    }

    displayAdjacencyList(AdjacencyList, vertices);

    int startNode;
    printf("Enter source vertex for Dijkstra: ");
    scanf("%d", &startNode);

    if (startNode >= 0 && startNode < vertices) {

        start_time = clock();
        dijkstraList(AdjacencyList, vertices, startNode);
        end_time = clock();
        time_list = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        start_time = clock();
        dijkstraMatrix(vertices, AdjacencyMatrix, startNode);
        end_time = clock();
        time_matrix = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("\nPerformance Evaluation\n");
        printf("Adjacency List Execution Time: %f seconds\n", time_list);
        printf("Adjacency Matrix Execution Time: %f seconds\n", time_matrix);

    } else {
        printf("Invalid source vertex.\n");
    }

    freeAdjacencyList(AdjacencyList, vertices);
    return 0;
}
