#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

void iniciarListaReposicao(ListaReposicao* lista) {
    lista->fim = NULL;
}


int estaNaListaReposicao(ListaReposicao* lista, int codigo) {

    if (lista->fim == NULL) {
        return 0; // se a lista esta vazia
    }

    NoRep* atual = lista->fim->prox; // declara o primeiro no
    do { // enquanto nao der um loop completo
        if (atual->codigo == codigo) { // verifica se o codigo do produto eh o solicitado
            return 1; // return 1 (sim, esta na lista)
        }
        atual = atual->prox; // se nao for, passa pro proximo no
    } while (atual != lista->fim->prox); // condicao do loop
    return 0; // loop completo, poduto nao encontrado
}


void inserirProdutoReposicao(ListaReposicao* lista, int codigo, const char* nome) {
    
    if (estaNaListaReposicao(lista, codigo)) { // se o produto ja esta na lista, nao precisa adicionar de novo
        return;
    }
    
    NoRep* novo = (NoRep*) malloc(sizeof(NoRep));
    novo->codigo = codigo; // insere os atributos do produto no no
    novo->nome = strdup(nome); 

    if (lista->fim == NULL) { // se a lista estiver vazia
        novo->prox = novo; // insere o novo no como primeiro e ultimo elemento
        lista->fim = novo;
    } else { // se nao estiver vazia
        novo->prox = lista->fim->prox; // atualiza o proximo do novo no para o primeiro elemento
        lista->fim->prox = novo; // atualiza o ponteiro do antigo ultimo no para o novo no
        lista->fim = novo; // atualiza o ponteiro que controla o ultimo no
    }
}


int removerProdutoReposicao(ListaReposicao* lista, int codigo) {
    if (lista->fim == NULL) return 0; // verifica se a lista nao esta vazia

    NoRep* atual = lista->fim->prox;
    NoRep* anterior = lista->fim;

    do {
        if (atual->codigo == codigo) {
            if (atual == anterior) {  // Só um elemento
                lista->fim = NULL;
            } else {
                anterior->prox = atual->prox;
                if (atual == lista->fim) {
                    lista->fim = anterior;  // Atualiza fim
                }
            }
            free(atual->nome);
            free(atual);
            return 1;  // Sucesso
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != lista->fim->prox);

    return 0;  // Código não encontrado
}


void exibirListaReposicao(ListaReposicao* lista) {
    printf("\n=== LISTA DE REPOSICAO ===\n");

    if (lista->fim == NULL) {
        printf("Nenhum produto na lista de reposicao.\n");
        return;
    }

    NoRep* atual = lista->fim->prox;
    do {
        printf("Código: %d | Nome: %s\n", atual->codigo, atual->nome);
        atual = atual->prox;
    } while (atual != lista->fim->prox);

    printf("===========================\n");
}


void liberarLista(ListaReposicao* lista) {

    // libera a lista de reposiscao, no por no
    if (lista->fim == NULL) return;

    NoRep* atual = lista->fim->prox;
    NoRep* proxNo;

    do {
        proxNo = atual->prox;
        free(atual->nome);
        free(atual);
        atual = proxNo;
    } while (atual != lista->fim->prox);

    lista->fim = NULL;
}
