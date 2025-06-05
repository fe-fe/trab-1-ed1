#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "produto.h"
#include "lista.h"

CatalogoProdutos* iniciarCatalogo() {
    // aloca na memoria um novo catalogo de produtos
    CatalogoProdutos* novoCatalogo = (CatalogoProdutos*) malloc(sizeof(CatalogoProdutos));
    novoCatalogo->listaProdutos = (Produto*) malloc(sizeof(Produto) * CATALOGO_MAX); // aloca na memoria a nova lista de produtos

    if (novoCatalogo == NULL) { // verifica se a alocacao foi bem sucedida
        return NULL; // retorna null se nao for
    }

    // inicia os atributos e retorna o catalogo criado
    novoCatalogo->tamanho = 0; 
    novoCatalogo->tamanhoMaximo = CATALOGO_MAX;
    return novoCatalogo;
}


int catalogoCheio(CatalogoProdutos* catalogo) {
    // verifica se o catalogo esta cheio
    return (catalogo->tamanho == catalogo->tamanhoMaximo);
}


int realocarCatalogo(CatalogoProdutos* catalogo) {
    // aumenta o tamanho do catalogo para o dobro do tamanho autal
    int novoMaximo = catalogo->tamanhoMaximo * 2;

    // realoca a lista de produtos com o novo tamanho
    Produto* listaAumentada = realloc(catalogo->listaProdutos, sizeof(Produto) * novoMaximo);
    if (listaAumentada == NULL) { // verifica se a realocacao foi bem sucedida
        return 0; // erro ao realocar
    }
    // corrige os novos tamanhos nos atributos do catalogo
    catalogo->listaProdutos = listaAumentada;
    catalogo->tamanhoMaximo = novoMaximo;
    return 1; // sucesso na realocacao
}


int cadastrarProduto(CatalogoProdutos* catalogo, ListaReposicao* listaRep, char* nome, Categoria categoria, int codigo, int estoque) {

    printf("\n");

    // verifica se o catalogo eh valido
    if (catalogo == NULL) {
        printf("Catalogo invalido");
        return 0; // catalogo invalido, nao eh possivel cadastrar um novo produto
    }

    // verifica se o catalogo esta cheio
    if (catalogoCheio(catalogo)) {
        printf("Catalogo cheio, aumentando capacidade... "); // auumenta a capacidade caso o catalogo esteja cheio
        if (realocarCatalogo(catalogo)) { // verifica se a funcao de aumentar a capacidade foi bem sucedida
            printf("capacidade aumentada!\n"); // capacidade aumentada, prosseguir com o cadastro do produto
        } else {
            printf("erro ao aumentar a capacidade.\n");
            return 0; // catalogo cheio e nao foi possivel aumentar a capacidade
        }
    }

    // verifica se ja existe algum produto com esse codigo
    if (buscarProduto(catalogo, codigo) != NULL) {
        printf("Esse codigo ja foi cadastrado no catalogo!\n"); // ja existe
        return 0; // nao registra novo produto, pois ja existe esse codigo no catalogo
    }

    if (estoque < 10) {
        printf("Aviso: Produto com estoque baixo\n");
        printf("Aviso: Produto adicionado a lista de reposicao\n");
        inserirProdutoReposicao(listaRep, codigo, nome);
    }
    
    // inicia um novo produto
    // e preenche seus atributos
    Produto novoProduto;
    strcpy(novoProduto.nome, nome);
    novoProduto.categoria = categoria;
    novoProduto.codigo = codigo;
    novoProduto.estoque = estoque;

    // adiciona o novo produto ao catalogo
    catalogo->listaProdutos[catalogo->tamanho] = novoProduto;
    catalogo->tamanho++; // aumenta o contador de produtos

    return 1;
}


Produto* buscarProduto(CatalogoProdutos* catalogo, int codigo) {
    if (catalogo == NULL || catalogo->tamanho == 0) { // verifica se o catalogo eh valido e nao esta vazio
        return NULL; // se estiver vazio ou invalido, nao tem como buscar nenhum produto
    }

    for (int i = 0; i < catalogo->tamanho; i++) { // para cada produto
        if (catalogo->listaProdutos[i].codigo == codigo) { // verifica se o produto possui o codigo recebio
            return &(catalogo->listaProdutos[i]); // retorna o endereco do produto encontrado
        }
    }
    // se nao tiver encontrado nenhum produto...
    return NULL;
}


int removerProduto(CatalogoProdutos* catalogo, int codigo) {
    if (catalogo == NULL || catalogo->tamanho == 0) { // verifica se o catalogo eh valido e nao esta vazio
        printf("catalogo vazio ou nao existente...\n"); // se estiver vazio ou invalido, nao tem como remover nenhum produto
        return 0;
    } // verifica se o catalogo esta vazio

    int indice = -1; // inicia a variavel de indice como -1 (ou seja, um "nenhum")
    
    for (int i = 0; i < catalogo->tamanho; i++) { // para cada produto
        if (catalogo->listaProdutos[i].codigo == codigo) { // se o produto possui o codigo recebido
            indice = i; // anota o indice
            break; // para o loop: produto encontrado
        }
    }

    if (indice == -1) { // verifica se o produto foi encontrado ou nao
        printf("Produto nao encontrado!\n"); 
        return 0; // retorna 0: nenhum produto removido
    }

    printf("produto removido: "); // printa o produto que sera removido
    visualizarProduto(catalogo->listaProdutos[indice]);

    for (int i = indice; i < catalogo->tamanho - 1; i++) { // reorganiza a lista
        catalogo->listaProdutos[i] = catalogo->listaProdutos[i+1];
    }

    catalogo->tamanho--; // diminui o contador de produtos
    return 1; // retorna 1: produto removido
}


void visualizarProduto(Produto produto) {
    printf("[%d] %s | %s | %d EM ESTOQUE\n", produto.codigo, produto.nome, nomeCategoria(produto.categoria), produto.estoque);
}


void visualizarCatalogo(CatalogoProdutos* catalogo) {
    // printa cada produto do catalogo
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

const char* nomeCategoria(Categoria categoria) { // funcao que retorna o nome da categoria (enum) em string
    switch (categoria) {
        case FRUTA: return "Fruta";
        case DOCE: return "Doce";
        case SALGADO: return "Salgado";
        case CHOCOLATE: return "Chocolate";
        default: return "Desconhecido";
    }
}

int reporEstoque(CatalogoProdutos* catalogo, ListaReposicao* listaRep, int codigoProduto, int quantidade) {

    Produto* produto = buscarProduto(catalogo, codigoProduto); // busca um produto pelo codigo recebido
    if (produto == NULL) { // se nao encontrar nenhum produto
        printf("produto invalido"); // 
        return 0; // avisa o erro e retorna 0; estoque do produto nao reposto
    }
    // produto foi encontrado
    printf("Estoque do produto reposto:\n");
    produto->estoque += quantidade; // repor estoque
    if (produto->estoque - quantidade < 10 && produto->estoque >= 10) { // se ele estava na lista de reposicao, mas o estoque passou a ser 10 ou maior, tira da reposicao
        removerProdutoReposicao(listaRep, codigoProduto);
    }
    visualizarProduto(*produto); // printar produto
    return 1;
}
