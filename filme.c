#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista.h"
#include "filme.h"

void insere_filme_lista(Filme filme, Lista *lista)
{
    insere_fim(lista, filme);
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
