#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "abb.h"
#include "lista.h"

void get_filtros(int opcao, Lista *lista, No_arvore *arvore);

int main()
{
    int limite = 0;
    do
    {
        printf("Insira o limite de cadastro de dados desejado (de 0 a 10.000): ");
        scanf("%d", &limite);
    } while (limite < 0 && limite > 10000);

    Lista lista;

    No_arvore *raiz_abb = popular_abb("imdb_movies.csv", limite);
    popular_lista(&lista, limite);

    int opcao;
    do
    {
        printf("\n\n----- Menu -----\n");
        printf("\n** Menu Lista **\n");
        printf("1 - Exibir todos os filmes\n");
        printf("2 - Buscar filmes por filtros\n");
        printf("\n** Menu ABB **\n");
        printf("3 - Exibir todos os filmes\n");
        printf("4 - Buscar filmes por filtros\n");
        printf("\n0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa o \n

        if (opcao == 1)
        {
            exibe(&lista);
        }
        else if (opcao == 2 || opcao == 4)
        {
            get_filtros(opcao, &lista, raiz_abb);
        }
        else if (opcao == 3)
        {
            exibir_arvore_in_ordem(raiz_abb);
        }

    } while (opcao != 0);

    libera(&lista);
    return 0;
}

void get_filtros(int opcao, Lista *lista, No_arvore *arvore)
{
    char genero[50], entrada[50];
    float nota;
    int ano;
    printf("\n*Aperte 'Enter' para deixar o filtro em branco*\n\n");

    printf("Genero desejado: ");
    fgets(genero, sizeof(genero), stdin);
    genero[strcspn(genero, "\n")] = '\0'; // remover \n

    printf("Nota minima: ");
    if (fgets(entrada, sizeof(entrada), stdin) != NULL)
    {
        entrada[strcspn(entrada, "\n")] = 0;
        if (strlen(entrada) == 0)
        {
            nota = 0.0f;
        }
        else
        {
            if (sscanf(entrada, "%f", &nota) != 1)
            {
                nota = 0.0f;
            }
        }
    }

    printf("Ano minimo: ");
    if (fgets(entrada, sizeof(entrada), stdin) != NULL)
    {
        entrada[strcspn(entrada, "\n")] = 0;
        if (strlen(entrada) == 0)
        {
            ano = 0;
        }
        else
        {
            if (sscanf(entrada, "%i", &ano) != 1)
            {
                ano = 0;
            }
        }
    }

    if (opcao == 2)
    {
        medir_tempo_busca_lista(lista, genero, nota, ano);
    }
    else
    {
        medir_tempo_busca_abb(arvore, genero, nota, ano);
    }
}