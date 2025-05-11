#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

No_arvore* criar_no(Filme filme) {
    No_arvore* novo = (No_arvore*) malloc(sizeof(No_arvore));
    novo->nota = filme.nota;
    novo->filmes = NULL;
    insere_inicio(&novo->filmes, filme);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

No_arvore* inserir_abb(No_arvore* raiz, Filme filme) {
    if (raiz == NULL) {
        return criar_no(filme);
    }

    if (filme.nota < raiz->nota) {
        raiz->esquerda = inserir_abb(raiz->esquerda, filme);
    } else if (filme.nota > raiz->nota) {
        raiz->direita = inserir_abb(raiz->direita, filme);
    } else {
        // mesma nota, insere na lista ligada
        insere_inicio(&raiz->filmes, filme);
    }

    return raiz;
}

void liberar_abb(No_arvore* raiz) {
    if (!raiz) return;
    liberar_abb(raiz->esquerda);
    liberar_abb(raiz->direita);
    libera(&raiz->filmes);
    free(raiz);
}

void medir_tempo_busca_abb(No_arvore* raiz, const char* genero, float nota_min, int ano_min) {
    int comparacoes = 0;
    clock_t inicio = clock();
    buscar_filmes_abb(raiz, genero, nota_min, ano_min, &comparacoes);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    size_t memoria = calcular_memoria_abb(raiz);

    printf("\n* Resumo da Busca ABB: *\n");
    printf("\nTempo de execucao: %.6f segundos", tempo);
    printf("\nComparacoes realizadas: %d", comparacoes);
    printf("\nMemoria estimada usada: %.2f KB\n", memoria / 1024.0);
}


size_t calcular_memoria_abb(No_arvore* raiz) {
    if (!raiz) return 0;

    size_t memoria_no = sizeof(No_arvore);
    size_t memoria_lista = 0;

    No_lista* atual = raiz->filmes;
    while (atual) {
        memoria_lista += sizeof(No_lista);
        atual = atual->prox;
    }

    return memoria_no + memoria_lista
           + calcular_memoria_abb(raiz->esquerda)
           + calcular_memoria_abb(raiz->direita);
}