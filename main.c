#include <stdio.h>
#include "filme.h"
#include "lista.h"

int main(){
    Lista lista;

    if (popular_lista(&lista)) {
        printf("Filmes carregados com sucesso!\n");
        exibe(&lista);
    } else {
        printf("Erro ao carregar os filmes.\n");
    }

    libera(&lista);
    return 0;
}
