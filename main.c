#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "usuarios.h"
#include "vendas.h"
#include "lista.h"


int main() {
    // Inicializações
    CatalogoProdutos* catalogo = iniciarCatalogo();
    ListaAlunos alunos;
    ControleVendas vendas;
    FilaReposicao fila;

    iniciarListaAlunos(&alunos);
    iniciarControleVendas(&vendas);
    iniciarFila(&fila);

    // Produtos de exemplo cadastrados inicialmente
    //cadastrarProduto(catalogo, "HERSHEYS COM NOZES", CHOCOLATE, 001, 10);
    //cadastrarProduto(catalogo, "BIS CHOCOLATE BRANCO", CHOCOLATE, 002, 5);

    // Alunos de exemplo cadastrados inicialmente
    //cadastrarAluno(&alunos, "Joao Silva", 123456);
    //cadastrarAluno(&alunos, "Maria Oliveira", 654321);

    int opcao;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Visualizar Produtos\n");
        printf("3. Cadastrar Aluno\n");
        printf("4. Listar Alunos\n");
        printf("5. Registrar Venda\n");
        printf("6. Relatorio de Vendas por Aluno\n");
        printf("7. Mostrar Fila de Reposicao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        if (opcao == 1) {

            //////////////////////////////
            // INICIO CADASTRAR PRODUTO //
            //////////////////////////////

            char nome[100];
            int codigo, categoriaInt, estoque;
            Categoria cat;

            printf("\n=== REGISTRAR PRODUTO ===\n");

            printf("Nome do produto: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Categoria (0=FRUTA, 1=DOCE, 2=SALGADO, 3=CHOCOLATE): ");
            scanf("%d", &categoriaInt);

            switch (categoriaInt) {
                case 0: cat = FRUTA; break;
                case 1: cat = DOCE; break;
                case 2: cat = SALGADO; break;
                case 3: cat = CHOCOLATE; break;
                default: categoriaInt = -1; 
            }

            if (categoriaInt == -1) {
                printf("categoria invalida");
            } else {
                printf("Codigo: ");
                scanf("%d", &codigo);

                printf("Estoque inicial: ");
                scanf("%d", &estoque);

                if (cadastrarProduto(catalogo, nome, cat, codigo, estoque)) {
                    printf("Produto cadastrado com sucesso.");
                } else {
                    printf("Erro ao cadastrar o produto.");
                }
                printf("\n=========================\n");
            }
            ///////////////////////////
            // FIM CADASTRAR PRODUTO //
            ///////////////////////////

        } else if (opcao == 2) {
            // visualizar todos os produtos
            visualizarCatalogo(catalogo);

        } else if (opcao == 3) {
            /////////////////////
            // CADASTRAR ALUNO //
            /////////////////////
            char nome[100];
            int matricula;

            printf("\n==== CADASTRAR NOVO ALUNO ====\n");

            printf("Nome do aluno: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Matricula: ");
            scanf("%d", &matricula);

            if (cadastrarAluno(&alunos, nome, matricula)) {
                printf("\nAluno cadastrado com sucesso.");
            }

            printf("\n==============================\n");
            /////////////////////////
            // FIM CADASTRAR ALUNO //
            /////////////////////////
        } else if (opcao == 4) {
            // visualizar todos os alunos
            listarAlunos(&alunos);

        } else if (opcao == 5) {

            /////////////////////
            // REGISTRAR VENDA //
            /////////////////////

            printf("\n==== REGISTRAR VENDA ====\n");

            int matricula, codigo, quantidade;
            printf("Matricula do aluno: ");
            scanf("%d", &matricula);

            printf("Codigo do produto: ");
            scanf("%d", &codigo);

            printf("Quantidade: ");
            scanf("%d", &quantidade);

            if (registrarVenda(&vendas, &alunos, catalogo, &fila, matricula, codigo, quantidade)) {
                printf("Venda registrada com sucesso.");
            }

            printf("\n=========================\n");
            /////////////////////////
            // FIM REGISTRAR VENDA //
            /////////////////////////

        } else if (opcao == 6) {

            /////////////////////////
            // VER VENDAS P/ ALUNO //
            /////////////////////////

            printf("\n==== RELATORIO DE VENDAS DE ALUNO ====\n");

            int matricula;
            printf("Matricula do aluno: ");
            scanf("%d", &matricula);
            relatorioVendasAluno(&vendas, &alunos, matricula);

            printf("\n======================================\n");

            //////////////////////////////
            // FIM VER VENDAS POR ALUNO //
            //////////////////////////////

        } else if (opcao == 7) {
            // exibir fila de reposicao
            exibirFila(&fila);
        } else {
            printf("opcao invalida!\n");
        }

    } while (opcao != 0);

    printf("Programa encerrado.\n");
    return 0;
}
