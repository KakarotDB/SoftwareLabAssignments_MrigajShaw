#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int n;
} DisjointSet;

DisjointSet *createSet(int n) {
    DisjointSet *disjoint = (DisjointSet *)malloc(sizeof(DisjointSet));
    disjoint->n = n;
    disjoint->parent = (int *)malloc(n * sizeof(int));
    disjoint->rank = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        disjoint->parent[i] = i;
        disjoint->rank[i] = 0;
    }
    return disjoint;
}

int find(DisjointSet *ds, int i) {
    if (ds->parent[i] != i) {
        ds->parent[i] = find(ds, ds->parent[i]);
    }
    return ds->parent[i];
}

bool unionSets(DisjointSet *ds, int a, int b) {
    int rootA = find(ds, a);
    int rootB = find(ds, b);

    if (rootA != rootB) {
        if (ds->rank[rootA] < ds->rank[rootB]) {
            ds->parent[rootA] = rootB;
        } else if (ds->rank[rootA] > ds->rank[rootB]) {
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
    for (int i = 0; i < n; i++)
        printf("%d ", i);
    printf("\n");

    printf("Parents:  ");
    for (int i = 0; i < n; i++)
        printf("%d ", ds->parent[i]);
    printf("\n");

    printf("Ranks:    ");
    for (int i = 0; i < n; i++)
        printf("%d ", ds->rank[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    DisjointSet *ds = createSet(n);
    printf("Disjoint Set created with %d elements (0 to %d)\n", n, n - 1);

    int choice, a, b;
    do {
        printf("\nDisjoint Set Menu\n");
        printf("1. Display Set\n");
        printf("2. Union\n");
        printf("3. Find (root of element)\n");
        printf("4. Check if Same Set\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            displaySet(ds);
            break;

        case 2:
            printf("Enter two elements to union: ");
            scanf("%d %d", &a, &b);
            if (a < 0 || a >= n || b < 0 || b >= n) {
                printf("Invalid elements. Must be between 0 and %d.\n", n - 1);
                break;
            }
            if (unionSets(ds, a, b))
                printf("Union successful: %d and %d are now in the same set.\n",
                       a, b);
            else
                printf("%d and %d are already in the same set.\n", a, b);
            break;

        case 3:
            printf("Enter element to find root of: ");
            scanf("%d", &a);
            if (a < 0 || a >= n) {
                printf("Invalid element. Must be between 0 and %d.\n", n - 1);
                break;
            }
            printf("Root of %d is: %d\n", a, find(ds, a));
            break;

        case 4:
            printf("Enter two elements to check: ");
            scanf("%d %d", &a, &b);
            if (a < 0 || a >= n || b < 0 || b >= n) {
                printf("Invalid elements. Must be between 0 and %d.\n", n - 1);
                break;
            }
            if (IsSameSet(ds, a, b))
                printf("%d and %d belong to the SAME set.\n", a, b);
            else
                printf("%d and %d belong to DIFFERENT sets.\n", a, b);
            break;

        case 5:
            printf("Freeing memory and exiting...\n");
            freeSet(ds);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
