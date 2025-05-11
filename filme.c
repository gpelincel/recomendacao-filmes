#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista.h"
#include "filme.h"
#include "abb.h"

void insere_filme_lista(Filme filme, Lista *lista)
{
    insere_inicio(lista, filme);
}

void limpar(char *str)
{
    char *src = str, *dst = str;
    while (*src)
    {
        if (*src != '"' && *src != '\n' && *src != '\r')
        {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int popular_lista(Lista *lista, int limite)
{
    cria(lista);

    clock_t inicio = clock();
    FILE *arquivo = fopen("imdb_movies.csv", "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char linha[1024];
    int total_linhas = 0;
    fgets(linha, sizeof(linha), arquivo); // pula cabeçalho

    while (fgets(linha, sizeof(linha), arquivo) && total_linhas < limite)
    {
        Filme f;
        char *token;
        int coluna = 0;

        token = strtok(linha, ",");
        while (token != NULL)
        {
            limpar(token);
            switch (coluna)
            {
            case 0:
                strncpy(f.titulo, token, sizeof(f.titulo));
                break;
            case 1:
                strncpy(f.genero, token, sizeof(f.genero));
                break;
            case 2:
                f.ano = atoi(token);
                break;
            case 3:
                f.nota = atof(token);
                break;
            }
            token = strtok(NULL, ",");
            coluna++;
        }

        insere_inicio(lista, f);
        total_linhas++;
    }

    fclose(arquivo);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    size_t memoria = calcular_memoria_lista(*lista);

    printf("\n* Resumo da Insercao na Lista: *\n");
    printf("\nTempo de execucao: %.6f segundos", tempo);
    printf("\nMemoria estimada usada: %.2f KB\n", memoria / 1024.0);
    printf("\nLinhas inseridas: %d\n", total_linhas);

    return 1;
}

void buscar_filmes_abb(No_arvore *raiz, const char *genero, float nota_min, int ano_min, int *comparacoes)
{
    if (!raiz) return;

    (*comparacoes)++;

    if (nota_min < raiz->nota) {
        // Pode haver nós à esquerda com nota >= nota_min
        buscar_filmes_abb(raiz->esquerda, genero, nota_min, ano_min, comparacoes);
    }

    // Verifica os filmes do nó atual (que tem nota == raiz->nota)
    No_lista *atual = raiz->filmes;
    while (atual) {
        Filme f = atual->filme;
        (*comparacoes)++;
        if (f.nota >= nota_min && f.ano >= ano_min && strstr(f.genero, genero)) {
            printf("\nTitulo: %s\nGenero: %s\nAno: %d\nNota: %.1f\n",
                   f.titulo, f.genero, f.ano, f.nota);
        }
        atual = atual->prox;
    }

    if (nota_min <= raiz->nota) {
        // Pode haver nós à direita com nota >= nota_min
        buscar_filmes_abb(raiz->direita, genero, nota_min, ano_min, comparacoes);
    }
}


No_arvore *popular_abb(const char *nome_arquivo, int limite)
{
    clock_t inicio = clock();
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arquivo); // pula cabeçalho

    No_arvore *raiz = NULL;
    int total_linhas = 0;

    while (fgets(linha, sizeof(linha), arquivo) && total_linhas < limite)
    {
        Filme f;
        char *token;
        int coluna = 0;

        token = strtok(linha, ",");
        while (token != NULL)
        {
            limpar(token);
            switch (coluna)
            {
            case 0:
                strncpy(f.titulo, token, sizeof(f.titulo));
                break;
            case 1:
                strncpy(f.genero, token, sizeof(f.genero));
                break;
            case 2:
                f.ano = atoi(token);
                break;
            case 3:
                f.nota = atof(token);
                break;
            }
            token = strtok(NULL, ",");
            coluna++;
        }

        raiz = inserir_abb(raiz, f);
        total_linhas++;
    }

    fclose(arquivo);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    size_t memoria = calcular_memoria_abb(raiz);

    printf("\n* Resumo da Insercao na ABB: *\n");
    printf("\nTempo de execucao: %.6f segundos", tempo);
    printf("\nMemoria estimada usada: %.2f KB\n", memoria / 1024.0);
    printf("\nLinhas inseridas: %d\n", total_linhas);

    return raiz;
}

void buscar_filmes(Lista *p_l, const char *genero, float nota_min, int ano_min)
{
    No_lista *aux = *p_l;
    int encontrados = 0;

    while (aux != NULL)
    {
        Filme f = aux->filme;

        if (strstr(f.genero, genero) != NULL && f.nota >= nota_min && f.ano >= ano_min)
        {
            printf("\nTitulo : %s\n", f.titulo);
            printf("Genero : %s\n", f.genero);
            printf("Ano    : %d\n", f.ano);
            printf("Nota   : %.1f\n", f.nota);
            encontrados++;
        }

        aux = aux->prox;
    }

    if (encontrados == 0)
    {
        printf("\n\n* Nenhum filme encontrado com os critérios fornecidos *\n");
    }
}