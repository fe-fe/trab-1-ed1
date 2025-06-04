#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Inicia fila vazia
void iniciarFila(FilaReposicao* fila) {
    fila->fim = NULL;
}

// Enfileira novo produto
void enfileirar(FilaReposicao* fila, int codigoProduto) {
    No* novo = (No*) malloc(sizeof(No));
    novo->codigoProduto = codigoProduto;

    if (fila->fim == NULL) {
        novo->prox = novo;
        fila->fim = novo;
    } else {
        novo->prox = fila->fim->prox;
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

// Remove produto do início da fila
int desenfileirar(FilaReposicao* fila) {
    if (fila->fim == NULL) return -1;

    No* inicio = fila->fim->prox;
    int codigo = inicio->codigoProduto;

    if (inicio == fila->fim) {
        free(inicio);
        fila->fim = NULL;
    } else {
        fila->fim->prox = inicio->prox;
        free(inicio);
    }

    return codigo;
}

// Mostra todos os itens da fila
void exibirFila(FilaReposicao* fila) {
    if (fila->fim == NULL) {
        printf("Fila de reposicao vazia.\n");
        return;
    }

    No* atual = fila->fim->prox;
    do {
        printf("Produto cod: %d\n", atual->codigoProduto);
        atual = atual->prox;
    } while (atual != fila->fim->prox);
}
