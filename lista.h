#ifndef LISTA_H
#define LISTA_H
#include "filme.h"

typedef struct no
{
   Filme filme;
   struct no *prox;
} No_lista;

typedef No_lista *Lista;

//Cria a lsita
void cria(Lista *p_l);
//Verifica se a lista está vazia
int vazia(Lista *p_l);
//Insere filme no início da lista
void insere_inicio(Lista *p_l, Filme filme);
//Insere um filme na lista 
void insere_filme_lista(Filme filme, Lista *lista);
//Preenche lista a partir do .csv
int popular_lista(Lista *lista);
/* Remove todos os nós da lista */
void libera(Lista *p_l);
/* Exibe o conteúdo da lista */
void exibe(Lista *p_l);
//Busca o filme de acordo com filtros
void buscar_filmes(Lista *p_l, const char *genero, float nota_min, int ano_min);
//mete o tempoo da busca
void medir_tempo_busca_lista(Lista *p_l, const char *genero, float nota_min, int ano_min);

#endif