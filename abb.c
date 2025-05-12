#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cria um novo nó da árvore com a nota do filme como chave e inicia a lista de filmes
No_arvore* criar_no(Filme filme) {
    No_arvore* novo = (No_arvore*) malloc(sizeof(No_arvore)); // Aloca memória para o novo nó
    novo->nota = filme.nota; // Define a nota como chave do nó
    novo->filmes = NULL; // Inicializa a lista de filmes com essa nota
    insere_inicio(&novo->filmes, filme); // Insere o primeiro filme na lista
    novo->esquerda = novo->direita = NULL; // Inicializa filhos como NULL
    return novo;
}

// Insere um filme na árvore binária de busca (ABB), agrupando por nota
No_arvore* inserir_abb(No_arvore* raiz, Filme filme) {
    if (raiz == NULL) {
        return criar_no(filme); // Cria o primeiro nó (caso base)
    }

    if (filme.nota < raiz->nota) {
        // Insere à esquerda se a nota for menor
        raiz->esquerda = inserir_abb(raiz->esquerda, filme);
    } else if (filme.nota > raiz->nota) {
        // Insere à direita se a nota for maior
        raiz->direita = inserir_abb(raiz->direita, filme);
    } else {
        // Mesma nota: insere o filme na lista ligada do nó atual
        insere_inicio(&raiz->filmes, filme);
    }

    return raiz;
}

// Libera toda a árvore recursivamente (pós-ordem)
void liberar_abb(No_arvore* raiz) {
    if (!raiz) return;

    liberar_abb(raiz->esquerda); // Libera subárvore esquerda
    liberar_abb(raiz->direita);  // Libera subárvore direita
    libera(&raiz->filmes);       // Libera a lista de filmes do nó atual
    free(raiz);                  // Libera o próprio nó
}

// Mede o tempo de execução e memória usada na busca por filtros na ABB
void medir_tempo_busca_abb(No_arvore* raiz, const char* genero, float nota_min, int ano_min) {
    int comparacoes = 0;

    clock_t inicio = clock(); // Marca o início do tempo
    buscar_filmes_abb(raiz, genero, nota_min, ano_min, &comparacoes); // Executa a busca
    clock_t fim = clock(); // Marca o fim do tempo

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // Calcula tempo em segundos

    printf("\n* Resumo da Busca ABB: *\n");
    printf("\nTempo de execucao: %.6f segundos", tempo);
    printf("\nComparacoes realizadas: %d", comparacoes);
}

// Percorre a ABB in-order (ordem crescente de nota) e exibe os filmes
void exibir_arvore_in_ordem(No_arvore* raiz) {
    if (raiz) {
        exibir_arvore_in_ordem(raiz->esquerda); // Visita a subárvore esquerda

        // Exibe todos os filmes da lista ligada do nó atual
        No_lista* aux = raiz->filmes;
        while (aux) {
            Filme f = aux->filme;
            printf("\nTitulo: %s\nGenero: %s\nAno: %d\nNota: %.1f\n",
                   f.titulo, f.genero, f.ano, f.nota);
            aux = aux->prox;
        }

        exibir_arvore_in_ordem(raiz->direita); // Visita a subárvore direita
    }
}