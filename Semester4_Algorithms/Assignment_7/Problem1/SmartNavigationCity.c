#include "../../Assignment_6/AdjacencyList/AdjacencyList.h"
#include "../../Assignment_6/MinHeap/MinHeap.h"
#include <stdio.h>

int main() {
	int vertices = 10; //10 vertices 
	int edges = 0;
	int u = 0, v = 0, w = 0;
	Node** AdjacencyList = createAdjacencyList(vertices);

	if(!AdjacencyList) {
		printf("[ERROR] Couldn't initialize adjacency list : Null error\n");
		return -1;
	}

	printf("Enter number of edges (upto 90): ");
	scanf("%d", &edges);

	if(edges > 90) {
		printf("Can't have more than 90 edges! Program terminating...\n");
		return -1;
	}

	printf("Enter edges in the format (u v w), where u and v <= 9, w is the weight of the edge\n");

	for(int i = 0; i < edges; i++) {
		scanf("%d %d %d", &u, &v, &w);
		if(u >= 9 || v >= 9) {
			printf("Only 10 vertices exist! Program exiting...\n");
			return -1;
		}
		addEdgeAdjacencyListDirectedWithWeight(AdjacencyList, u, v, w);
	}

	displayAdjacencyList(AdjacencyList, vertices);



	freeMinHeap(heap);
	freeAdjacencyList(AdjacencyList);
	return 0;
}
