#ifndef PRODUTO_H
#define PRODUTO_H

#define CATALOGO_MAX 100

typedef enum  {
    FRUTA,
    DOCE,
    SALGADO,
    CHOCOLATE
} Categoria;

typedef struct  {
    char nome[100];
    Categoria categoria;
    int codigo;
    int estoque;
} Produto;

typedef struct  {
    Produto* listaProdutos;
    int tamanho;
    int tamanhoMaximo;
} CatalogoProdutos;

// inicia um catalogo de produtos vazio
// retorno: o catalogo de produtos vazio, ou NULL caso haja erro na realocacao
CatalogoProdutos* iniciarCatalogo();

// verifica se o catalogo esta cheio
// retorno: 1 para cheio, 0 para nao cheio
int catalogoCheio(CatalogoProdutos* catalogo);

// aumenta o tamanho total do catalogo para suportar mais produtos
// retorno: 1 para realocacao bem sucedida, 0 para erro na realocacao
int realocarCatalogo(CatalogoProdutos* catalogo);

// cadastra um novo produto no catalogo
// retorno: 1 para cadastro bem sucedido, 0 para erro no cadastro
int cadastrarProduto(CatalogoProdutos* catalogo, char* nome, Categoria categoria, int codigo, int estoque);

// remove um produto do catalogo
// retorno: 1 para remocao bem sucedida, 0 para erro na remocao
int removerProduto(CatalogoProdutos* catalogo, int codigo);

// busca um produto no catalogo pelo seu codigo
// retorno: objeto Produto caso encontrado, NULL caso nao encontrado
Produto* buscarProduto(CatalogoProdutos* catalogo, int codigo);

// imprime na tela um produto do catalogo pelo seu codigo
void visualizarProduto(Produto produto);

// imprime na tela todos os produtos do catalogo
void visualizarCatalogo(CatalogoProdutos* catalogo);

const char* nomeCategoria(Categoria categoria);

#endif