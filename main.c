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
    cadastrarProduto(catalogo, "HERSHEYS COM NOZES", CHOCOLATE, 001, 10);
    cadastrarProduto(catalogo, "BIS CHOCOLATE BRANCO", CHOCOLATE, 002, 5);

    // Alunos de exemplo cadastrados inicialmente
    cadastrarAluno(&alunos, "Joao Silva", 123456);
    cadastrarAluno(&alunos, "Maria Oliveira", 654321);

    int opcao;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
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
            char nome[100];
            int codigo, categoriaInt, estoque;

            printf("Nome do produto: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Categoria (0=FRUTA, 1=DOCE, 2=SALGADO, 3=CHOCOLATE): ");
            scanf("%d", &categoriaInt);

            printf("Codigo: ");
            scanf("%d", &codigo);

            printf("Estoque inicial: ");
            scanf("%d", &estoque);

            if (cadastrarProduto(catalogo, nome, (Categoria)categoriaInt, codigo, estoque)) {
                printf("Produto cadastrado com sucesso.\n");
            }

        } else if (opcao == 2) {
            visualizarCatalogo(catalogo);

        } else if (opcao == 3) {
            char nome[100];
            int matricula;

            printf("Nome do aluno: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Matricula: ");
            scanf("%d", &matricula);

            if (cadastrarAluno(&alunos, nome, matricula)) {
                printf("Aluno cadastrado com sucesso.\n");
            }

        } else if (opcao == 4) {
            listarAlunos(&alunos);

        } else if (opcao == 5) {
            int matricula, codigo, quantidade;
            printf("Matricula do aluno: ");
            scanf("%d", &matricula);

            printf("Codigo do produto: ");
            scanf("%d", &codigo);

            printf("Quantidade: ");
            scanf("%d", &quantidade);

            if (registrarVenda(&vendas, &alunos, catalogo, &fila, matricula, codigo, quantidade)) {
                printf("Venda registrada com sucesso.\n");
            }

        } else if (opcao == 6) {
            int matricula;
            printf("Matricula do aluno: ");
            scanf("%d", &matricula);
            relatorioVendasAluno(&vendas, &alunos, matricula);

        } else if (opcao == 7) {
            exibirFila(&fila);
        }

    } while (opcao != 0);

    printf("Programa encerrado.\n");
    return 0;
}
