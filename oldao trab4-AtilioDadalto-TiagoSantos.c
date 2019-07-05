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
 * Structs e typedefs em CamelCase: ArvBin, Lista.
 * Funções em snake_case: imprime_pre_ordem_ArvBin(), insere_lista().
 * Ponteiros com asterisco do lado do nome da variável: ArvBin *foo, int *bar.
 */

/* APENAS LISTAS ENCADEADAS */
int main(int argc, char *argv[])
{
    clr_scr();

    struct timeval t;          // Para gerar semente do srand
    char strTexto[TAM_STRING]; // Vetor para armazenamento temporário de strings do texto
    int nArquivos = argc - 2, posicao = 0, i = 0;
    Palavra *palavraAleatoria, *palavraBusca;

    /* Teste de múltiplos arquivos */
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
    Lista *listas;
    SentRandPal *palavrasAleatorias = cria_RandPal(); // Lista para busca de palavras
    Palavra *palavra;
    printf("Lista de busca de palavras criada com sucesso.\n");

    gettimeofday(&t, NULL); // Para gerar semente do srand
    srand((unsigned int)t.tv_usec);

    printf("Criando estruturas...\n");
    
    listas = cria_Lista();
    for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
    {
        fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
        printf("%io arquivo aberto com sucesso.\n", i + 1);
        printf("%ia estrutura criada com sucesso.\n", i + 1);

        printf("Lendo %io arquivo...\n", i + 1);
        while (!feof(fs))
        {
            posicao = le_palavra(fs, strTexto);

            /* Preenchendo listas[i] de palavras aleatórias */
            insere_RandPal(strTexto, palavrasAleatorias);

            /* Preenchendo estruturas de dados do projeto */
            palavra = cria_Palavra(argv[i + 2],strTexto, posicao);
            insere_Lista(palavra, listas);
        }
        fclose(fs);
    }
    printf("\nEstruturas criadas com sucesso.\n");

    for (i = 0; i < nBuscas; i++)
    {
        /* Carregando o vetor com palavras aleatórias da listas[i] */
        strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
    }


    printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
     
    printf("\n\n\nLISTA ENCADEADA\n\n\n");
    imprime_Lista(listas);
    
    for (int i = 0; i < nBuscas; i++)
    {
        palavraAleatoria = busca_Lista(vetBusca[i], listas);

        if (palavraAleatoria != NULL)
        {
            printf("PALAVRA ENCONTRADA.\n");
            imprime_Palavra(palavraAleatoria);
        }
        else
        {
            printf("Palavra %s não encontrada.\n", vetBusca[i]);
        }
        printf("\n");
    }

    char stringBuscada[TAM_STRING];
    printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
    scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1
    palavraBusca = busca_Lista(stringBuscada, listas);
    if (palavraBusca != NULL)
    {
        printf("PALAVRA ENCONTRADA.\n");
        imprime_Palavra(palavraBusca);
    }
    else
    {
        printf("A palavra nao foi encontrada nas listas.\n");
    }
    

    printf("\nFim da leitura. Liberando estruturas...\n");
    libera_Lista(listas);

    libera_RandPal(palavrasAleatorias);
    printf("Estruturas liberadas com sucesso. Talvez. hehe\n");

    return 0;
}
