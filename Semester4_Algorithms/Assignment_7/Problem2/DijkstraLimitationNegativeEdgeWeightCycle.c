#include "../../Assignment_6/AdjacencyList/AdjacencyList.h"
#include "../../Assignment_6/MinHeap/MinHeap.h"
#include <limits.h>
#include <stdio.h>

void dijkstraList(Node **adjList, int vertices, int startNode) {
    int dist[vertices];
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[startNode] = 0;

    MinHeap *pq = createMinHeap(1000);
    insertMinHeap(pq, -1, startNode, 0);

    int extraction_count = 0;
    int max_safe_extractions = 200; // Circuit breaker to prevent infinite loops

    printf("\nStarting Dijkstra from vertex %d...\n", startNode);

    while (!isEmpty(pq)) {
        Edge current = extractMin(pq);
        int u = current.v;
        int d = current.weight;

        extraction_count++;

        if (extraction_count > max_safe_extractions) {
            printf("\n[ABORT] Infinite loop detected!\n");
            printf("Extraction count exceeded %d. Negative cycle exists.\n",
                   max_safe_extractions);
            break;
        }

        if (d > dist[u])
            continue;

        Node *temp = adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;

                // Print the update to observe the algorithm failing
                printf("Update: dist[%d] dropped to %d (via %d)\n", v, dist[v],
                       u);

                insertMinHeap(pq, u, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\nFinal Distances (Likely Incorrect or Incomplete):\n");
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
    if (!AdjacencyList)
        return -1;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v w) - Negative weights allowed:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdgeAdjacencyListDirectedWithWeight(AdjacencyList, u, v, w);
    }

    int startNode;
    printf("Enter source vertex: ");
    scanf("%d", &startNode);

    if (startNode >= 0 && startNode < vertices) {
        dijkstraList(AdjacencyList, vertices, startNode);
    }

    freeAdjacencyList(AdjacencyList, vertices);
    return 0;
}
