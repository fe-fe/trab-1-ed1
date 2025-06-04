#include <stdio.h>
#include "vendas.h"

// Inicia o controle de vendas
void iniciarControleVendas(ControleVendas* controle) {
    controle->totalVendas = 0;
}

// Verifica quantos itens o aluno comprou hoje
int itensCompradosHoje(ControleVendas* controle, int matricula) {
    int total = 0;
    for (int i = 0; i < controle->totalVendas; i++) {
        if (controle->historico[i].matriculaAluno == matricula) {
            total += controle->historico[i].quantidade;
        }
    }
    return total;
}

// Registra uma venda, respeita o limite de 5 itens/dia
int registrarVenda(
    ControleVendas* controle, ListaAlunos* alunos, CatalogoProdutos* catalogo, 
    FilaReposicao* fila, int matricula, int codigoProduto, int quantidade
) {
    Aluno* aluno = buscarAluno(alunos, matricula);
    Produto* produto = buscarProduto(catalogo, codigoProduto);

    if (aluno == NULL || produto == NULL) {
        printf("Erro: Aluno ou produto inexistente.\n");
        return 0;
    }

    int jaComprados = itensCompradosHoje(controle, matricula);
    if (jaComprados + quantidade > 5) {
        printf("Aviso: Limite diario de 5 itens excedido!\n");
        return 0;
    }

    if (produto->estoque < quantidade) {
        printf("Aviso: Estoque insuficiente. Produto adicionado à fila de reposição.\n");
        enfileirar(fila, codigoProduto);
        return 0;
    }

    produto->estoque -= quantidade;

    if (produto->estoque == 0) {
        printf("Aviso: ultima unidade do estoque vendida.\nProduto adicionado à fila de reposição.\n");
        enfileirar(fila, codigoProduto);
    }

    Venda v = {matricula, codigoProduto, quantidade};
    controle->historico[controle->totalVendas++] = v;

    return 1;

}

// Mostra todas as vendas de um aluno
void relatorioVendasAluno(ControleVendas* controle, ListaAlunos* alunos, int matricula) {
    Aluno* aluno = buscarAluno(alunos, matricula);

    
    
    if (!aluno) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    printf("Relatorio de vendas do(a) aluno(a) %s:\n", aluno->nome);
    for (int i = 0; i < controle->totalVendas; i++) {
        if (controle->historico[i].matriculaAluno == matricula) {
            printf("Produto %d - %d unidades\n",
                   controle->historico[i].codigoProduto,
                   controle->historico[i].quantidade);
        }
    }

}
