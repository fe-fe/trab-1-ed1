#include <stdio.h>
#include <stdlib.h>

#include "vendas.h"
#include "lista.h"

// Pedro Eduardo Dall Agnol

// Inicia o controle de vendas
void iniciarControleVendas(ControleVendas* controle) {
    controle->totalVendas = 0;
    controle->capacidade = MAX_VENDAS; // capacidade inicial
    controle->historico = malloc(controle->capacidade * sizeof(Venda));
    if (!controle->historico) {
        printf("Erro ao alocar memoria para o historico de vendas.\n");
        exit(1);
    }
}

int realocarHistoricoVendas(ControleVendas* controle) {
    controle->capacidade *= 2; // dobra a capacidade
    Venda* novo = realloc(controle->historico, controle->capacidade * sizeof(Venda));
    if (!novo) {
        printf("Erro ao realocar memoria para o historico de vendas.\n");
        controle->capacidade = controle->capacidade / 2;
        return 0;
    }
    controle->historico = novo;
    return 1;
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
    ListaReposicao* listaRep, int matricula, int codigoProduto, int quantidade
) {

    if (controle->totalVendas >= controle->capacidade) {
        if (!realocarHistoricoVendas(controle)) {
            printf("Nao foi possivel realocar o controle de vendas.\n");
            return 0;
        }
        
    }

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
        printf("Aviso: Estoque insuficiente.\n");
        if (!estaNaListaReposicao(listaRep, codigoProduto)) {
            printf("Produto Adicionado a Lista de Reposicao.\n");
            inserirProdutoReposicao(listaRep, codigoProduto, produto->nome);
        }
    }

    produto->estoque -= quantidade;

    if (produto->estoque < 10) {
        printf("Aviso: Estoque baixo.\n");
        if (!estaNaListaReposicao(listaRep, codigoProduto)) {
            printf("Produto Adicionado a Lista de Reposicao.\n");
            inserirProdutoReposicao(listaRep, codigoProduto, produto->nome);
        }
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

void liberarControleVendas(ControleVendas* controle) {
    free(controle->historico);
    controle->historico = NULL;
    controle->totalVendas = 0;
    controle->capacidade = 0;
}
