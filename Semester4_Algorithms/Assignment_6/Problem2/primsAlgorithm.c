#include "../AdjacencyList/AdjacencyList.h"
#include "../MinHeap/MinHeap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 6; // 6 cities (C1 to C6)
    Node **adjacencyList = createAdjacencyList(n);

    // mapping C1->0, C2->1, C3->2, C4->3, C5->4, C6->5 to make indexing easier
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 0, 1, 3);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 0, 2, 1);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 0, 3, 6);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 1, 2, 5);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 1, 4, 3);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 2, 3, 5);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 2, 5, 4);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 3, 5, 2);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 4, 5, 6);

    // Prim's Algo setup
    bool visited[6] = {false};
    int total_cost = 0;
    int edges_added = 0;

    // array to track the order of cities we visit
    int order[6];
    int order_idx = 0;

    // queue size is large enough to hold all possible edges
    MinHeap *pq = createMinHeap(100);

    // Start from C1 (which is index 0)
    visited[0] = true;
    order[order_idx++] = 0;

    // throw all initial edges from C1 into the priority queue
    Node *temp = adjacencyList[0];
    while (temp != NULL) {
        insertMinHeap(pq, 0, temp->vertex, temp->weight);
        temp = temp->next;
    }

    printf("\nEdges in the Minimum Spanning Tree (MST):\n");
    printf("-----------------------------------------\n");

    // run until we connect all V-1 edges (6 cities = 5 edges)
    while (!isEmpty(pq) && edges_added < n - 1) {
        Edge minEdge = extractMin(pq);

        // if the destination city is already in the MST, skip it
        if (visited[minEdge.v]) {
            continue;
        }

        // Add edge to our MST
        visited[minEdge.v] = true;
        total_cost += minEdge.weight;
        edges_added++;
        order[order_idx++] = minEdge.v; // record the order

        printf("C%d - C%d \t Cost: %d lakhs\n", minEdge.u + 1, minEdge.v + 1,
               minEdge.weight);

        // push all adjacent edges of the new city into the heap
        temp = adjacencyList[minEdge.v];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                insertMinHeap(pq, minEdge.v, temp->vertex, temp->weight);
            }
            temp = temp->next;
        }
    }

    printf("-----------------------------------------\n");
    printf("Total Minimum Cost: %d lakhs\n\n", total_cost);

    printf("Order of vertices added: ");
    for (int i = 0; i < n; i++) {
        printf("C%d", order[i] + 1); // +1 because we mapped 0 to C1
        if (i < n - 1)
            printf(" -> ");
    }
    printf("\n");

    freeMinHeap(pq);
    freeAdjacencyList(adjacencyList, n);

    return 0;
}
