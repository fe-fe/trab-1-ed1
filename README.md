# 🍽️ Sistema de Controle de Estoque para Cantina Escolar

**Trabalho Prático I – Estrutura de Dados Linear com Interface de Aplicação**  
📚 **Disciplina**: Estrutura de Dados  
👨‍🏫 **Professor(a)**: Dr. Helcio Soares Padilha Junior.

---

## 👥 Integrantes do Grupo

| Nome                                 | Matrícula    |
|--------------------------------------|--------------|
| Maria Fernanda Zandona Casagrande   | GRR20241727  |
| Pedro Eduardo Dall' Agnol           | GRR20240844  |
| Gabriela Harres Rodrigues           | GRR20246215  |
| João Vítor Kretzschmar              | GRR20240632  |

---

## 📌 Objetivo

Desenvolver um sistema em linguagem C para controle de produtos, alunos e vendas em uma cantina escolar, utilizando diferentes **estruturas de listas lineares**. O projeto inclui funcionalidades como cadastro de produtos e alunos, controle de estoque, registro de vendas com limite diário por aluno e gerenciamento de fila de reposição de produtos esgotados.

---

## 🗃️ Estrutura de Arquivos

```
📁 Projeto
├── main.c                   # Menu principal e integração dos módulos
├── produto.c / produto.h   # Gerenciamento do catálogo de produtos
├── usuarios.c / usuarios.h # Cadastro e listagem de alunos
├── vendas.c / vendas.h     # Registro de vendas e controle de limite diário
├── lista.c / lista.h       # Fila circular de reposição de produtos
├── README.md               # Este documento
```

---

## 🧪 Como Compilar e Executar

### ✅ Compilação

```bash
gcc main.c produto.c usuarios.c vendas.c lista.c -o cantina
```

### ▶️ Execução

```bash
./cantina
```

Em sistemas Windows:

```bash
cantina.exe
```

---

## 🧭 Funcionalidades Implementadas

- ✅ Cadastro de produtos com nome, categoria, código e estoque.
- ✅ Cadastro de alunos com nome e matrícula.
- ✅ Registro de vendas com verificação de limite diário (máx. 5 itens).
- ✅ Atualização automática de estoque.
- ✅ Inserção de produtos esgotados na fila de reposição.
- ✅ Relatórios de vendas por aluno.
- ✅ Exibição da fila circular de reposição.

---

## 📚 Conceitos Aplicados

### Estruturas de Dados Utilizadas:

#### 🟩 Catálogo de Produtos
- **Tipo**: Lista Linear Dinâmica (vetor com realloc)
- **Justificativa**: Permite crescimento sob demanda. Ideal para acesso sequencial e listagem completa.
```
[ Produto 1 ] -> [ Produto 2 ] -> ... -> [ Produto N ]
```

#### 🟨 Lista de Alunos
- **Tipo**: Lista Linear Estática
- **Justificativa**: Simples de implementar, ideal para protótipos. Pode ser substituída por vetor dinâmico em versões futuras.
```
[ Aluno 1 ] -> [ Aluno 2 ] -> ... -> [ Aluno N ]
```

#### 🟦 Lista de Reposição de Produtos
- **Tipo**: Lista Circular Encadeada
- **Justificativa**: Estrutura ideal para Reposição. Permite inserções e remoções eficientes no ciclo de reposição e facilita o gerenciamento. Requisitada pelo Professor.
```
    +--------+       +--------+
    |ProdutoA| ----> |ProdutoB| --+
    +--------+       +--------+  |
        ^                        |
        +------------------------+
```

#### 🟧 Histórico de Vendas
- **Tipo**: Lista Linear Estática
- **Justificativa**: Estrutura simples para registros cronológicos. Não requer remoção ou ordenação. Ideal para simulações.

---

## 📋 Ilustração Geral do Sistema

```
+--------------------------+
|       Aluno (static)     |
| Nome | Matrícula         |
+--------------------------+
            |
            v
+--------------------------+
|     Venda (static)       |
| Mat. | Cod.Produto | Qtd |
+--------------------------+
            |
            v
+--------------------------+      +------------------+
|    Produto (dinâmico)    | ---> |  Estoque Atual   |
| Nome | Código | Categoria|      +------------------+
+--------------------------+
            |
            v
+--------------------------+
|   Fila Circular (repos)  |
+--------------------------+
```

---

## 🧠 Decisões de Projeto

- ✔️ **Vetor dinâmico** para produtos: flexível e eficiente para listagens e buscas.
- ✔️ **Lista circular encadeada** para fila de reposição: operações rápidas de inserção e remoção, sem necessidade de reorganizar memória.
- ✔️ **Limite de 5 itens por aluno/dia**: ajuda no controle de consumo e simula regra prática.
- ✔️ **Controle de Reposição automatica** insere produtos com menos de 10 unidades disponiveis na lista de reposição automaticamente.
- ✔️ Uso de modularização com `.c` e `.h` para clareza e reusabilidade do código.

---

## 💬 Comentários e Experiência do Grupo

> O desenvolvimento do projeto proporcionou uma vivência prática com os principais tipos de listas lineares e seus usos em sistemas reais. Enfrentamos desafios na modularização e gerenciamento de memória dinâmica, especialmente ao lidar com ponteiros e filas circulares.

> Entendemos que listas estáticas são úteis para prototipagem, mas optamos por usar estruturas dinâmicas nos casos em que flexibilidade era crucial (como no catálogo de produtos).

> A simulação de um sistema real, com múltiplos arquivos e integração entre módulos, nos ajudou a consolidar a importância da organização do código, da separação de responsabilidades e da documentação clara.

---

## 💡 Conclusão

Este projeto reforçou o aprendizado dos seguintes pontos:

- Implementação e aplicação de **listas lineares** (estáticas e dinâmicas).
- Uso de **listas circulares encadeadas** em contextos de fila.
- Modularização e clareza de código.
- Integração de múltiplas estruturas de dados para resolver um problema prático realista.

> ✅ A cantina agora tem um sistema de controle funcional, didático e com base sólida em Estrutura de Dados!

---

📌 **Obrigado pela atenção!**


UFPR - SEPT - TADS - V;
