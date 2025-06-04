#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "produto.h"


CatalogoProdutos* iniciarCatalogo() {
    CatalogoProdutos* novoCatalogo = (CatalogoProdutos*) malloc(sizeof(CatalogoProdutos));
    novoCatalogo->listaProdutos = (Produto*) malloc(sizeof(Produto) * CATALOGO_MAX);

    if (novoCatalogo == NULL) {
        return NULL;
    }

    novoCatalogo->tamanho = 0;
    novoCatalogo->tamanhoMaximo = CATALOGO_MAX;
    return novoCatalogo;
}


int catalogoCheio(CatalogoProdutos* catalogo) {
    return (catalogo->tamanho == catalogo->tamanhoMaximo);
}


int realocarCatalogo(CatalogoProdutos* catalogo) {
    int novoMaximo = catalogo->tamanhoMaximo * 2;

    Produto* listaAumentada = realloc(catalogo->listaProdutos, sizeof(Produto) * novoMaximo);
    if (listaAumentada == NULL) {
        return 0; // erro ao realocar
    }
    
    catalogo->listaProdutos = listaAumentada;
    catalogo->tamanhoMaximo = novoMaximo;
    return 1; // sucesso na realocacao
}


int cadastrarProduto(CatalogoProdutos* catalogo, char* nome, Categoria categoria, int codigo, int estoque) {

    printf("\n");

    // verifica se o catalogo eh valido
    if (catalogo == NULL) {
        printf("Catalogo invalido");
        return 0; // catalogo invalido, nao eh possivel cadastrar um novo produto
    }

    // verifica se o catalogo esta cheio
    if (catalogoCheio(catalogo)) {
        printf("Catalogo cheio, aumentando capacidade... ");
        if (realocarCatalogo(catalogo)) {
            printf("capacidade aumentada!\n"); // capacidade aumentada, prosseguir com o cadastro do produto
        } else {
            printf("erro ao aumentar a capacidade.\n");
            return 0; // catalogo cheio e nao foi possivel aumentar a capacidade
        }
    }

    // verifica se ja existe algum produto com esse codigo
    if (buscarProduto(catalogo, codigo) != NULL) {
        printf("Esse codigo ja foi cadastrado no catalogo!\n");
        return 0;
    }

    Produto novoProduto;
    strcpy(novoProduto.nome, nome);
    novoProduto.categoria = categoria;
    novoProduto.codigo = codigo;
    novoProduto.estoque = estoque;

    catalogo->listaProdutos[catalogo->tamanho] = novoProduto;
    catalogo->tamanho++;

    return 1;
}


Produto* buscarProduto(CatalogoProdutos* catalogo, int codigo) {
    if (catalogo == NULL || catalogo->tamanho == 0) {
        return NULL;
    }

    for (int i = 0; i < catalogo->tamanho; i++) {
        if (catalogo->listaProdutos[i].codigo == codigo) {
            return &(catalogo->listaProdutos[i]); // retorna o endereco do produto encontrado
        }
    }
    // se nao tiver encontrado nenhum produto...
    return NULL;
}


int removerProduto(CatalogoProdutos* catalogo, int codigo) {
    if (catalogo == NULL || catalogo->tamanho == 0) {
        printf("catalogo vazio ou nao existente...\n");
        return 0;
    }

    int indice = -1;

    for (int i = 0; i < catalogo->tamanho; i++) {
        if (catalogo->listaProdutos[i].codigo == codigo) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Produto nao encontrado!\n");
        return 0;
    }

    printf("produto removido: ");
    visualizarProduto(catalogo->listaProdutos[indice]);

    for (int i = indice; i < catalogo->tamanho - 1; i++) {
        catalogo->listaProdutos[i] = catalogo->listaProdutos[i+1];
    }

    catalogo->tamanho--;
    return 1;
}


void visualizarProduto(Produto produto) {
    printf("[%d] %s | %s | %d EM ESTOQUE\n", produto.codigo, produto.nome, nomeCategoria(produto.categoria), produto.estoque);
}


void visualizarCatalogo(CatalogoProdutos* catalogo) {

    printf("\n======== CATALOGO DE PRODUTOS ========\n");

    if (catalogo == NULL || catalogo->tamanho == 0) {
        printf("catalogo invalido ou vazio");
        printf("\n======================================\n");
        return;
    }
    for (int i = 0; i < catalogo->tamanho; i++) {
        visualizarProduto(catalogo->listaProdutos[i]);
    }

    printf("======================================\n");
}

const char* nomeCategoria(Categoria categoria) {
    switch (categoria) {
        case FRUTA: return "Fruta";
        case DOCE: return "Doce";
        case SALGADO: return "Salgado";
        case CHOCOLATE: return "Chocolate";
        default: return "Desconhecido";
    }
}