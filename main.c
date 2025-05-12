#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "abb.h"
#include "lista.h"

// Declaração da função que coleta os filtros e executa a busca
void get_filtros(int opcao, Lista *lista, No_arvore *arvore);

int main()
{
    int limite = 0;

    // Loop para solicitar ao usuário o número de linhas que deseja carregar do CSV
    do
    {
        printf("Insira o limite de cadastro de dados desejado (de 0 a 10.000): ");
        scanf("%d", &limite);
    } while (limite < 0 && limite > 10000); // Condição incorreta: nunca entra no loop se limite for > 10000 (*ver observação abaixo)

    Lista lista;

    // Popular a árvore binária e a lista encadeada com os dados do CSV
    No_arvore *raiz_abb = popular_abb("imdb_movies.csv", limite);
    popular_lista(&lista, limite);

    int opcao;
    do
    {
        // Menu principal com opções de busca e exibição
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
        getchar(); // Consome o '\n' deixado pelo scanf

        // Executa a opção escolhida
        if (opcao == 1)
        {
            exibe(&lista); // Exibe a lista encadeada completa
        }
        else if (opcao == 2 || opcao == 4)
        {
            // Opções de busca com filtros, chama a função que coleta os parâmetros
            get_filtros(opcao, &lista, raiz_abb);
        }
        else if (opcao == 3)
        {
            // Exibe os filmes em ordem (ABB - in-order traversal)
            exibir_arvore_in_ordem(raiz_abb);
        }

    } while (opcao != 0); // Sai do programa quando o usuário digita 0

    libera(&lista); // Libera a memória da lista antes de encerrar
    return 0;
}

// Função auxiliar que coleta os filtros do usuário e executa a busca conforme a opção
void get_filtros(int opcao, Lista *lista, No_arvore *arvore)
{
    char genero[50], entrada[50];
    float nota;
    int ano;

    printf("\n*Aperte 'Enter' para deixar o filtro em branco*\n\n");

    // Coleta o gênero desejado
    printf("Genero desejado: ");
    fgets(genero, sizeof(genero), stdin);
    genero[strcspn(genero, "\n")] = '\0'; // Remove o caractere de nova linha

    // Coleta a nota mínima (ou considera 0 se vazio)
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

    // Coleta o ano mínimo (ou considera 0 se vazio)
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

    // Executa a busca na lista ou na ABB, dependendo da opção
    if (opcao == 2)
    {
        medir_tempo_busca_lista(lista, genero, nota, ano);
    }
    else
    {
        medir_tempo_busca_abb(arvore, genero, nota, ano);
    }
}