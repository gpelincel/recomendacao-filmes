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

No_arvore* inserir_abb(No_arvore* raiz, Filme filme);
void liberar_abb(No_arvore* raiz);
void buscar_filmes_abb(No_arvore* raiz, const char* genero, float nota_min, int ano_min, int* comparacoes);
void medir_tempo_busca_abb(No_arvore* raiz, const char* genero, float nota_min, int ano_min);
No_arvore* popular_abb(const char* nome_arquivo);
size_t calcular_memoria_abb(No_arvore* raiz);

#endif
