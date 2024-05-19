#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int numero;
    struct Celula* prox;
} Celula;

typedef struct CelulaMat {
    int numero;
    struct CelulaMat* prox;
    struct CelulaMat* ant;
    struct CelulaMat* sup;
    struct CelulaMat* inf;
} CelulaMat;

typedef struct No {
    int numero;
    struct No* esq;
    struct No* dir;
} No;

Celula* novaCelula(int elemento) {
    Celula* c = (Celula*)malloc(sizeof(Celula));
    c->numero = elemento;
    c->prox = NULL;
    return c;
}

void adicionarElemento(Celula** lista, int elemento) {
    Celula* nova = novaCelula(elemento);
    nova->prox = *lista;
    *lista = nova;
}

int pesquisarArvore(No* raiz, int elemento) {
    if (raiz == NULL) {
        return 0;
    }
    if (raiz->numero == elemento) {
        return 1;
    }
    if (elemento < raiz->numero) {
        return pesquisarArvore(raiz->esq, elemento);
    } else {
        return pesquisarArvore(raiz->dir, elemento);
    }
}

void obterElementosComuns(CelulaMat* inicio, No* raiz, Celula** comuns) {
    CelulaMat* linha = inicio;
    while (linha != NULL) {
        CelulaMat* coluna = linha;
        while (coluna != NULL) {
            if (pesquisarArvore(raiz, coluna->numero)) {
                adicionarElemento(comuns, coluna->numero);
            }
            coluna = coluna->prox;
        }
        linha = linha->inf;
    }
}

Celula* encontrarRepetidos(No* raiz, CelulaMat* inicio) {
    Celula* comuns = NULL;

    // Obter elementos comuns pesquisando na árvore
    obterElementosComuns(inicio, raiz, &comuns);

    return comuns;
}

// Funções de criação e inserção na árvore e na matriz para teste

No* novoNo(int numero) {
    No* n = (No*)malloc(sizeof(No));
    n->numero = numero;
    n->esq = n->dir = NULL;
    return n;
}

No* inserirArvore(No* raiz, int numero) {
    if (raiz == NULL) {
        return novoNo(numero);
    }
    if (numero < raiz->numero) {
        raiz->esq = inserirArvore(raiz->esq, numero);
    } else if (numero > raiz->numero) {
        raiz->dir = inserirArvore(raiz->dir, numero);
    }
    return raiz;
}

CelulaMat* novaCelulaMat(int numero) {
    CelulaMat* c = (CelulaMat*)malloc(sizeof(CelulaMat));
    c->numero = numero;
    c->prox = c->ant = c->sup = c->inf = NULL;
    return c;
}

CelulaMat* inserirMatriz(CelulaMat* inicio, int linha, int coluna, int numero) {
    CelulaMat* nova = novaCelulaMat(numero);
    CelulaMat* atual = inicio;
    for (int i = 0; i < linha; i++) {
        if (atual->inf == NULL) {
            atual->inf = nova;
            nova->sup = atual;
        }
        atual = atual->inf;
    }
    for (int j = 0; j < coluna; j++) {
        if (atual->prox == NULL) {
            atual->prox = nova;
            nova->ant = atual;
        }
        atual = atual->prox;
    }
    return inicio;
}

int main() {
    // Criar árvore binária
    No* raiz = NULL;
    raiz = inserirArvore(raiz, 5);
    raiz = inserirArvore(raiz, 3);
    raiz = inserirArvore(raiz, 7);
    raiz = inserirArvore(raiz, 2);
    raiz = inserirArvore(raiz, 4);
    raiz = inserirArvore(raiz, 6);
    raiz = inserirArvore(raiz, 8);

    // Criar matriz flexível
    CelulaMat* inicio = novaCelulaMat(1);
    inserirMatriz(inicio, 0, 1, 3);
    inserirMatriz(inicio, 0, 2, 5);
    inserirMatriz(inicio, 1, 0, 2);
    inserirMatriz(inicio, 1, 1, 4);
    inserirMatriz(inicio, 1, 2, 7);

    // Encontrar elementos comuns
    Celula* comuns = encontrarRepetidos(raiz, inicio);

    // Imprimir elementos comuns
    Celula* atual = comuns;
    while (atual != NULL) {
        printf("%d ", atual->numero);
        atual = atual->prox;
    }

    return 0;
}
