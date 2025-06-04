#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

typedef struct No {
    int codigoProduto;
    struct No* prox;
} No;

typedef struct {
    No* fim;
} FilaReposicao;

// Inicializa a fila circular
void iniciarFila(FilaReposicao* fila);

// Enfileira um produto para reposição
void enfileirar(FilaReposicao* fila, int codigoProduto);

// Desenfileira o próximo produto
int desenfileirar(FilaReposicao* fila);

// Mostra todos os itens na fila
void exibirFila(FilaReposicao* fila);

#endif
