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

int popular_lista(Lista *lista)
{
    cria(lista);

    FILE *arquivo = fopen("IMDB-Movie-Data.csv", "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    while (fgets(linha, sizeof(linha), arquivo))
    {
        Filme f;
        char *token;
        int coluna = 0;

        token = strtok(linha, ";");
        while (token != NULL)
        {
            limpar(token); // <- remove aspas, \n, etc.

            switch (coluna)
            {
            case 1:
                strncpy(f.titulo, token, sizeof(f.titulo));
                break;
            case 2:
                strncpy(f.genero, token, sizeof(f.genero));
                break;
            case 3:
                strncpy(f.nome_diretor, token, sizeof(f.nome_diretor));
                break;
            case 4:
                f.ano = atoi(token); // <- precisa do campo limpo
                break;
            case 5:
                f.nota = atof(token); // <- precisa do campo limpo
                break;
            }

            token = strtok(NULL, ";");
            coluna++;
        }

        insere_filme_lista(f, lista);
    }

    fclose(arquivo);
    return 1;
}

void buscar_filmes_abb(No_arvore *raiz, const char *genero, float nota_min, int ano_min, int *comparacoes)
{
    if (!raiz)
        return;

    (*comparacoes)++;
    if (raiz->nota >= nota_min)
    {
        buscar_filmes_abb(raiz->esquerda, genero, nota_min, ano_min, comparacoes);
    }

    (*comparacoes)++;
    if (raiz->nota >= nota_min)
    {
        No_lista *atual = raiz->filmes;
        while (atual)
        {
            Filme f = atual->filme;
            (*comparacoes)++;
            if (strstr(f.genero, genero) && f.ano >= ano_min)
            {
                printf("\nTitulo: %s\nGenero: %s\nDiretor: %s\nAno: %d\nNota: %.1f\n",
                       f.titulo, f.genero, f.nome_diretor, f.ano, f.nota);
            }
            atual = atual->prox;
        }
    }

    (*comparacoes)++;
    if (raiz->nota <= nota_min)
    {
        buscar_filmes_abb(raiz->direita, genero, nota_min, ano_min, comparacoes);
    }
}

No_arvore *popular_abb(const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arquivo); // pula cabeçalho

    No_arvore *raiz = NULL;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        Filme f;
        char *token;
        int coluna = 0;

        token = strtok(linha, ";");
        while (token != NULL)
        {
            // Limpar
            char limpo[256];
            int j = 0, i = 0;
            for (i; token[i]; i++)
            {
                if (token[i] != '"' && token[i] != '\n' && token[i] != '\r')
                {
                    limpo[j++] = token[i];
                }
            }
            limpo[j] = '\0';

            switch (coluna)
            {
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
            printf("Diretor: %s\n", f.nome_diretor);
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