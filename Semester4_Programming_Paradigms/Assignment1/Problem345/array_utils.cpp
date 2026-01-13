#include "array_utils.h"
#include <iostream>
using namespace std;

int largestAmongNIntegers(int *a, int n, int index, int max) {
    if (index == n)
        return max;
    else if (a[index] >= max)
        return largestAmongNIntegers(a, n, index + 1, a[index]);
    else
        return largestAmongNIntegers(a, n, index + 1, max);
}

int searchList(int *a, int n, int index, int target) {
    if (index == n)
        return 0;
    if (a[index] == target)
        return 1;
    return searchList(a, n, index + 1, target);
}

void printReverse(int *a, int n) {
    if (n == 0)
        return;
    cout << a[n - 1] << " ";
    printReverse(a, n - 1);
}

int sumArray(int *a, int n, int sum) {
    if (n == 0)
        return sum;
    return sumArray(a, n - 1, sum + a[n - 1]);
}
