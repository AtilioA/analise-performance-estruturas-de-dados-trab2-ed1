#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "include/lista_encadeada.h"
#include "include/indexador.h"
#include "include/arquivos.h"

#define TAM_STRING 80

/*
 * CONVENÇÕES PARA O TRABALINDO:
 * Constantes em CAPS: UNUSED, TRUE, FALSE.
 */

/* APENAS LISTAS ENCADEADAS */
int main(int argc, char *argv[])
{
    clr_scr();

    struct timeval t;          // Para gerar semente do srand
    char strTexto[TAM_STRING]; // Vetor para armazenamento temporário de strings do texto
    int posicao;

    /* Teste múltiplos arquivos */
    if (argv[1] == NULL)
    {
        printf("Entrada de buscas invalida.\n");
        exit(1);
    }

    int nBuscas = atoi(argv[1]);
    if (nBuscas < 1)
    {
        printf("Numero de buscas invalido.\n");
        exit(1);
    }

    char vetBusca[nBuscas][TAM_STRING]; // Vetor para busca de palavras
    FILE *fs;
    int i = 0;
    int nArquivos = argc - 2;
    Lista *listas[nArquivos];
    SentRandPal *palavrasAleatorias = cria_RandPal(); // Lista para busca de palavras
    Palavra *palavra;
    printf("Lista de busca de palavras criada com sucesso.\n");

    gettimeofday(&t, NULL); // Para gerar semente do srand
    srand((unsigned int)t.tv_usec);

    for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
    {
        printf("Criando estruturas...\n");
        fs = le_arquivo(argv[i + 2]);
        printf("Arquivo aberto com sucesso.\n");
        printf("Lendo arquivos...\n");
        listas[i] = cria_Lista();
        strncpy(listas[i]->nomeArquivo, argv[i + 2], 79); // argv[2] até argv[argc]
        printf("Estruturas criadas com sucesso.\n");

        while (!feof(fs))
        {
            le_palavra(fs, strTexto);

            /* Preenchendo listas[i] encadeada de palavras aleatórias */
            insere_RandPal(strTexto, palavrasAleatorias);
            posicao = ftell(fs) - strlen(strTexto) + 1;

            /* Preenchendo estruturas de dados do projeto */
            palavra = cria_Palavra(strTexto, posicao);
            insere_Lista(palavra, listas[i]);
        }

        for (int i = 0; i < nBuscas; i++)
        {
            /* Carregando o vetor com palavras aleatórias da listas[i] */
            strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
        }
    }

    for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
    {
        printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
        printf("\n\n\nLISTA ENCADEADA\n\n\n");
        imprime_Lista(listas[i]);
        for (int i = 0; i < nBuscas; i++)
        {
            Palavra *palavraLista = busca_Lista(vetBusca[i], listas[i]);

            if (palavraLista != NULL)
            {
                printf("A palavra %s foi encontrada na listas[i].\n", vetBusca[i]);
            }
        }

        printf("\nFim da leitura. Liberando estruturas...\n");
        libera_RandPal(palavrasAleatorias);
        fclose(fs);
        libera_Lista(listas[i]);
        printf("Estruturas liberadas com sucesso. Talvez. hehe\n");
    }

    /*
    char stringBuscada[TAM_STRING];
    printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
    scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

    Palavra *palavraLista = busca_Lista(stringBuscada, listas[i]);

    if (palavraLista != NULL)
    {
        printf("A palavra \"%s\" foi encontrada nas listas.\n", stringBuscada);
        imprime_Palavra(palavraLista);
    }
    else
    {
        printf("A palavra nao foi encontrada nas listas.\n");
    }

    */

    return 0;
}
