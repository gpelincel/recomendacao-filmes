#include <time.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista.h"
#include "filme.h"

// Inicializa uma lista: define o ponteiro inicial como NULL
void cria(Lista *p_l)
{
    *p_l = NULL;
}

// Verifica se a lista está vazia (retorna 1 se estiver, 0 caso contrário)
int vazia(Lista *p_l)
{
    return (*p_l == NULL);
}

// Insere um filme no início da lista
void insere_inicio(Lista *p_l, Filme filme)
{
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista)); // Aloca memória para novo nó
    novo->filme = filme;         // Atribui os dados do filme ao nó
    novo->prox = *p_l;           // O próximo do novo nó aponta para o início atual
    *p_l = novo;                 // Atualiza o ponteiro da lista para o novo nó
}

// Insere um filme no final da lista
void insere_fim(Lista *p_l, Filme filme)
{
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista)); // Aloca novo nó
    novo->filme = filme;
    novo->prox = NULL;

    if (vazia(p_l)) {
        *p_l = novo; // Lista vazia → novo nó é o primeiro
    } else {
        No_lista *aux = *p_l;
        while (aux->prox != NULL) // Percorre até o fim
            aux = aux->prox;

        aux->prox = novo; // Conecta o novo nó no fim
    }
}

// Libera toda a memória da lista, removendo todos os nós
void libera(Lista *p_l)
{
    No_lista *aux;

    while (*p_l != NULL) {
        aux = *p_l;           // Armazena nó atual
        *p_l = aux->prox;     // Avança para o próximo
        free(aux);            // Libera o nó atual
    }
}

// Exibe todos os filmes armazenados na lista
void exibe(Lista *p_l)
{
    No_lista *aux = *p_l;

    while (aux != NULL) {
        printf("\nTitulo: %s\nGenero: %s\nAno: %d\nNota: %.1f\n",
               aux->filme.titulo, aux->filme.genero, aux->filme.ano, aux->filme.nota);
        aux = aux->prox;
    }
    printf("\n");
}

// Realiza a busca na lista por filtros de gênero, nota mínima e ano mínimo
// Também mede tempo de execução e comparações
void medir_tempo_busca_lista(Lista *p_l, const char *genero, float nota_min, int ano_min)
{
    clock_t inicio, fim;
    double tempo;
    int comparacoes = 0;
    int encontrados = 0;

    No_lista *aux = *p_l;

    inicio = clock(); // Início da medição de tempo

    // Percorre toda a lista fazendo a filtragem
    while (aux != NULL) {
        comparacoes++; // Conta cada filme verificado
        Filme f = aux->filme;

        // Verifica se o filme atende aos critérios
        if (strstr(f.genero, genero) && f.nota >= nota_min && f.ano >= ano_min) {
            printf("\nTitulo: %s\nGenero: %s\nAno: %d\nNota: %.1f\n",
                   f.titulo, f.genero, f.ano, f.nota);
            encontrados++;
        }

        aux = aux->prox;
    }

    fim = clock(); // Fim da medição de tempo
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC; // Calcula tempo em segundos

    // Caso nenhum filme tenha sido encontrado
    if (encontrados == 0) {
        printf("Nenhum filme encontrado com os critérios fornecidos.\n");
    }

    // Estima o uso de memória: tamanho dos nós + struct Filme (campos embutidos)
    size_t tamanho_no = sizeof(No_lista);
    size_t tamanho_filme = sizeof(Filme);
    int total_nos = 0;

    // Conta quantos nós existem na lista
    aux = *p_l;
    while (aux != NULL) {
        total_nos++;
        aux = aux->prox;
    }

    // Multiplica pelo total de nós para obter memória total estimada
    size_t memoria_total = total_nos * (tamanho_no + tamanho_filme);

    // Exibe o resumo da operação
    printf("\n* Resumo da Busca Lista: *\n");
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Comparacoes realizadas: %d\n", comparacoes);
}
