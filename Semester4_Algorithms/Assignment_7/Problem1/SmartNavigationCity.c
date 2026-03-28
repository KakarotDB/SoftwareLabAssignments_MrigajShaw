#include "../../Assignment_6/AdjacencyList/AdjacencyList.h"
#include "../../Assignment_6/MinHeap/MinHeap.h"
#include <stdio.h>

void dijkstra(Node **adjList, int vertices, int startNode) {
    int dist[vertices];
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX; // representing infinity
    }
    dist[startNode] = 0;

    /* We use a capacity of edges * 2 because the "Lazy Deletion" approach
       may store multiple distance entries for the same vertex in the heap
       before they are processed. */
    MinHeap *pq = createMinHeap(200);

    /* Repurposing the Edge struct: u = -1 (unused), v = vertex, weight =
     * distance */
    insertMinHeap(pq, -1, startNode, 0);

    printf("\nRunning Dijkstra starting from Vertex %d...\n", startNode);

    while (!isEmpty(pq)) {
        Edge current = extractMin(pq);
        int u = current.v;
        int d = current.weight;

        // Skip this node if we already found a shorter path previously.
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

    printf("\nShortest Distances from Source %d:\n", startNode);
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

    Node **AdjacencyList = createAdjacencyList(vertices);
    if (!AdjacencyList) {
        printf("[ERROR] Adjacency list initialization failed\n");
        return -1;
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
        if (u >= vertices || v >= vertices || u < 0 || v < 0) {
            printf("Invalid vertex index! Skipping edge.\n");
            continue;
        }
        addEdgeAdjacencyListDirectedWithWeight(AdjacencyList, u, v, w);
    }

    displayAdjacencyList(AdjacencyList, vertices);

    int startNode;
    printf("Enter source vertex for Dijkstra: ");
    scanf("%d", &startNode);

    if (startNode >= 0 && startNode < vertices) {
        dijkstra(AdjacencyList, vertices, startNode);
    } else {
        printf("Invalid source vertex.\n");
    }

    freeAdjacencyList(AdjacencyList, vertices);
    return 0;
}
