#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ll long long
#define max(a, b) ((a) > (b) ? (a) : (b))

ll maxProfitRecursive(ll values[], ll weights[], int n, int W) {
    if (n == 0 || W == 0)
        return 0;

    if (weights[n - 1] > W) {
        return maxProfitRecursive(values, weights, n - 1, W);
    } else {
        ll take = values[n - 1] + maxProfitRecursive(values, weights, n - 1,
                                                     W - weights[n - 1]);
        ll leave = maxProfitRecursive(values, weights, n - 1, W);

        return max(take, leave);
    }
}

ll maxProfitDynamicProgramming(ll *values, ll *weights, int n, int W) {
    ll dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = 0;
        }
    }

    int Wj = 0;
    int Vi = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            Wj = weights[i - 1];
            Vi = values[i - 1];

            if (Wj > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], Vi + dp[i - 1][j - Wj]);
            }
        }
    }

    return dp[n][W];
}

int main() {
    ll n = 0;
    ll KnapSack_Capacity = 0;
    clock_t start, end;

    printf("Enter number of items: ");
    scanf("%lld", &n);

    printf("Enter capacity of knapsack: ");
    scanf("%lld", &KnapSack_Capacity);

    ll values[n], weights[n];

    printf("Enter %lld pairs (values, weights)\n", n);

    for (ll i = 0; i < n; i++) {
        scanf("%lld %lld", &values[i], &weights[i]);
    }

    printf("Bruteforce solution result : \n");
    ll result = 0;
    start = clock();
    result = maxProfitRecursive(values, weights, n, KnapSack_Capacity);
    end = clock();

    printf("Result = %lld\n", result);
    printf("Time taken = %.10f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("DP solution result : \n");
    result = 0;
    start = clock();
    result = maxProfitDynamicProgramming(values, weights, n, KnapSack_Capacity);
    end = clock();

    printf("Result = %lld\n", result);
    printf("Time taken = %.10f\n", (double)(end - start) / CLOCKS_PER_SEC);
}
