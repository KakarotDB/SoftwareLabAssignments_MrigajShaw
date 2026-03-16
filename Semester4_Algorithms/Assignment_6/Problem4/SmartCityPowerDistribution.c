#include "../../Assignment_5/DisjointSetUnion/DisjointSetUnion.h"
#include "../AdjacencyList/AdjacencyList.h"
#include "../MinHeap/MinHeap.h"
#include <stdio.h>
#include <stdlib.h>

// struct just for G1 edge list
typedef struct {
    int u, v, weight;
} GraphEdge;

// sort helper for qsort (ascending weight)
int compareEdges(const void *a, const void *b) {
    return ((GraphEdge *)a)->weight - ((GraphEdge *)b)->weight;
}

int main() {
    int V1, E1, V2, E2;

    // input G1 as sparse (using flat array for kruskal's)
    printf("Enter V1 and E1 for Graph G1: ");
    scanf("%d %d", &V1, &E1);

    GraphEdge *edgesG1 = (GraphEdge *)malloc(E1 * sizeof(GraphEdge));
    printf("Enter %d edges for G1 (u v weight):\n", E1);
    for (int i = 0; i < E1; i++) {
        scanf("%d %d %d", &edgesG1[i].u, &edgesG1[i].v, &edgesG1[i].weight);
    }

    // input G2 as dense (using adjacency list for prim's)
    printf("\nEnter V2 and E2 for Graph G2: ");
    scanf("%d %d", &V2, &E2);

    Node **adjListG2 = createAdjacencyList(V2);
    printf("Enter %d edges for G2 (u v weight):\n", E2);
    for (int i = 0; i < E2; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdgeAdjacencyListUnDirectedWithWeight(adjListG2, u, v, w);
    }

    // mandatory bridge edge
    int connect_u, connect_v, connect_weight;
    printf("\nEnter mandatory connecting edge (u_in_G1 v_in_G2 weight): ");
    scanf("%d %d %d", &connect_u, &connect_v, &connect_weight);

    int total_cost = 0;
    printf("\n==================================================\n");
    printf("       GLOBAL MINIMUM SPANNING TREE (MST)\n");
    printf("===============================================\n");

    // Phase 1: Kruskal's on G1
    printf("\n[Graph G1 - Kruskal's MST]\n");
    qsort(edgesG1, E1, sizeof(GraphEdge), compareEdges);
    DisjointSet *ds = createSet(V1);
    int mst1_edges = 0;

    for (int i = 0; i < E1 && mst1_edges < V1 - 1; i++) {
        int rootU = find(ds, edgesG1[i].u);
        int rootV = find(ds, edgesG1[i].v);

        // if roots differ, no cycle
        if (rootU != rootV) {
            unionSets(ds, edgesG1[i].u, edgesG1[i].v);
            printf("G1 Edge: %2d - %2d \t Cost: %d\n", edgesG1[i].u,
                   edgesG1[i].v, edgesG1[i].weight);
            total_cost += edgesG1[i].weight;
            mst1_edges++;
        }
    }

    // Phase 2: Prim's on G2
    printf("\n[Graph G2 - Prim's MST]\n");
    bool *visited = (bool *)calloc(V2, sizeof(bool));

    // allocate extra space for dense graph edges
    MinHeap *pq = createMinHeap(E2 * 2);
    int mst2_edges = 0;

    // start from vertex 0
    visited[0] = true;
    Node *temp = adjListG2[0];
    while (temp != NULL) {
        insertMinHeap(pq, 0, temp->vertex, temp->weight);
        temp = temp->next;
    }

    while (!isEmpty(pq) && mst2_edges < V2 - 1) {
        Edge minEdge = extractMin(pq);

        if (visited[minEdge.v])
            continue; // cycle check

        visited[minEdge.v] = true;
        printf("G2 Edge: %2d - %2d \t Cost: %d\n", minEdge.u, minEdge.v,
               minEdge.weight);
        total_cost += minEdge.weight;
        mst2_edges++;

        // push unvisited neighbors
        temp = adjListG2[minEdge.v];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                insertMinHeap(pq, minEdge.v, temp->vertex, temp->weight);
            }
            temp = temp->next;
        }
    }

    // Phase 3: Combine with mandatory edge
    printf("\n[Interconnecting Transmission Edge]\n");
    printf("Link: G1(%d) - G2(%d) \t Cost: %d\n", connect_u, connect_v,
           connect_weight);
    total_cost += connect_weight;

    printf("--------------------------------------------------\n");
    printf("Total Cost of Global MST: %d\n\n", total_cost);

    // cleanup
    freeSet(ds);
    free(edgesG1);
    free(visited);
    freeMinHeap(pq);
    freeAdjacencyList(adjListG2, V2);

    return 0;
}
