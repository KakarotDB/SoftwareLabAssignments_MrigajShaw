#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x, y;
} Point;

int compare1D(const void *a, const void *b) {
    double difference = (*(double *)a - *(double *)b);
    return (difference > 0) - (difference < 0);
}

double closestPair1D(double *array, int n) {
    qsort(array, n, sizeof(double), compare1D);
    double minDistance = DBL_MAX;

    for (int i = 0; i < n - 1; i++) {
        if (array[i + 1] - array[i] < minDistance)
            minDistance = array[i + 1] - array[i];
    }
    return minDistance;
}

int compareX(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;

    return (p1->x > p2->x) - (p1->x < p2->x);
}

int compareY(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;

    return (p1->y > p2->y) - (p1->y < p2->y);
}

double distance2D(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double minDouble(double x, double y) { return (x < y) ? x : y; }

double closestUtil(Point *Px, Point *Py, int n) {
    if (n <= 3) {
        double minVal = DBL_MAX;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double distance = distance2D(Px[i], Py[i]);
                minVal = minDouble(distance, minVal);
            }
        }
        return minVal;
    }

    int mid = n / 2;
    Point midPoint = Px[mid];

    Point *PyL = (Point *)malloc(mid * sizeof(Point));
    Point *PyR = (Point *)malloc((n - mid) * sizeof(Point));

    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if ((Py[i].x < midPoint.x || (Py[i].x == midPoint.x && l < mid)) &&
            l < mid) {
            PyL[l++] = Py[i];
        } else
            PyR[r++] = Py[i];
    }

    double dl = closestUtil(Px, PyL, mid);
    double dr = closestUtil(Px + mid, PyR, n - mid);

    double d = minDouble(dl, dr);

    Point *strip = (Point *)malloc(n * sizeof(Point));

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(Py[i].x - midPoint.x) < d)
            strip[j++] = Py[i];
    }

    double minVal = d;

    for (int i = 0; i < j; i++) {
        for (int k = i + 1; k < j && (strip[k].y - strip[i].y) < minVal; k++) {
            double distance = distance2D(strip[i], strip[k]);
            minVal = minDouble(minVal, distance);
        }
    }

    free(PyL);
    free(PyR);
    free(strip);

    return minVal;
}

double closestPair2D(Point *P, int n) {
    Point *Px = (Point *)malloc(n * sizeof(Point));
    Point *Py = (Point *)malloc(n * sizeof(Point));

    for (int i = 0; i < n; i++) {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);

    double ans = closestUtil(Px, Py, n);

    free(Px);
    free(Py);

    return ans;
}

int main() {
    int choice, n;

    printf("Select Case:\n1. 1D Points\n2. 2D Points\nEnter choice: ");
    if (scanf("%d", &choice) != 1)
        return 1;

    printf("Enter the number of points: ");
    if (scanf("%d", &n) != 1 || n < 2) {
        printf("Need at least 2 points.\n");
        return 1;
    }

    if (choice == 1) {
        double *arr = (double *)malloc(n * sizeof(double));
        printf("Enter %d points (X coordinates):\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%lf", &arr[i]);
        }

        printf("The smallest distance is: %lf\n", closestPair1D(arr, n));
        free(arr);
    } else if (choice == 2) {
        Point *P = (Point *)malloc(n * sizeof(Point));
        printf("Enter %d points (X Y coordinates separated by space):\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &P[i].x, &P[i].y);
        }

        printf("The smallest distance is: %lf\n", closestPair2D(P, n));
        free(P);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
