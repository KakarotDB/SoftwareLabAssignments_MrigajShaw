#include "../../Assignment_5/DisjointSetUnion/DisjointSetUnion.h"
#include "../AdjacencyList/AdjacencyList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
    int weight;
} GraphEdge;

// helper for qsort to sort edges by weight ascending
int compareEdges(const void *a, const void *b) {
    GraphEdge *edgeA = (GraphEdge *)a;
    GraphEdge *edgeB = (GraphEdge *)b;
    return edgeA->weight - edgeB->weight;
}

int main() {
    int V = 6; // map C1-C6 to indices 0-5

    Node **adjacencyList = createAdjacencyList(V);

    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 0, 1, 3);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 0, 2, 1);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 0, 3, 6);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 1, 2, 5);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 1, 4, 3);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 2, 3, 5);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 2, 5, 4);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 3, 5, 2);
    addEdgeAdjacencyListUnDirectedWithWeight(adjacencyList, 4, 5, 6);

    // convert adjacency list to a flat edge array for kruskal's
    int max_edges = V * (V - 1) / 2;
    GraphEdge *edges = (GraphEdge *)malloc(max_edges * sizeof(GraphEdge));
    int edge_count = 0;

    for (int i = 0; i < V; i++) {
        Node *temp = adjacencyList[i];
        while (temp != NULL) {
            // i < vertex check stops us from adding reverse edges (like 1->0)
            // twice
            if (i < temp->vertex) {
                edges[edge_count].u = i;
                edges[edge_count].v = temp->vertex;
                edges[edge_count].weight = temp->weight;
                edge_count++;
            }
            temp = temp->next;
        }
    }

    qsort(edges, edge_count, sizeof(GraphEdge), compareEdges);

    DisjointSet *ds = createSet(V);

    int mst_edges_count = 0;
    int current_edge_idx = 0;
    int total_cost = 0;

    printf("\nEdges included in the Minimum Spanning Tree (MST):\n");
    printf("--------------------------------------------------\n");

    // stop when we have exactly V-1 edges connected
    while (mst_edges_count < V - 1 && current_edge_idx < edge_count) {
        GraphEdge next_edge = edges[current_edge_idx++];

        int rootU = find(ds, next_edge.u);
        int rootV = find(ds, next_edge.v);

        // only add if they don't share a parent (prevents cycles)
        if (rootU != rootV) {
            mst_edges_count++;
            total_cost += next_edge.weight;

            unionSets(ds, next_edge.u, next_edge.v);

            // +1 to convert indices back to C1, C2 etc.
            printf("Edge: C%d - C%d \t Cost: %d lakhs\n", next_edge.u + 1,
                   next_edge.v + 1, next_edge.weight);
        }
    }

    printf("--------------------------------------------------\n");
    printf("Total Minimum Cost: %d lakhs\n\n", total_cost);

    // cleanup memory
    freeSet(ds);
    free(edges);
    freeAdjacencyList(adjacencyList, V);

    return 0;
}
