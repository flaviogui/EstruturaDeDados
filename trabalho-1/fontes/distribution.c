#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void distribution_sort(int *v, int n) {
    int s = v[0];
    int b = v[0];

    for (int i = 1; i < n; i++) {
        if (v[i] < s)
            s = v[i];
        if (v[i] > b)
            b = v[i];
    }

    int size = b - s + 1;
    int *c = (int *) calloc(size, sizeof(int));

    for (int i = 0; i < n; i++) {
        c[v[i] - s]++;
    }

    for (int i = 1; i < size; i++) {
        c[i] += c[i - 1];
    }

    int *w = (int *) malloc(n * sizeof(int));

    for (int i = n - 1; i >= 0; i--) {
        int d = v[i] - s;
        w[c[d] - 1] = v[i];
        c[d]--;
    }

    for (int i = 0; i < n; i++) {
        v[i] = w[i];
    }

    free(c);
    free(w);
}

int main(int argc, char **argv) {
    struct timespec a, b;
    unsigned int t, n;
    int *v;

    if (argc < 2) {
        printf("Digite o tamanho do vetor como argumento!\n");
        return 1;
    }

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = rand() % 100;  

    clock_gettime(CLOCK_MONOTONIC, &b);
    distribution_sort(v, n);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}
