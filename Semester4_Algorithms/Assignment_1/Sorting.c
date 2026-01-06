#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(int a[], int n) {
    if (a == NULL) {
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

void InsertionSort(int *a, int n) {
    if (a == NULL) {
        return;
    }
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int partition(int *a, int low, int high) {
    int mid = (high + low) >> 1;
    if (a[low] > a[mid]) {
        swap(&a[low], &a[mid]);
    }
    if (a[low] > a[high]) {
        swap(&a[low], &a[high]);
    }
    if (a[mid] > a[high]) {
        swap(&a[mid], &a[high]);
    }
    // now we have sorted the three elements at these positions, so our median
    // would be a[mid] we put a[mid] at high for the algorithm and choosing this
    // as pivot
    swap(&a[mid], &a[high]);

    int i = low - 1;
    int pivot = a[high];

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            swap(&a[++i], &a[j]);
        }
    }
    swap(&a[++i], &a[high]);

    return i;
}

void quickSort(int *a, int low, int high) {
    if (low < high) {
        int partition_index = partition(a, low, high);
        quickSort(a, low, partition_index - 1);
        quickSort(a, partition_index + 1, high);
    }
}

void merge(int *leftArray, int leftSize, int *rightArray, int rightSize,
           int *array) {
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize) {
        if (leftArray[l] < rightArray[r]) {
            array[i] = leftArray[l];
            i++;
            l++;
        } else {
            array[i] = rightArray[r];
            i++;
            r++;
        }
    }

    while (l < leftSize) {
        array[i] = leftArray[l];
        i++;
        l++;
    }

    while (r < rightSize) {
        array[i] = rightArray[r];
        i++;
        r++;
    }
}

void mergeSort(int *array, int n) {
    if (n <= 1)
        return;

    int mid = n / 2;
    int leftSize = mid;
    int rightSize = n - mid;

    int *leftArray = (int *)malloc(leftSize * sizeof(int));
    int *rightArray = (int *)malloc(rightSize * sizeof(int));

    memcpy(leftArray, array, leftSize * sizeof(int));
    memcpy(rightArray, &array[mid], rightSize * sizeof(int));

    mergeSort(leftArray, leftSize);
    mergeSort(rightArray, rightSize);

    merge(leftArray, leftSize, rightArray, rightSize, array);

    free(leftArray);
    free(rightArray);
}

void sort(int *a, int n) {
    clock_t start, end;
    start = clock();
    BubbleSort(a, n);
    end = clock();
    double bubble_Sort = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for BubbleSort : %f\n", bubble_Sort);

    start = clock();
    InsertionSort(a, n);
    end = clock();
    double insertion_Sort = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for InsertionSort: %f\n", insertion_Sort);

    start = clock();
    quickSort(a, 0, n - 1);
    end = clock();
    double quick_Sort = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for quickSort: %f\n", quick_Sort);

    start = clock();
    mergeSort(a, n);
    end = clock();
    double merge_Sort = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for merge Sort: %f\n", merge_Sort);
}

void ShowStats(int *a, int n, int serial) {
    printf("\nFor array %d of size %d:\n", serial, n);
    printf("------------Statitstics-----------\n");
    sort(a, n);
    printf("----------------------------------\n");
}

int main() {
    int n1 = 5000;
    int n2 = 10000;
    int n3 = 15000;
    int n4 = 20000;
    int n5 = 25000;
    int n6 = 30000;
    int n7 = 35000;
    int n8 = 40000;
    int n9 = 45000;
    int n10 = 50000;

    int a1[n1], a2[n2], a3[n3], a4[n4], a5[n5], a6[n6], a7[n7], a8[n8], a9[n9],
        a10[n10];

    srand(time(NULL));

    for (int i = 0; i < n1; i++)
        a1[i] = rand();
    for (int i = 0; i < n2; i++)
        a2[i] = rand();
    for (int i = 0; i < n3; i++)
        a3[i] = rand();
    for (int i = 0; i < n4; i++)
        a4[i] = rand();
    for (int i = 0; i < n5; i++)
        a5[i] = rand();
    for (int i = 0; i < n6; i++)
        a6[i] = rand();
    for (int i = 0; i < n7; i++)
        a7[i] = rand();
    for (int i = 0; i < n8; i++)
        a8[i] = rand();
    for (int i = 0; i < n9; i++)
        a9[i] = rand();
    for (int i = 0; i < n10; i++)
        a10[i] = rand();

    ShowStats(a1, n1, 1);
    ShowStats(a2, n2, 2);
    ShowStats(a3, n3, 3);
    ShowStats(a4, n4, 4);
    ShowStats(a5, n5, 5);
    ShowStats(a6, n6, 6);
    ShowStats(a7, n7, 7);
    ShowStats(a8, n8, 8);
    ShowStats(a9, n9, 9);
    ShowStats(a10, n10, 10);
}
