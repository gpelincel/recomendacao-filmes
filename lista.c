#include <time.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista.h"
#include "filme.h"

/* Inicializa uma lista */
void cria(Lista *p_l)
{
    *p_l = NULL;
}

/* Verifica se a lista está vazia ou não */
int vazia(Lista *p_l)
{
    return (*p_l == NULL);
}

/* Insere um elemento no início da lista */
void insere_inicio(Lista *p_l, Filme filme)
{
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista));
    novo->filme = filme;
    novo->prox = *p_l;
    *p_l = novo;
}

/* Insere um elemento no final da lista */
void insere_fim(Lista *p_l, Filme filme)
{
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista));
    novo->filme = filme;
    novo->prox = NULL;

    if (vazia(p_l))
        *p_l = novo; // Se a lista estiver vazia, insere o nó
    else
    {
        No_lista *aux = *p_l;

        while (aux->prox != NULL) // Percorre a lista até o fim
            aux = aux->prox;

        aux->prox = novo; // Adiciona o nó no final da lista
    }
}


/* Remove todos os nós da lista e a deixa vazia */
void libera(Lista *p_l)
{
    No_lista *aux;

    while (*p_l != NULL)
    {
        aux = *p_l;
        *p_l = aux->prox;
        free(aux);
    }
}

/* Exibe o conteúdo da lista */
void exibe(Lista *p_l)
{
    No_lista *aux = *p_l;

    while (aux != NULL)
    {
        printf("%s (%d) - %s - %.1f\n", aux->filme.titulo, aux->filme.ano, aux->filme.genero, aux->filme.nota);
        aux = aux->prox;
    }
    printf("\n");
}

void medir_tempo_busca_lista(Lista *p_l, const char *genero, float nota_min, int ano_min) {
    clock_t inicio, fim;
    double tempo;
    int comparacoes = 0;
    int encontrados = 0;

    No_lista *aux = *p_l;

    inicio = clock();

    while (aux != NULL) {
        comparacoes++;  // Contamos cada comparação
        Filme f = aux->filme;
        if (strstr(f.genero, genero) && f.nota >= nota_min && f.ano >= ano_min) {
            printf("\nTitulo: %s\nGenero: %s\nDiretor: %s\nAno: %d\nNota: %.1f\n",
                   f.titulo, f.genero, f.nome_diretor, f.ano, f.nota);
            encontrados++;
        }
        aux = aux->prox;
    }

    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    if (encontrados == 0) {
        printf("Nenhum filme encontrado com os critérios fornecidos.\n");
    }

    // Memória estimada (aproximada): cada nó + struct Filme
    size_t tamanho_no = sizeof(No_lista);
    size_t tamanho_filme = sizeof(Filme);
    int total_nos = 0;
    aux = *p_l;
    while (aux != NULL) {
        total_nos++;
        aux = aux->prox;
    }
    size_t memoria_total = total_nos * (tamanho_no + tamanho_filme);

    printf("\n* Resumo da Busca Lista: *\n");
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Memoria estimada usada: %.2f KB\n", memoria_total / 1024.0);
}