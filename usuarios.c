#include <stdio.h>
#include <string.h>
#include "usuarios.h"

// Inicializa a lista de alunos
void iniciarListaAlunos(ListaAlunos* lista) {
    lista->quantidade = 0;
}

// Cadastra um novo aluno, se não houver outro com a mesma matrícula
int cadastrarAluno(ListaAlunos* lista, char* nome, int matricula) {
    if (lista->quantidade >= MAX_USUARIOS) return 0;

    if (buscarAluno(lista, matricula) != NULL) {
        printf("Matricula ja cadastrada.\n");
        return 0;
    }

    strcpy(lista->lista[lista->quantidade].nome, nome);
    lista->lista[lista->quantidade].matricula = matricula;
    lista->quantidade++;
    return 1;
}

// Busca um aluno por matrícula
Aluno* buscarAluno(ListaAlunos* lista, int matricula) {
    for (int i = 0; i < lista->quantidade; i++) {
        if (lista->lista[i].matricula == matricula) {
            return &lista->lista[i];
        }
    }
    return NULL;
}

// Mostra todos os alunos
void listarAlunos(ListaAlunos* lista) {
    for (int i = 0; i < lista->quantidade; i++) {
        printf("[%d] %s\n", lista->lista[i].matricula, lista->lista[i].nome);
    }
}
