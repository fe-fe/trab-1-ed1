#include "produto.h"
#include <stdio.h>

void main() {

    int idSerial = 1;
    
    CatalogoProdutos* catalogo = iniciarCatalogo();
    cadastrarProduto(catalogo, "HERSHEYS COM NOZES", CHOCOLATE, idSerial, 10);

    idSerial++;

    cadastrarProduto(catalogo, "BIS CHOCOLATE BRANCO", CHOCOLATE, idSerial, 5);

    idSerial++;

    visualizarCatalogo(catalogo);

    removerProduto(catalogo, 2);

    cadastrarProduto(catalogo, "HERSHEYS COOKIES 'N' CREME", CHOCOLATE, idSerial, 200000);

    idSerial++;

    cadastrarProduto(catalogo, "HERSHEYS CHOCOLATE BRANCO", CHOCOLATE, idSerial, 200000);

    idSerial++;

    visualizarCatalogo(catalogo);

    getchar();
}