#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_USUARIOS 100

typedef struct {
    char nome[100];
    int matricula;
} Aluno;

typedef struct {
    Aluno lista[MAX_USUARIOS];
    int quantidade;
} ListaAlunos;

// Inicializa a lista de alunos
void iniciarListaAlunos(ListaAlunos* lista);

// Cadastra um novo aluno
int cadastrarAluno(ListaAlunos* lista, char* nome, int matricula);

// Busca um aluno pela matrícula
Aluno* buscarAluno(ListaAlunos* lista, int matricula);

// Mostra todos os alunos
void listarAlunos(ListaAlunos* lista);

#endif
