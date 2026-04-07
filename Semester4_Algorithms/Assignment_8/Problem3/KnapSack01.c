#include <stdio.h>
#define ll long long 

ll maxProfitRecursive(ll values[], ll weights[], int n, int W) {
	if(n == 0 || W == 0) return 0;

	if(weight[n - 1] > W) {
		return maxProfitRecursive(values, weights, n - 1, W);
	}
	else {
		return max(values[n - 1] + maxProfitRecursive(values, weights, n - 1, W - weights[n - 1]), maxProfitRecursive(values, weights, n - 1, W);
	}
}

ll maxProfitDynamicProgramming(ll *values, ll *weights, int n, int W) {
	ll dp[n + 1][W + 1];

	int n_values, n_weights, KnapSack_Weight;
	printf("Enter number of values and weights: ");
	scanf("%d %d", &n, &n_weights);

	ll values[n_values], weights[n_weights];

	printf("Enter %d values: \n", n)h
	for(int i = 0; i < n_values; i++) {
		int vi = 0;
		scanf("%d", &vi);
		values[i] = vi;
	}

	for(int i = 0; i <= W; i++) {
		dp[0][i] = 0;
	}
	for(int i = 0; i <= n; i++) {
		dp[i][0] = 0;
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j<= W; j++) {
			ll vi = values[i];
			ll wi = weights[i];
		}
	}
}
