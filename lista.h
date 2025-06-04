#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

// Estrutura do nó
typedef struct NoRep {
    int codigo;
    char* nome;
    struct NoRep* prox;
} NoRep;

typedef struct ListaReposicao {
    NoRep* fim;
} ListaReposicao;

// Inicializa a fila circular
void iniciarListaReposicao(ListaReposicao* fila);

// Enfileira um produto para reposição
void inserirProdutoReposicao(ListaReposicao* lista, int codigo, const char* nome);

// Desenfileira o próximo produto
int removerProdutoReposicao(ListaReposicao* lista, int codigo);

// Mostra todos os itens na fila
void exibirListaReposicao(ListaReposicao* lista);

void liberarLista(ListaReposicao* lista);

#endif
