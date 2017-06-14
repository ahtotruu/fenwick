/* Brute-force test driver. */

#include <stdlib.h>
#include <assert.h>

#include "fenwick.h"

#define MAXN 100
#define MAXA 100

int *a; /* An array containing the Fenwick tree. */
int *b; /* A plain array for reference. */

/* Sum the first k elements of the plain array b. */
int array_sum(int k) {
	int s = 0;
	for (int i = 0; i < k; ++i) {
		s += b[i];
	}
	return s;
}

/* Check that the data extracted from the tree matches the plain array. */
void check(int n) {
	/* Check extracting individual elements. */
	for (int i = 0; i < n; ++i) {
		assert(fenwick_get(a, n, i) == b[i]);
	}
	/* Check extracting prefix sums. */
	for (int i = 0; i <= n; ++i) {
		assert(fenwick_sum(a, n, i) == array_sum(i));
	}
}

int main() {
	/* Test all array sizes 0..MAXN. */
	for (int n = 0; n <= MAXN; ++n) {
		/* Allocate exact amount of memory, to help detect out-of-bounds accesses. */
		a = (int *)calloc(n, sizeof(int));
		b = (int *)calloc(n, sizeof(int));
		/* Fill two arrays with the same random data. */
		for (int i = 0; i < n; ++i) {
			a[i] = b[i] = rand() % MAXA;
		}
		/* Turn one array into tree, check for consistency. */
		fenwick_init(a, n);
		check(n);
		/* Change each element by a random value, check for consistency. */
		for (int i = 0; i < n; ++i) {
			int d = rand() % MAXA;
			fenwick_inc(a, n, i, d);
			b[i] += d;
			check(n);
		}
		/* Set each element to a random value, check for consistency. */
		for (int i = 0; i < n; ++i) {
			int v = rand() % MAXA;
			fenwick_set(a, n, i, v);
			b[i] = v;
			check(n);
		}
		/* Turn the tree back into array, check for consistency. */
		fenwick_done(a, n);
		for (int i = 0; i < n; ++i) {
			assert(a[i] == b[i]);
		}
		/* Release allocated memory before next iteration. */
		free(a);
		free(b);
	}
	return 0;
}
