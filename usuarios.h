#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_USUARIOS 200

typedef struct {
    char nome[100];
    int matricula;
} Aluno;

typedef struct {
    Aluno* alunos;
    int quantidade;
    int capacidade;
} ListaAlunos;

// Inicializa a lista de alunos
void iniciarListaAlunos(ListaAlunos* listaAlunos);

// Cadastra um novo aluno
int cadastrarAluno(ListaAlunos* listaAlunos, char* nome, int matricula);

// Busca um aluno pela matrícula
Aluno* buscarAluno(ListaAlunos* listaAlunos, int matricula);

// Mostra todos os alunos
void listarAlunos(ListaAlunos* listaAlunos);

void liberarListaAlunos(ListaAlunos* listaAlunos);

int realocarListaAlunos(ListaAlunos* listaAlunos);

#endif
