#include "include/lista_encadeada.h"
#include "include/arvore_binaria.h"
#include "include/arvore_AVL.h"
#include "include/indexador.h"
#include "include/arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

/*
 * CONVENÇÕES PARA O TRABALINDO:
 * Constantes em CAPS: UNUSED, TRUE, FALSE.
 * Structs e typedefs em CamelCase: ArvBin, Lista.
 * Funções em snake_case: pre_ordem_ArvBin(), insere_lista().
 * Ponteiros com asterisco do lado do nome da variável: ArvBin *foo, int *bar.
 */

int main(int argc, char *argv[])
{
    clr_scr();

    printf("Criando estruturas...\n");
    struct timeval t;
    Lista *lista = cria_Lista();
    ArvBin *arvere = criaArvBin();
    ArvAVL *arvl = cria_ArvAVL();
    printf("Estruturas criadas com sucesso.\n");

    tSentRandPal *pal_al = newRandpal(); // lista de busca de palavras
    Palavra *pal;
    char strat[80];
    int posicao;
    printf("Lista de busca de palavras criada com sucesso.\n");

    FILE *f = le_arquivo(argv[1]);

    if (argv[2] == NULL)
    {
        printf("Entrada de buscas invalida.\n");
        exit(1);
    }

    int nBuscas = atoi(argv[2]);
    if (nBuscas < 1)
    {
        printf("Numero de buscas invalido.\n");
        exit(1);
    }
    printf("Arquivo aberto com sucesso.\n");

    char vet[nBuscas][80]; // vetor de busca

    gettimeofday(&t, NULL);
    srand((unsigned int)t.tv_usec);

    printf("Lendo arquivo...\n");
    while (!feof(f))
    {
        fscanf(f, "%s", strat); // vo usar o fscanf de placeholder até a gnt fazer uma função de leitura de palavras decente
        insereRandPal(strat, pal_al);
        posicao = ftell(f) - strlen(strat) + 1;
        pal = cria_Palavra(strat, posicao);
        insere_ArvBin(arvere, pal);
        pal = cria_Palavra(strat, posicao);
        insere_Lista(pal, lista);
        pal = cria_Palavra(strat, posicao);
        insere_ArvAVL(arvl, pal);
    }

    for (int i = 0; i < nBuscas; i++)
    {
        strcpy(vet[i], buscaRandPal(rand() % (pal_al->qtd), pal_al)); // carrega o vetor com palavras aleatórias da lista
    }

    printf("\n\nLEITURA CONCLUIDA. IMPRIMINDO RESULTADOS:");

    printf("\n\n\nARVORE BINARIA (em ordem)\n\n\n");
    em_ordem_ArvBin(arvere);
    printf("\n\n\nARVORE AVL (em ordem)\n\n\n");
    em_ordem_ArvAVL(arvl);
    printf("\n\n\nLISTA ENCADEADA\n\n\n");
    imprime_lista(lista);
    for (int i = 0; i < nBuscas; i++)
    {
        Palavra *palavraLista = busca_Lista(vet[i], lista);
        Palavra *palavraArvore = consulta_ArvBin(arvere, vet[i]);
        Palavra *palavraAVL = consulta_ArvAVL(arvl, vet[i]);
        if (palavraLista != NULL)
        {
            printf("A palavra %s foi encontrada na lista.\n", vet[i]);
        }
        if (palavraArvore != NULL)
        {
            printf("A palavra %s foi encontrada na arvore.\n", vet[i]);
        }
        if (palavraAVL != NULL)
        {
            printf("A palavra %s foi encontrada na arvore AVL.\n", vet[i]);
        }
    }

    printf("\nFim da leitura. Liberando estruturas...\n");
    destroiRandPal(pal_al);
    //imprime_lista(lista);
    fclose(f);
    libera_ArvBin(arvere);
    libera_ArvAVL(arvl);
    destroi_lista(lista);

    printf("Estruturas liberadas com sucesso... talvez... eu não assumo o BO do valgrind!\n");

    return 0;
}
