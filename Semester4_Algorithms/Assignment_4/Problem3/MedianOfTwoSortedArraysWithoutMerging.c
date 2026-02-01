#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

double findMedianSortedArays(int *a1, int n1, int *a2, int n2) {
    if (n1 > n2) {
        return findMedianSortedArays(
            a2, n2, a1, n1); // ensuring lesser of the two arrays is always used
    }

    int x = n1;
    int y = n2;
    int low = 0, high = x;

    while (low <= high) {
        int partitionX = (low + high) >> 1;
        int partitionY = (x + y + 1) / 2 - partitionX;

        int maxLeftX = (partitionX == 0) ? INT_MIN : a1[partitionX - 1];
        int minRightX = (partitionX == x) ? INT_MAX : a1[partitionX];

        int maxLeftY = (partitionY == 0) ? INT_MIN : a2[partitionY - 1];
        int minRightY = (partitionY == y) ? INT_MAX : a2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((x + y) % 2 == 0) {
                return (double)(max(maxLeftX, maxLeftY) +
                                min(minRightX, minRightY)) /
                       2;
            } else {
                return (double)max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    return 0.0;
}

int main() {
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n1 = 8;
    int B[] = {1, 2, 3, 4, 5};
    int n2 = 5;

    printf("Bank A transactions:\n");
    for (int i = 0; i < n1; i++)
        printf("%d ", A[i]);
    printf("\n");

    printf("Bank B transactions:\n");
    for (int i = 0; i < n2; i++)
        printf("%d ", B[i]);
    printf("\n");

    double median = findMedianSortedArays(A, n1, B, n2);

    printf("Combined median transaction value = %.2f\n", median);

    return 0;
}
