#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista.h"
#include "filme.h"
#include "abb.h"

//Limpa uma string de carcteres que possam afetar o cadastro
void limpar(char *str)
{
    //Variável auxiliar
    char *src = str, *dst = str;
    while (*src)
    {
        //Verifica char por char e limpa remove o que é desnecessário
        if (*src != '"' && *src != '\n' && *src != '\r')
        {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

//Lê a linha do arquivo csv
//Trecho separado para deixar o código de população mais limpo
int ler_linha_csv(char *linha, Filme *f)
{
    char *token;
    int coluna = 0;

    token = strtok(linha, ",");
    while (token != NULL)
    {
        //Remove caracteres indesejados
        limpar(token);
        switch (coluna)
        {
        //Monta a struct a partir da coluna da linha
        case 0: strncpy(f->titulo, token, sizeof(f->titulo)); break;
        case 1: strncpy(f->genero, token, sizeof(f->genero)); break;
        case 2: f->ano = atoi(token); break;
        case 3: f->nota = atof(token); break;
        }
        token = strtok(NULL, ",");

        //Avança para a próxima coluna
        coluna++;
    }

    return (coluna >= 4); // garante que os campos principais foram lidos
}

int popular_lista(Lista *lista, int limite)
{
    //Cria a lista encadeada
    cria(lista);
    FILE *arquivo = fopen("imdb_movies.csv", "r");

    //Verifica a abertura do arquivo
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho do arquivo

    //Conta o total de registros inseridos
    int total = 0;
    //Inicia a contagem e tempo do processador
    clock_t inicio = clock();

    while (fgets(linha, sizeof(linha), arquivo) && total < limite)
    {
        //Faz a leitura da linha e insere no inicio da lista
        Filme f;
        if (ler_linha_csv(linha, &f))
        {
            insere_inicio(lista, f);
            total++;
        }
    }

    //Fecha a leitura do arquivo
    fclose(arquivo);
    clock_t fim = clock();

    //Calcula o tempo de CPU utilizado
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    //Exibe as métricas
    printf("\n* Resumo da Insercao na Lista: *\n");
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Linhas inseridas: %d\n", total);

    return 1;
}


//Filtra os registros de filmes da lista
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

//Busca os filmes cadastrados na árvore binária
void buscar_filmes_abb(No_arvore *raiz, const char *genero, float nota_min, int ano_min, int *comparacoes)
{
    if (!raiz) return;

    //Soma o total de comparações (nós percorridos)
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
        //Se o filme corresponde aos critérios, ele é exibido
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

//Popula a ABB com registro dos filmes, assim como na lista
No_arvore *popular_abb(const char *nome_arquivo, int limite)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    No_arvore *raiz = NULL;
    int total = 0;
    clock_t inicio = clock();

    while (fgets(linha, sizeof(linha), arquivo) && total < limite)
    {
        Filme f;
        if (ler_linha_csv(linha, &f))
        {
            raiz = inserir_abb(raiz, f);
            total++;
        }
    }

    fclose(arquivo);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n* Resumo da Insercao na ABB: *\n");
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Linhas inseridas: %d\n", total);

    return raiz;
}