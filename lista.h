#ifndef LISTA_H
#define LISTA_H
#include "filme.h"

typedef struct no
{
   Filme filme;
   struct no *prox;
} No_lista;

typedef No_lista *Lista;

void cria(Lista *p_l);
int vazia(Lista *p_l);
void insere_inicio(Lista *p_l, Filme filme);
void insere_filme_lista(Filme filme, Lista *lista);
int popular_lista(Lista *lista);
/* Remove todos os nós da lista */
void libera(Lista *p_l);
/* Exibe o conteúdo da lista */
void exibe(Lista *p_l);

// /* Insere um elemento na lista de maneira ordenada.
//    Retorna 0 caso o elemento já exista na lista.
//    Assume que a lista está ordenada */
// int insere_ordenado(Lista *p_l, Filme e);

// /* Verifica se a lista está ordenada */
// int ordenada(Lista *p_l);

// /* Ordena a lista */
// void ordena(Lista *p_l);

// /* Remove o elemento que está no início da lista.
//    Retorna 0 caso a lista esteja vazia */
// int remove_inicio(Lista *p_l, Filme *p_e);

// /* Remove o elemento que está no final da lista.
//    Retorna 0 caso a lista esteja vazia */
// int remove_fim(Lista *p_l, Filme *p_e);

// /* Remove o nó de valor e.
//    Retorna 0 caso este nó não tenha sido encontrado */
// int remove_valor(Lista *p_l, Filme e);

// /* Inverte os elementos de uma lista */
// void inverte(Lista *p_l);

#endif