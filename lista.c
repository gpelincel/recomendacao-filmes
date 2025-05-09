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

/* Remove o elemento que está no início da lista.
   Retorna 0 caso a lista esteja vazia */
// int remove_inicio(Lista *p_l, Filme filme)
// {
//     if (vazia(p_l))
//         return 0;

//     No_lista *aux = *p_l;

//     //Salva o elemento removido
//     *filme = aux->filme;
//     //Troca o primeiro nó da lista
//     *p_l = aux->prox;
//     free(aux);

//     return 1;
// }

/* Remove o elemento que está no final da lista.
   Retorna 0 caso a lista esteja vazia */
// int remove_fim(Lista *p_l, Filme filme)
// {
//     if (vazia(p_l))
//         return 0;

//     No_lista *aux = *p_l;

//     //Se tiver apenas um elemento
//     if (aux->prox == NULL)
//     {
//         *filme = aux->filme;
//         free(aux);
//         *p_l = NULL;
//         return 1;
//     }

//     //Chega ao final da lista
//     while (aux->prox->prox != NULL)
//         aux = aux->prox;

//     //Remove o elemento
//     *filme = aux->filme;
//     free(aux->prox);
//     aux->prox = NULL;
//     return 1;
// }

/* Insere um elemento na lista de maneira ordenada.
   Retorna 0 caso o elemento já exista na lista.
   Assume que a lista está ordenada */
// int insere_ordenado(Lista *p_l, Filme filme)
// {
//     No_lista *aux = *p_l;
//     No_lista *novo = (No_lista *)malloc(sizeof(No_lista));

//     while (aux->prox != NULL)
//     {
//         //Verifica se o elemento é compativel com essa posição
//         if (aux->filme <= filme)
//         {
//             //Se o valor for igual, retorna 0
//             if (aux->filme == filme){
//                 return 0;
//             }

//             //Adiciona o novo nó
//             novo->prox = aux->prox;
//             aux->prox = novo;
//         }

//         aux = aux->prox;
//     }

//     return 1;
// }

/* Verifica se a lista está ordenada */
// int ordenada(Lista *p_l)
// {
//     No_lista *aux = *p_l;

//     //Percorre a lista
//     while (aux->prox != NULL)
//     {
//         //Verifica se os elementos estão em ordem
//         if (aux->filme  > aux->prox->filme)
//         {
//             return 0;
//         }

//         aux = aux->prox;
//     }

//     return 1;
// }

/* Ordena a lista em ordem crescente */
// void ordena(Lista *p_l) {
//     if (*p_l == NULL || (*p_l)->prox == NULL) return; // Lista vazia ou com um único elemento

//     int trocou;
//     No_lista *aux;
//     No_lista *ultimo = NULL;

//     //Bubble Sort: Faz a ordenação comparando pares
//     do {
//         trocou = 0;
//         aux = *p_l;

//         while (aux->prox != ultimo) {
//             if (aux->filme > aux->prox->filme) {
//                 // Troca os valores dos nós
//                 int temp = aux->filme;
//                 aux->filme = aux->prox->filme;
//                 aux->prox->filme = temp;
//                 trocou = 1;
//             }
//             aux = aux->prox;
//         }
//         ultimo = aux; // Otimização: o último elemento já está ordenado

//     } while (trocou);
// }

/* Remove o nó de valor e.
   Retorna 0 caso este nó não tenha sido encontrado */
// int remove_valor(Lista *p_l, Filme filme){
//     No_lista *aux = *p_l;

//     if (aux->filme == filme)
//     {
//         free(aux);

//         return 1;
//     }

//     while (aux->prox->prox != NULL)
//     {
//         //Verifica se o elemento existe
//         if (aux->prox->filme == filme)
//         {
//             //Salva o nó para não perder o restante da lista
//             No_lista *backup = aux->prox->prox;
//             free(aux->prox);
//             aux->prox = backup;
//             return 1;
//         } else {
//             return 0;
//         }
//     }

// }

/* Inverte os elementos de uma lista */
// void inverte(Lista *p_l){
//     No_lista *aux = *p_l;
//     No_lista *anterior = NULL;
//     No_lista *proximo_no = aux->prox;

//     //Looping infinito para ter acesso ao último elemento da lista
//     while (1 == 1)
//     {
//         //Reordena os ponteiros
//         aux->prox = anterior;
//         anterior = aux;
//         aux = proximo_no;

//         if (proximo_no == NULL)
//         {
//             *p_l = anterior;
//             break;
//         }

//         proximo_no = proximo_no->prox;
//     }
// }