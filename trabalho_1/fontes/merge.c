#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void merge(int *v, int s, int m, int e) {
    int i, j, k;
    int n1 = m - s + 1;
    int n2 = e - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = v[s + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    i = 0;
    j = 0;
    k = s;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int *v, int s, int e) {
    if (s < e) {
        int m = s + (e - s) / 2;

        merge_sort(v, s, m);
        merge_sort(v, m + 1, e);

        merge(v, s, m, e);
    }
}

int main(int argc, char **argv) {
    struct timespec a, b;
    unsigned int t, n;
    int *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = rand();

    clock_gettime(CLOCK_MONOTONIC, &b);
    merge_sort(v, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}
