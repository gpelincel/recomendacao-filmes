#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "abb.h"
#include "lista.h"

int main(){
    Lista lista;

    No_arvore* raiz_abb = popular_abb("IMDB-Movie-Data.csv");
    medir_tempo_busca_abb(raiz_abb, "Action", 8.0, 2016);
    liberar_abb(raiz_abb);

    if (popular_lista(&lista)) {
        printf("Filmes carregados com sucesso!\n");
    } else {
        printf("Erro ao carregar os filmes.\n");
    }

    int opcao;
    do {
        printf("\n----- Menu -----\n");
        printf("\n** Menu Lista **\n");
        printf("1 - Exibir todos os filmes\n");
        printf("2 - Buscar filmes por filtros\n");
        printf("\n** Menu ABB **\n");
        printf("3 - Exibir todos os filmes\n");
        printf("4 - Buscar filmes por filtros\n");
        printf("\n** Menu Comparacao **\n");
        printf("5 - Comparar Lista com ABB\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa o \n

        if (opcao == 1) {
            exibe(&lista);
        } else if (opcao == 2) {
            char genero[50], entrada[50];
            float nota;
            int ano;

            printf("\n*Aperte 'Enter' para deixar o filtro em branco*\n\n");

            printf("Genero desejado: ");
            fgets(genero, sizeof(genero), stdin);
            genero[strcspn(genero, "\n")] = '\0'; // remover \n

            printf("Nota minima: ");
            if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
                entrada[strcspn(entrada, "\n")] = 0;
                if (strlen(entrada) == 0) {
                    nota = 0.0f;
                } else {
                    if (sscanf(entrada, "%f", &nota) != 1) {
                        nota = 0.0f;
                    }
                }
            }

            printf("Ano minimo: ");
            if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
                entrada[strcspn(entrada, "\n")] = 0;
                if (strlen(entrada) == 0) {
                    ano = 0;
                } else {
                    if (sscanf(entrada, "%i", &ano) != 1) {
                        ano = 0;
                    }
                }
            }

            //buscar_filmes(&lista, genero, nota, ano);
            medir_tempo_busca_lista(&lista, genero, nota, ano);
        }

    } while (opcao != 0);

    libera(&lista);
    return 0;
}
