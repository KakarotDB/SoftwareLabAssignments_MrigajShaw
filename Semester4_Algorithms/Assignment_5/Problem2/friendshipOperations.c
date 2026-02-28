#include "../DisjointSetUnion/DisjointSetUnion.h"
#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    printf("Enter number of students and operations: ");
    scanf("%d %d", &n, &m);

    DisjointSet *ds = createSet(n);
    printf("Created set with %d students (0 to %d)\n", n, n - 1);

    for (int i = 0; i < m; i++) {
        char operation[10];
        int a, b;
        scanf("%s", operation);

        if (strcmp(operation, "Union") == 0) {
            scanf("%d %d", &a, &b);
            if (unionSets(ds, a, b))
                printf("Union(%d, %d): merged.\n", a, b);
            else
                printf("Union(%d, %d): already in same group.\n", a, b);
        } else if (strcmp(operation, "Find") == 0) {
            scanf("%d", &a);
            printf("Find(%d): leader is %d\n", a, find(ds, a));
        } else if (strcmp(operation, "Same") == 0) {
            scanf("%d %d", &a, &b);
            if (isSameSet(ds, a, b))
                printf("Same(%d, %d): YES\n", a, b);
            else
                printf("Same(%d, %d): NO\n", a, b);
        } else {
            printf("Unknown operation.\n");
        }
    }

    freeSet(ds);
    return 0;
}
