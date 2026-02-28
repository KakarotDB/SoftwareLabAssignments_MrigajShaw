#include "../DisjointSetUnion/DisjointSetUnion.h"
#include <stdio.h>

bool isFullyConnected(DisjointSet *ds) {
    int root = find(ds, 0);
    for (int i = 1; i < ds->n; i++) {
        if (find(ds, i) != root)
            return false;
    }
    return true;
}

int main() {
    int n, m;
    printf("Enter number of buildings and road operations: ");
    scanf("%d %d", &n, &m);

    DisjointSet *ds = createSet(n);
    printf("Created set with %d buildings (0 to %d)\n", n, n - 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        printf("Enter road operation (u v): ");
        scanf("%d %d", &u, &v);

        if (unionSets(ds, u, v))
            printf("Union(%d, %d): connected.\n", u, v);
        else
            printf("Union(%d, %d): already in same component.\n", u, v);

        if (isFullyConnected(ds)) {
            printf("City is now fully connected!\n");
            break;
        } else
            printf("City is not yet fully connected.\n");
    }

    freeSet(ds);
    return 0;
}
