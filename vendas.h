#ifndef VENDAS_H
#define VENDAS_H

#include "produto.h"
#include "usuarios.h"
#include "lista.h"

#define MAX_VENDAS 500

typedef struct {
    int matriculaAluno;
    int codigoProduto;
    int quantidade;
} Venda;

typedef struct {
    Venda historico[MAX_VENDAS];
    int totalVendas;
} ControleVendas;

// Inicializa o controle de vendas
void iniciarControleVendas(ControleVendas* controle);

// Verifica quantos itens o aluno já comprou no dia
int itensCompradosHoje(ControleVendas* controle, int matricula);

// Registra uma venda, atualiza estoque e insere na fila se necessário
int registrarVenda(
    ControleVendas* controle, ListaAlunos* alunos, CatalogoProdutos* catalogo, 
    ListaReposicao* fila, int matricula, int codigoProduto, int quantidade
);

// Mostra vendas por aluno
void relatorioVendasAluno(ControleVendas* controle, ListaAlunos* alunos, int matricula);

#endif
