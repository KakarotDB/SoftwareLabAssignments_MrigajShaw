#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, weight;
} Edge;

void bellmanFord(Edge *edges, int V, int E, int source) {
    int *dist = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;

    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int weight = edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("\nGraph contains a negative weight cycle! Shortest paths "
                   "are undefined.\n");
            free(dist);
            return;
        }
    }

    printf("\nVertex \t Distance from Source (%d)\n", source);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d \t INF\n", i);
        } else {
            printf("%d \t %d\n", i, dist[i]);
        }
    }

    free(dist);
}

int main() {
    int V, E, source;

    printf("Enter number of vertices: ");
    if (scanf("%d", &V) != 1)
        return 1;

    printf("Enter number of edges: ");
    if (scanf("%d", &E) != 1)
        return 1;

    // Just allocate a flat array of edges directly in main
    Edge *edges = (Edge *)malloc(E * sizeof(Edge));

    printf("Enter %d edges (format: source destination weight):\n", E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    printf("Enter the source vertex: ");
    if (scanf("%d", &source) != 1)
        return 1;

    bellmanFord(edges, V, E, source);

    free(edges);

    return 0;
}
