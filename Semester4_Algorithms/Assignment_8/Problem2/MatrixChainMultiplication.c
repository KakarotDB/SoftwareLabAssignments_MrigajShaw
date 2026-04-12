#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ll long long

typedef struct {
    ll rows, columns;
} Matrix;

ll matrixChainRecursive(Matrix *matrices, ll i, ll j) {
    if (i == j)
        return 0;

    ll minCost = LONG_LONG_MAX;

    for (ll k = i; k < j; k++) {
        ll leftCost = matrixChainRecursive(matrices, i, k);
        ll rightCost = matrixChainRecursive(matrices, k + 1, j);

        ll mergeCost =
            (ll)(matrices[i].rows * matrices[k].columns * matrices[j].columns);

        ll totalCost = leftCost + rightCost + mergeCost;

        if (totalCost < minCost)
            minCost = totalCost;
    }

    return minCost;
}

ll matrixChainDynamicProgramming(Matrix *matrices, int n) {
    ll dp[n][n];

    // base case : dp[i][i] = 0
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;

    for (int chainLength = 2; chainLength <= n; chainLength++) {
        for (int i = 0; i < n - chainLength + 1; i++) {
            // j is ending index of current chain
            int j = i + chainLength - 1;

            dp[i][j] = LONG_LONG_MAX;

            // for all possible split points k in between i and < j
            for (int k = i; k < j; k++) {
                ll leftCost = dp[i][k];
                ll rightCost = dp[k + 1][j];
                ll mergeCost = (ll)(matrices[i].rows * matrices[k].columns *
                                    matrices[j].columns);

                ll cost = leftCost + rightCost + mergeCost;

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    ll n = 0;
    ll result = 0;
    Matrix *matrices = NULL;
    clock_t start, end;

    printf("Enter number of matrices : ");
    scanf("%lld", &n);

    matrices = (Matrix *)malloc(sizeof(Matrix) * n);

    printf("Enter the number of rows and columns for each matrix: \n");

    for (ll i = 0; i < n; i++) {
        scanf("%lld %lld", &matrices[i].rows, &matrices[i].columns);
        if (i != 0 && matrices[i].rows != matrices[i - 1].columns) {
            printf("Cannot multiply matrices due to incompatibility!");
            return -1;
        }
    }

    printf("Recursive bruteforce solution: ");

    start = clock();
    result = matrixChainRecursive(matrices, 0, n - 1);
    end = clock();

    printf("Result = %lld\n", result);
    printf("Time taken = %.10f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("DP solution: ");

    start = clock();
    result = matrixChainDynamicProgramming(matrices, n);
    end = clock();

    printf("Result = %lld\n", result);
    printf("Time taken = %.10f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
