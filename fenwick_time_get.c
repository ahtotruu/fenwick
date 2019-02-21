/* Simple timing test driver. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fenwick.h"

#define MAXN 100000000
#define MAXQ 100000000
#define MAXA 100

int a[MAXN]; /* An array containing the Fenwick tree. */
int b[MAXN]; /* A plain array for reference. */

int main() {
	/* Test different array sizes. */
	for (int n = 10; n <= MAXN; n *= 10) {
		/* Fill two arrays with the same random data. */
		for (int i = 0; i < n; ++i) {
			a[i] = b[i] = rand() % MAXA;
		}
		/* Turn one array into tree. */
		fenwick_init(a, n);
		/* Time pulling random elements from the tree. */
		srand(n);
		int sa = 0;
		int ta = clock();
		for (int q = 0; q < MAXQ; ++q) {
			sa += fenwick_get(a, n, rand() % n);
		}
		ta = clock() - ta;
		/* Time pulling random elements from the array. */
		srand(n);
		int sb = 0;
		int tb = clock();
		for (int q = 0; q < MAXQ; ++q) {
			sb += b[rand() % n];
		}
		tb = clock() - tb;
		/* Results. */
		printf("N = %d, check: %d, tree: %d, array: %d, ratio: %lf\n", n, sa == sb, ta, tb, (double) ta / (double) tb);
	}
	return 0;
}
