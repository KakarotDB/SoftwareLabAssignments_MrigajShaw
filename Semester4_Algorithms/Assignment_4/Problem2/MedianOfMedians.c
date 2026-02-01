#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0; // global variable to keep track of comparisons

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findMedianSmall(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        comparisons++;
        arr[j + 1] = key;
    }
    return arr[n / 2];
}

int partition(int arr[], int l, int r, int x) {
    int i;
    if (arr[r] != x) {
        comparisons++;
        for (i = l; i < r; i++) {
            if (arr[i] == x)
                break;
        }
        swap(&arr[i], &arr[r]);
    } else
        comparisons++;

    i = l;
    for (int j = l; j <= r - 1; j++) {
        comparisons++;
        if (arr[j] <= x) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int randomPartition(int *a, int l, int r) {
    int n = r - l + 1;
    int pivotIndex = l + rand() % n;
    swap(&a[pivotIndex], &a[r]);
    return partition(a, l, r, a[r]);
}

int kthSmallest(int arr[], int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int n = r - l + 1;
        int i;
        int *median = (int *)malloc(((n + 4) / 5) * sizeof(int));

        for (i = 0; i < n / 5; i++)
            median[i] = findMedianSmall(arr + l + i * 5, 5);

        if (i * 5 < n) {
            median[i] = findMedianSmall(arr + l + i * 5, n % 5);
            i++;
        }

        int medOfMed =
            (i == 1) ? median[0] : kthSmallest(median, 0, i - 1, i / 2);

        free(median);

        int pos = partition(arr, l, r, medOfMed);

        if (pos - l == k - 1)
            return arr[pos];

        if (pos - l > k - 1)
            return kthSmallest(arr, l, pos - 1, k);

        return kthSmallest(arr, pos + 1, r, k - pos + l - 1);
    }
    return -1;
}

int quickSelect(int *arr, int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int pos = randomPartition(arr, l, r);

        if (pos - l == k - 1)
            return arr[pos];

        if (pos - l > k - 1)
            return quickSelect(arr, l, pos - 1, k);

        return quickSelect(arr, pos + 1, r, k - pos + l - 1);
    }
    return -1;
}

int main() {
    int n = 120000; // Census size
    printf("--- CENSUS DATA ANALYSIS SYSTEM ---\n");
    printf("Generating dataset for %d households...\n", n);

    int census_data[n];
    int census_data_copy[n];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int val = 10000 + rand() % 190001; // Random income in range [10k, 200k]
        census_data[i] = val;
        census_data_copy[i] = val;
    }

    int k = (n / 2) + 1; // kth rank = median element

    printf("----Median of Medians Statistics----\n");
    comparisons = 0;
    clock_t start = clock();
    int result_MoM = kthSmallest(census_data, 0, n - 1, k);
    clock_t end = clock();

    double time_MoM = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Median income = $%d | Execution time : %f | Comparisons = %lld\n",
           result_MoM, time_MoM, comparisons);

    printf("---Quick Select Statistics----\n");
    comparisons = 0;
    start = clock();
    int result_QS = quickSelect(census_data_copy, 0, n - 1, k);
    end = clock();

    double time_QS = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Median income = $%d | Execution time : %f | Comparisons = %lld\n",
           result_QS, time_QS, comparisons);

    printf("--------------------------------\n");

    printf("Time difference : %f\n", fabs(time_MoM - time_QS));

    return 0;
}
