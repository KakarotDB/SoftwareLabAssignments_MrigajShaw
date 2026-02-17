#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int *parent;
	int *rank;
	int n;
} DisjointSet;

DisjointSet* createSet(int n) {
	DisjointSet* disjoint = (DisjointSet*) malloc(n * sizeof(DisjointSet));
	disjoint->n = n;
	disjoint->parent = (int*) malloc(n * sizeof(int));
	disjoint->rank = (int*) malloc(n * sizeof(int));

	for(int i = 0; i < n; i++) {
		disjoint->parent[i] = i;
		disjoint->rank[i] = 0;
	}
	return disjoint;
}

int find(DisjointSet *ds, int i) {
	if(ds->parent[i] != i){
		ds->parent[i] = find(ds, ds->parent[i]);
	}
	return ds->parent[i];
}

bool unionSets(DisjointSet *ds, int a, int b) {
	int rootA = find(ds, a);
	int rootB = find(ds, b);

	if(rootA != rootB) {
		if(ds->rank[rootA] < ds->rank[rootB]) {
			ds->parent[rootA] = rootB;
		} else if(ds->rank[rootA] > ds->rank[rootB]) {
			ds->parent[rootB] = rootA;
		} else {
			ds->parent[rootB] = rootA;
			ds->rank[rootA]++;
		}
		return true;
	}
	return false;	
}

bool IsSameSet(DisjointSet *ds, int a, int b) {
	return find(ds, a) == find(ds, b);
}

void freeSet(DisjointSet *ds) {
	free(ds->parent);
	free(ds->rank);
	free(ds);
}

void displaySet(DisjointSet *ds) {
	int n = ds->n;
	
	printf("Elements: ");
	for(int i = 0; i < n; i++) printf("%d ", i);
	printf("\n");

	printf("Parents: ");
	for(int i = 0; i < n; i++) printf("%d ", ds->parent[i]);
	printf("\n");

	printf("Ranks: ");
	for(int i = 0; i < n; i++) printf("%d ", ds->rank[i]);
	printf("\n");
}

int main() {
	int n = 5;

	DisjointSet *ds = createSet(n);

	printf("Disjoint set created with %d elements (0, %d)\n", n, n - 1);
	displaySet(ds);

	printf("Performing union operations: \n");
	printf("union(0,1)\n");
	unionSets(ds, 0, 1);

	displaySet(ds);

	return 0;
}
