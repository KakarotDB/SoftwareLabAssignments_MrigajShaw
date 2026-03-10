#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    struct Node *next;
    int vertex;
    int weight;
} Node;

Node **createAdjacencyList(int vertices) {
    Node **list = (Node **)malloc(vertices * sizeof(Node *));
    for (int i = 0; i < vertices; i++) {
        list[i] = NULL;
    }
    return list;
}

bool addEdgeAdjacencyListDirectedWithoutWeight(Node **list, int u, int v) {
    if (list == NULL)
        return false;
	Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        return false;

    newNode->vertex = v;
    newNode->weight = 0;
    newNode->next = list[u];
    list[u] = newNode;

    return true;
}

bool addEdgeAdjacencyListUnDirectedWithoutWeight(Node **list, int u, int v) {
    if (!addEdgeAdjacencyListDirectedWithoutWeight(list, u, v))
        return false;
    if (!addEdgeAdjacencyListDirectedWithoutWeight(list, v, u))
        return false;
    return true;
}

bool addEdgeAdjacencyListDirectedWithWeight(Node **list, int u, int v,
                                            int weight) {
    if (list == NULL)
        return false;

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        return false;

    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = list[u];
    list[u] = newNode;

    return true;
}

bool addEdgeAdjacencyListUnDirectedWithWeight(Node **list, int u, int v,
                                              int weight) {
    if (!addEdgeAdjacencyListDirectedWithWeight(list, u, v, weight))
        return false;
    if (!addEdgeAdjacencyListDirectedWithWeight(list, v, u, weight))
        return false;
    return true;
}

void displayAdjacencyList(Node **list, int vertices) {
    printf("\nAdjacency List Representation\n");
    printf("------------------------------\n");
    for (int i = 0; i < vertices; i++) {
        printf("Vertex [%d]: ", i);
        Node *temp = list[i];

        while (temp != NULL) {
            printf("%d(w:%d) -> ", temp->vertex, temp->weight);
            temp = temp->next;
        }
    printf("NULL\n");
    }
    printf("------------------------------------\n");
}

void freeAdjacencyList(Node **list, int vertices) {
    if (list == NULL)
        return;

    for (int i = 0; i < vertices; i++) {
        Node *current = list[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(list);
}

int main() {
    int n = 100; // number of vertices
    // the vertices are [0, 99];
    srand(time(NULL));
    Node **list = createAdjacencyList(n);

	//Adjacency list
    for (int i = 0; i < n; i++) {
        int u = rand() % 100;
        int v = rand() % 100;
        addEdgeAdjacencyListUnDirectedWithoutWeight(list, u, v);
    }

    displayAdjacencyList(list, n);

	int edges_sparse = 120;
    for (int i = 0; i < edges_sparse; i++) {
        int u = rand() % 100;
        int v = rand() % 100;
        int weight = rand() % 50 + 1;
        addEdgeAdjacencyListUnDirectedWithWeight(list, u, v, weight);
    }

    displayAdjacencyList(list, n);

    freeAdjacencyList(list, n);

	//Adjacency Matrix 
	
		
    return 0;
}
