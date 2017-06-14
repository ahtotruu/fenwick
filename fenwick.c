/* A Fenwick tree of integers. Implementation. */

#include "fenwick.h"

/* Turn the n-element array a into a Fenwick tree. */
void fenwick_init(int a[], int n) {
	for (int i = 0; i < n; ++i) {
		for (int m = 1; (i & m) == m; m <<= 1) {
			a[i] += a[i - m];
		}
	}
}

/* Increment the i-th element in the n-element Fenwick tree by d. */
void fenwick_inc(int a[], int n, int i, int d) {
	a[i] += d;
	for (int m = 1; i + m < n; m <<= 1) {
		if ((i & m) == 0) {
			i += m;
			a[i] += d;
		}
	}
}

/* Set the i-th element of the n-element Fenwick tree to v. */
void fenwick_set(int a[], int n, int i, int v) {
	fenwick_inc(a, n, i, v - fenwick_get(a, n, i));
}

/* Get the i-th element of the n-element Fenwick tree. */
int fenwick_get(int a[], int n, int i) {
	int v = a[i];
	for (int m = 1; (i & m) == m; m <<= 1) {
		v -= a[i - m];
	}
	return v;
}

/* Sum the first k elements of the n-element Fenwick tree. */
int fenwick_sum(int a[], int n, int k) {
	int s = 0;
	for (int m = 1; m <= k; m <<= 1) {
		if ((k & m) == 0) {
			k += m;
		} else {
			s += a[k - m];
		}
	}
	return s;
}

/* Revert the n-element Fenwick tree back into an array. */
void fenwick_done(int a[], int n) {
	for (int i = n - 1; i >= 0; --i) {
		for (int m = 1; (i & m) == m; m <<= 1) {
			a[i] -= a[i - m];
		}
	}
}
