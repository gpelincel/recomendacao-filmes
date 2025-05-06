# Sistema de Recomendação de Filmes

Projeto da disciplina de **Estrutura de Dados (AC2)** com o objetivo de comparar o desempenho de diferentes estruturas de dados para resolver o mesmo problema.

## 🎯 Objetivo

Desenvolver um sistema de recomendação de filmes capaz de armazenar, buscar e sugerir filmes com base em critérios como nota, ano e gênero. O sistema será implementado em linguagem **C**, utilizando **TADs** e estruturas de dados distintas para análise de desempenho.

## 🧠 Problema Abordado

Simular um ambiente de recomendação como os utilizados por serviços de streaming, permitindo ao usuário buscar por filmes similares ao seu histórico de preferências.

Exemplo de busca:
> “Filmes de ação com nota maior que 7 lançados após 2015.”

## 🏗️ Estruturas de Dados Comparadas

### 1. Lista Encadeada
- Armazena os filmes na ordem em que são inseridos.
- As buscas percorrem a lista linearmente.
- Simples, porém ineficiente com grandes volumes de dados.

### 2. Árvore Binária de Busca (ABB)
- Organiza os filmes por nota como chave primária.
- Quando notas são iguais, os filmes são armazenados em uma **lista ligada no mesmo nó**.
- Permite buscas por intervalo (nota >= X && nota <= Y) de forma mais eficiente.

## 🧪 Testes Realizados

Os testes foram realizados com bases de:
- 1.000 filmes
- 10.000 filmes
- 100.000 filmes

As operações medidas foram:
- Tempo de **inserção**
- Tempo de **busca com filtros**
- Tempo de **remoção** (opcional)

Os tempos foram medidos com a função `clock()` da biblioteca `<time.h>`.

## 📊 Metodologia de Análise

Os tempos coletados foram organizados em tabelas e transformados em gráficos comparativos, possibilitando uma análise clara do desempenho entre as duas abordagens.

Ferramentas sugeridas para análise: Google Sheets, Excel ou matplotlib (Python).

## 🧩 Organização dos Arquivos

/src
├── main.c
├── filme.c / filme.h // Definição da estrutura Filme
├── lista.c / lista.h // Implementação da lista encadeada
├── abb.c / abb.h // Implementação da árvore binária com listas por nota
├── utils.c / utils.h // Geração de dados e medição de tempo

## 💬 Observações

Usar as seguinte structs

```
typedef struct No {
    float nota;
    ListaFilmes* filmes; // Lista de filmes com essa nota
    struct No* esquerda;
    struct No* direita;
} No;

typedef struct {
    char titulo[100];
    char genero[30];
    int ano;
    float nota;
} Filme;
```