#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

typedef struct node {
    int v;
    struct node *l;
    struct node *r;
    int height;
} Node;

Node* newnode(int num) {
    Node* a = (Node*)malloc(sizeof(Node));
    a->v = num;
    a->l = NULL;
    a->r = NULL;
    a->height = 1;
    return a;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

int getBalance(Node* n) {
    if (n == NULL) {
        return 0;
    }
    return height(n->l) - height(n->r);
}

Node* rotateRight(Node* y) {
    Node* x = y->l;
    Node* T2 = x->r;

    x->r = y;
    y->l = T2;

    y->height = max(height(y->l), height(y->r)) + 1;
    x->height = max(height(x->l), height(x->r)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->r;
    Node* T2 = y->l;

    y->l = x;
    x->r = T2;

    x->height = max(height(x->l), height(x->r)) + 1;
    y->height = max(height(y->l), height(y->r)) + 1;

    return y;
}

Node* insert(Node* n, int v) {
    if (n == NULL) {
        return newnode(v);
    }

    if (v < n->v) {
        n->l = insert(n->l, v);
    } else if (v > n->v) {
        n->r = insert(n->r, v);
    } else {
        return n; 
    }

    n->height = 1 + max(height(n->l), height(n->r));

    int balance = getBalance(n);

    if (balance > 1 && v < n->l->v) {
        return rotateRight(n);
    }

    if (balance < -1 && v > n->r->v) {
        return rotateLeft(n);
    }

    if (balance > 1 && v > n->l->v) {
        n->l = rotateLeft(n->l);
        return rotateRight(n);
    }

    if (balance < -1 && v < n->r->v) {
        n->r = rotateRight(n->r);
        return rotateLeft(n);
    }

    return n;
}

int search(Node* x, int v) {
    if (x == NULL) {
        return 0;
    }

    if (x->v == v) {
        return 1;
    }

    if (v < x->v) {
        return search(x->l, v);
    }

    return search(x->r, v);
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
    Node* node = NULL;
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
                node = insert(node, aleatorio);
            }

            /* BUSCA O ELEMENTO DE PIOR CASO */
            int element_not_present = n + 1; /* Pior caso: elemento não presente na árvore */
            gettimeofday(&b, NULL);
            int achou = search(node, element_not_present);
            gettimeofday(&a, NULL);

            tempo += tvtosec(a) - tvtosec(b);

            /* LIBERA A ÁRVORE */
            tremove(node);
            node = NULL;
        }

        /* PRINTA O RESULTADO */
        printf("%d %.20lf\n", n, tempo / 10000 * 1e9);
    }

    return 0;
}

