#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdbool.h>
#include <stdlib.h>

// structure to hold graph edges for the priority queue
typedef struct {
    int u;      // source vertex
    int v;      // destination vertex
    int weight; // edge cost
} Edge;

typedef struct {
    Edge *array;
    int capacity;
    int size;
} MinHeap;

MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (Edge *)malloc(capacity * sizeof(Edge));
    return minHeap;
}

void swapEdge(Edge *a, Edge *b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left].weight < minHeap->array[smallest].weight)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right].weight < minHeap->array[smallest].weight)
        smallest = right;

    if (smallest != idx) {
        swapEdge(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

bool isEmpty(MinHeap *minHeap) { return minHeap->size == 0; }

Edge extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap)) {
        Edge emptyEdge = {-1, -1, -1};
        return emptyEdge;
    }

    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    Edge root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void insertMinHeap(MinHeap *minHeap, int u, int v, int weight) {
    if (minHeap->size == minHeap->capacity)
        return; // heap full

    minHeap->size++;
    int i = minHeap->size - 1;

    // insert at the bottom and bubble up
    minHeap->array[i].u = u;
    minHeap->array[i].v = v;
    minHeap->array[i].weight = weight;

    while (i != 0 &&
           minHeap->array[(i - 1) / 2].weight > minHeap->array[i].weight) {
        swapEdge(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void freeMinHeap(MinHeap *minHeap) {
    free(minHeap->array);
    free(minHeap);
}

#endif
