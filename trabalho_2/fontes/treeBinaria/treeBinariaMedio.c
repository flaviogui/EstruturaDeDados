#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

typedef struct node {
    int v;
    struct node *l;
    struct node *r;
} Node;

Node* newnode(int num) {
    Node* a = (Node*)malloc(sizeof(Node));
    a->v = num;
    a->l = NULL;
    a->r = NULL;
    return a;
}

void adicionar(Node **n, int v) {
    Node *aux = *n;
    Node *f = NULL;

    while (aux != NULL) {
        f = aux;
        if (aux->v < v) {
            aux = aux->r;
        } else {
            aux = aux->l;
        }
    }

    if (f == NULL) {
        *n = newnode(v);
    } else {
        if (f->v < v) {
            f->r = newnode(v);
        } else {
            f->l = newnode(v);
        }
    }
}

int tsearch(Node* x, int v) {
    if (x == NULL) {
        return 0;
    }

    if (x->v == v) {
        return 1;
    }

    if (x->v < v) {
        return tsearch(x->r, v);
    }

    return tsearch(x->l, v);
}

double tvtosec(struct timeval t) {
    return (double)t.tv_sec * 1e9 + (double)t.tv_usec * 1e3;
}

void tremove(Node* x) {
    if (x != NULL) {
        tremove(x->l);
        tremove(x->r);
        free(x);
    }
}

int main(void) {
    Node *node = NULL;
    srand(time(NULL));
    struct timeval a, b;
    double tempo;
    int n, k, i, aleatorio;

    /* CONTROLA O TAMANHO */
    for (n = 1000; n <= 10000; n += 500) {
        tempo = 0;

        /* CALCULA A MEDIA */
        for (i = 0; i < 10000; i++) {
            /* PREENCHE A ÁRVORE */
            for (k = 0; k < n; k++) {
                aleatorio = rand() % (n + 1);
                adicionar(&node, aleatorio);
            }

            /* BUSCA O ELEMENTO DE CASO MÉDIO */
            aleatorio = rand() % (n + 1);
            gettimeofday(&b, NULL);
            int achou = tsearch(node, aleatorio); /* caso médio */
            gettimeofday(&a, NULL);

            tempo += tvtosec(a) - tvtosec(b);

            /* LIBERA A ARVORE */
            tremove(node);
            node = NULL;
        }

        /* PRINTA O RESULTADO */
        printf("%d %.20lf\n", n, tempo / 10000 * 1e9);
    }

    return 0;
}

