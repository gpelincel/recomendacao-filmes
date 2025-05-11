#ifndef ABB_H
#define ABB_H
#include <time.h>
#include "lista.h"
#include "filme.h"

typedef struct No_arvore {
    float nota;
    Lista filmes; // ponteiro para No_lista
    struct No_arvore* esquerda;
    struct No_arvore* direita;
} No_arvore;

//Insere um filme na ABB
No_arvore* inserir_abb(No_arvore* raiz, Filme filme);
//Limpa a ABB
void liberar_abb(No_arvore* raiz);
//Filtra os filmes cadastrado na ABB
void buscar_filmes_abb(No_arvore* raiz, const char* genero, float nota_min, int ano_min, int* comparacoes);
//Mede o tempo levado para buscar ABB
void medir_tempo_busca_abb(No_arvore* raiz, const char* genero, float nota_min, int ano_min);
//Preenche a ABB com os dados do .csv
No_arvore* popular_abb(const char* nome_arquivo);
//Calcula a memória RAM utilizada para as operção da ABB
size_t calcular_memoria_abb(No_arvore* raiz);

#endif
