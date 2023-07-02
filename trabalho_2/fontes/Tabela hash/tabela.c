#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

typedef struct bloco {
    int valor;
    struct bloco* proximo;
} Bloco;

typedef struct table {
    unsigned int tam;
    unsigned int n;
    struct bloco** b;
} Table;

Bloco* novo(int valor) {
    Bloco* bloco = (Bloco*)malloc(sizeof(Bloco));
    bloco->valor = valor;
    bloco->proximo = NULL;
    return bloco;
}

unsigned int hash(int valor, int tam) {
    return (valor % tam);
}

void adicionar(Table* table, Bloco* bloco) {
    unsigned int posicao = hash(bloco->valor, table->tam);
    if (table->b[posicao] == NULL) {
        table->b[posicao] = bloco;
    } else {
        bloco->proximo = table->b[posicao];
        table->b[posicao] = bloco;
    }
    table->n++;
}

void tremoveTabela(Table* table) {
    int i;
    for (i = 0; i < table->tam; i++) {
        Bloco* bloco = table->b[i];
        while (bloco != NULL) {
            Bloco* auxiliar = bloco->proximo;
            free(bloco);
            bloco = auxiliar;
        }
        table->b[i] = NULL;
    }
    table->n = 0;
}

int buscar(Table* table, int valor) {
    unsigned int posicao = hash(valor, table->tam);
    Bloco* bloco = table->b[posicao];
    while (bloco != NULL) {
        if (bloco->valor == valor) {
            return 1;
        }
        bloco = bloco->proximo;
    }
    return 0;
}

void atualizar(Table* table) {
    unsigned int tam = table->tam;
    Table new;
    new.tam = (tam * 2);
    new.b = (Bloco**)calloc(new.tam, sizeof(Bloco*));

    int i;
    for (i = 0; i < tam; i++) {
        Bloco* bloco = table->b[i];
        while (bloco != NULL) {
            unsigned int posicao = hash(bloco->valor, new.tam);
            Bloco* novoBloco = novo(bloco->valor);
            if (new.b[posicao] == NULL) {
                new.b[posicao] = novoBloco;
            } else {
                novoBloco->proximo = new.b[posicao];
                new.b[posicao] = novoBloco;
            }
            bloco = bloco->proximo;
            new.n++;
        }
    }

    tremoveTabela(table);
    table->b = new.b;
    table->tam = new.tam;
    table->n = new.n;
}

double tvtosec(struct timeval t) {
    return (double)t.tv_sec * 1e9 + (double)t.tv_usec * 1e3;
}

int main(void) {
    srand(time(NULL));
    Table table;
    int valor, i, j, y, k, achou, aleatorio;
    struct timeval a, b;
    double tempo;

    table.b = (Bloco**)malloc(sizeof(Bloco*) * 1000);
    table.n = 0;
    table.tam = 1000;

    for (j = 100; j <= 1000; j += 10) {
        tempo = 0;

        for (k = 0; k < 500; k++) {
            for (i = 0; i < j; i++) {
                table.b[i] = NULL;
            }

            for (y = 0; y < j; y++) {
                aleatorio = rand() % (j + 1);
                adicionar(&table, novo(aleatorio));
            }

            gettimeofday(&b, NULL);
            achou = buscar(&table, rand() % (y + 1));
            gettimeofday(&a, NULL);

            tempo += tvtosec(a) - tvtosec(b);
            tremoveTabela(&table);
        }

        printf("%d %.20lf\n", j, tempo / 500 * 1e9);
    }

    return 0;
}

