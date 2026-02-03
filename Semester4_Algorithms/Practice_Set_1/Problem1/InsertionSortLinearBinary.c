#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#define ll long long 

ll shifts = 0;
ll comparisons = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionsortlinear(int *a, int n) {
    if (a == NULL)
        return;
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
			comparisons++;
            a[j + 1] = a[j];
			shifts++;
            j--;
        }
		comparisons++;
        a[j + 1] = key;
    }
}

int binarysearch(int *a, int target, int left, int right) {
	while(left <= right) {
		comparisons++;
		int mid = left + right >> 1;
		if(target == a[mid]) return mid;
		if(target > a[mid]) left = mid + 1;
		else right = mid - 1;
	}
}

void insertionsortbinary(int *a, int n) {
    if (a == NULL)
        return;
    int i, key, j, location;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
		location = binarysearch(a, key, 0, j);

		while(j >= location) {
			a[j + 1] = a[j];
			shifts++;
			j--;
		}
		comparisons++;
		a[location] = key;
    }
}

void printarray(int *a, int n) {
	for(int i = 0; i < n; i++) printf("%d ", a[i]);
	printf("\n");
}

int main() {
	srand(time(NULL));
	clock_t start, end;
	int n = 12;
	int sizes[12] = {
		100, 1000, 10000
	};
	for(int i = 3; i < n; i++) {
		int base = 10000;
		sizes[i] = (i - 1) * base;
	}

	for(int i = 0; i < n; i++) {
		int currentsize = sizes[i];
		int *a = (int *) malloc(currentsize * sizeof(int));

		if(!a) {
			printf("memory allocation failed\n");
			return -1;
		}

		int *temp = (int *) malloc(currentsize * sizeof(int));
		if(!temp) {
			printf("memory allocation failed\n");
			return -1;
		}
		printf("generating array of size %d\n", currentsize);

		for(int i = 0; i < currentsize; i++) {
			int val = rand() % 1000;
			a[i] = val; 
			temp[i] = val;
		}

		printf("======== array of size %d metrics ========\n", currentsize);
		printf("--------insertion sort with linear search--------\n");

		comparisons = 0;
		shifts = 0;
		start = clock();
		insertionsortlinear(a, currentsize);		
		end = clock();
		
		printf("comparisons = %lld | shifts = %lld | execution time = %f\n", comparisons, shifts, (double) (end - start) / CLOCKS_PER_SEC ); 

		printf("-------------------------------------------------------\n");
		printf("--------insertion sort with binary search--------\n");

		comparisons = 0;
		shifts = 0;
		start = clock();
		insertionsortbinary(a, currentsize);		
		end = clock();
		
		printf("comparisons = %lld | shifts = %lld | execution time = %f\n", comparisons, shifts, (double) (end - start) / CLOCKS_PER_SEC ); 

		printf("=====================================================\n");
	}

	return 0;
}
