#include <stdio.h>
#include <time.h>
#define ll long long
#define MAX (int)1e6

ll memo[MAX];

ll fibonacciRecursion(ll n) {
	if(n <= 0) return 0;
	if(n == 1) return 1;
	return fibonacciRecursion(n - 1) + fibonacciRecursion(n - 2);	
}

ll fibonacciMemoization(int n) {
	if(n <= 1) return n;

	if(memo[n] != -1) return memo[n];

	memo[n] = fibonacciMemoization(n - 1) + fibonacciMemoization(n - 2);

	return memo[n];
}

ll fibonacciTabulation(int n) {
	ll dp[n + 1];
	ll f0 = 0;
	ll f1 = 1;	
	ll f2 = 0;

	if(n == 0) return f0;
	if(n == 1) return f1;
	for(int i = 2; i <=n; i++) {
		f2 = f0 + f1;
		f0 = f1;
		f1 = f2;
	}

	return f2; 
}

ll main() {
	//initializing global array to all -1 
	for(int i = 0; i < MAX; i++) {
		memo[i] = -1;
	}
	ll n = 0;
	clock_t start, end;

	printf("Enter value of n: ");
	scanf("%lld", &n);
	
	start = clock();
	ll result = fibonacciRecursion(n);	
	end = clock();
	printf("%lld\n", result);
	printf("%.10f\n", (double) (end - start)/CLOCKS_PER_SEC);

	start = clock();
	result = fibonacciMemoization(n);
	end = clock();
	printf("%lld\n", result);
	printf("%.10f\n", (double) (end - start)/CLOCKS_PER_SEC);

	start = clock();
	result = fibonacciTabulation(n);
	end = clock();
	printf("%lld\n", result);
	printf("%.10f\n", (double) (end - start)/CLOCKS_PER_SEC);
	return 0;
}
