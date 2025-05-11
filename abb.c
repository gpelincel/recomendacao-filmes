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

void buscar_filmes_abb(No_arvore* raiz, const char* genero, float nota_min, int ano_min, int* comparacoes) {
    if (!raiz) return;

    (*comparacoes)++;
    if (raiz->nota >= nota_min) {
        buscar_filmes_abb(raiz->esquerda, genero, nota_min, ano_min, comparacoes);
    }

    (*comparacoes)++;
    if (raiz->nota >= nota_min) {
        No_lista* atual = raiz->filmes;
        while (atual) {
            Filme f = atual->filme;
            (*comparacoes)++;
            if (strstr(f.genero, genero) && f.ano >= ano_min) {
                printf("\nTitulo: %s\nGenero: %s\nDiretor: %s\nAno: %d\nNota: %.1f\n",
                       f.titulo, f.genero, f.nome_diretor, f.ano, f.nota);
            }
            atual = atual->prox;
        }
    }

    (*comparacoes)++;
    if (raiz->nota <= nota_min) {
        buscar_filmes_abb(raiz->direita, genero, nota_min, ano_min, comparacoes);
    }
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


No_arvore* popular_abb(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arquivo); // pula cabeçalho

    No_arvore* raiz = NULL;

    while (fgets(linha, sizeof(linha), arquivo)) {
        Filme f;
        char* token;
        int coluna = 0;

        token = strtok(linha, ";");
        while (token != NULL) {
            // Limpar
            char limpo[256];
            int j = 0 , i = 0;
            for (i; token[i]; i++) {
                if (token[i] != '"' && token[i] != '\n' && token[i] != '\r') {
                    limpo[j++] = token[i];
                }
            }
            limpo[j] = '\0';

            switch (coluna) {
                case 1:
                    strncpy(f.titulo, limpo, sizeof(f.titulo));
                    break;
                case 2:
                    strncpy(f.genero, limpo, sizeof(f.genero));
                    break;
                case 3:
                    strncpy(f.nome_diretor, limpo, sizeof(f.nome_diretor));
                    break;
                case 4:
                    f.ano = atoi(limpo);
                    break;
                case 5:
                    f.nota = atof(limpo);
                    break;
            }

            token = strtok(NULL, ";");
            coluna++;
        }

        raiz = inserir_abb(raiz, f);
    }

    fclose(arquivo);
    return raiz;
}
