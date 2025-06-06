#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "usuarios.h"

// João Vítor Kretzschmar

// Inicializa a lista de alunos
void iniciarListaAlunos(ListaAlunos* listaAlunos) {
    listaAlunos->quantidade = 0;
    listaAlunos->capacidade = MAX_USUARIOS; // capacidade inicial
    listaAlunos->alunos = malloc(listaAlunos->capacidade * sizeof(Aluno));
    if (!listaAlunos->alunos) {
        printf("Erro ao alocar memoria para a lista de alunos.\n");
        exit(1);
    }
}

int realocarListaAlunos(ListaAlunos* listaAlunos) {
    listaAlunos->capacidade *= 2; // dobra a capacidade
    Aluno* listaMaior = realloc(listaAlunos->alunos, listaAlunos->capacidade * sizeof(Aluno));
    if (!listaMaior) {
        printf("Erro ao realocar memoria para a lista de alunos.\n");
        listaAlunos->capacidade = listaAlunos->capacidade / 2;
        return 0;
    }
    listaAlunos->alunos = listaMaior;
    return 1;
}



// Cadastra um novo aluno, se não houver outro com a mesma matrícula
int cadastrarAluno(ListaAlunos* listaAlunos, char* nome, int matricula) {
    if (listaAlunos->quantidade >= listaAlunos->capacidade) {
        if (!realocarListaAlunos(listaAlunos)) {
            printf("Nao foi possivel cadastrar o aluno.");
            return 0;
        }
    }

    if (buscarAluno(listaAlunos, matricula) != NULL) {
        printf("Matricula ja cadastrada.");
        return 0;
    }
    Aluno novoAluno;
    strcpy(novoAluno.nome, nome);
    novoAluno.matricula = matricula;
    listaAlunos->alunos[listaAlunos->quantidade] = novoAluno;
    listaAlunos->quantidade++;
    return 1;
}

// Busca um aluno por matrícula
Aluno* buscarAluno(ListaAlunos* listaAlunos, int matricula) {
    for (int i = 0; i < listaAlunos->quantidade; i++) {
        if (listaAlunos->alunos[i].matricula == matricula) {
            return &listaAlunos->alunos[i];
        }
    }
    return NULL;
}

// Mostra todos os alunos
void listarAlunos(ListaAlunos* listaAlunos) {
    //                                    .
    printf("\n======= LISTA DE ALUNOS =======\n");

    if (listaAlunos->quantidade == 0 || listaAlunos == NULL) {
        printf("Lista de alunos invalida ou vazia\n");
    }

    for (int i = 0; i < listaAlunos->quantidade; i++) {
        printf("[%d] %s\n", listaAlunos->alunos[i].matricula, listaAlunos->alunos[i].nome);
    }

    printf("================================\n");
}


void liberarListaAlunos(ListaAlunos* listaAlunos) {
    free(listaAlunos->alunos);
    listaAlunos->alunos = NULL;
    listaAlunos->quantidade = 0;
    listaAlunos->capacidade = 0;
}
