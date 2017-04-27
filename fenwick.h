/* A Fenwick tree of integers. Interface. */

void fenwick_init(int a[], int n);
void fenwick_inc(int a[], int n, int i, int d);
void fenwick_set(int a[], int n, int i, int v);
int fenwick_get(int a[], int n, int i);
int fenwick_sum(int a[], int n, int k);
void fenwick_done(int a[], int n);
