#include "include/lista_encadeada.h"
#include "include/arvore_binaria.h"
#include "include/arvore_AVL.h"
#include "include/arvore_trie.h"
#include "include/tabela_hash.h"
#include "include/indexador.h"
#include "include/arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define TAM_STRING 80

/*
 * CONVENÇÕES PARA O TRABALINDO:
 * Constantes em CAPS: UNUSED, TRUE, FALSE.
 * Structs e typedefs em CamelCase: ArvBin, Lista.
 * Funções em snake_case: imprime_pre_ordem_ArvBin(), insere_lista().
 * Ponteiros com asterisco do lado do nome da variável: ArvBin *foo, int *bar.
 */

int main(int argc, char *argv[])
{
    clr_scr();

    struct timeval t;          // Para gerar semente do srand
    char strTexto[TAM_STRING]; // Vetor para armazenamento temporário de strings do texto
    int posicao;

    printf("Criando estruturas...\n");
    Lista *lista = cria_Lista();
    ArvBin *arvBin = criaArvBin();
    ArvAVL *arvAVL = cria_ArvAVL();
    // ArvTrie *arvTrie = cria_ArvTrie();
    TabelaHash *tabela = cria_Hash();
    printf("Estruturas criadas com sucesso.\n");

    SentRandPal *palavrasAleatorias = cria_RandPal(); // Lista para busca de palavras
    Palavra *palavra;
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
    char vetBusca[nBuscas][TAM_STRING]; // Vetor para busca de palavras

    gettimeofday(&t, NULL); // Para gerar semente do srand
    srand((unsigned int)t.tv_usec);

    printf("Lendo arquivo...\n");
    while (!feof(f))
    {
        le_palavra(f, strTexto);

        /* Preenchendo lista encadeada de palavras aleatórias */
        insere_RandPal(strTexto, palavrasAleatorias);
        posicao = ftell(f) - strlen(strTexto) + 1;

        /* Preenchendo estruturas de dados do projeto */
        palavra = cria_Palavra(strTexto, posicao);
        insere_Lista(palavra, lista);

        palavra = cria_Palavra(strTexto, posicao);
        insere_ArvBin(arvBin, palavra);

        palavra = cria_Palavra(strTexto, posicao);
        insere_ArvAVL(arvAVL, palavra);

        // palavra = cria_Palavra(strTexto, posicao);
        // insere_ArvTrie(arvTrie, palavra);

        palavra = cria_Palavra(strTexto, posicao);
        insere_Hash(palavra, tabela);
    }

    for (int i = 0; i < nBuscas; i++)
    {
        /* Carregando o vetor com palavras aleatórias da lista */
        strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
    }

    printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");

    printf("\n\n\nARVORE BINARIA (em ordem)\n\n\n");
    imprime_em_ordem_ArvBin(arvBin);
    printf("\n\n\nARVORE AVL (em ordem)\n\n\n");
    imprime_em_ordem_ArvAVL(arvAVL);
    printf("\n\n\nLISTA ENCADEADA\n\n\n");
    imprime_Lista(lista);
    printf("\n\n\nTABELA HASH COM AVL (em ordem)\n\n\n");
    printar_Hash(tabela);

    for (int i = 0; i < nBuscas; i++)
    {
        Palavra *palavraLista = busca_Lista(vetBusca[i], lista);
        Palavra *palavraArvore = busca_ArvBin(arvBin, vetBusca[i]);
        Palavra *palavraAVL = busca_ArvAVL(arvAVL, vetBusca[i]);
        // Palavra *palavraTrie = busca_ArvTrie(arvTrie, vetBusca[i]);
        Palavra *palavraHash = busca_Hash(vetBusca[i], tabela);

        if (palavraLista != NULL)
        {
            printf("A palavra %s foi encontrada na lista.\n", vetBusca[i]);
        }
        if (palavraArvore != NULL)
        {
            printf("A palavra %s foi encontrada na arvore.\n", vetBusca[i]);
        }
        if (palavraAVL != NULL)
        {
            printf("A palavra %s foi encontrada na arvore AVL.\n", vetBusca[i]);
        }
        /*
        if (palavraTrie != NULL)
        {
            printf("A palavra %s foi encontrada na arvore trie.\n", vetBusca[i]);
        }
        */
        if (palavraHash != NULL)
        {
            printf("A palavra %s foi encontrada na tabela hash.\n", vetBusca[i]);
        }
    }

    char stringBuscada[TAM_STRING];
    printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
    scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

    Palavra *palavraLista = busca_Lista(stringBuscada, lista);
    Palavra *palavraArvore = busca_ArvBin(arvBin, stringBuscada);
    Palavra *palavraAVL = busca_ArvAVL(arvAVL, stringBuscada);
    // Palavra *palavraTrie = busca_ArvTrie(arvTrie, stringBuscada);
    Palavra *palavraHash = busca_Hash(stringBuscada, tabela);

    if (palavraLista != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na lista.\n", stringBuscada);
        imprime_Palavra(palavraLista);
    }
    else
    {
        printf("A palavra nao foi encontrada na lista.\n");
    }
    if (palavraArvore != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na arvore binaria.\n", stringBuscada);
        imprime_Palavra(palavraArvore);
    }
    else
    {
        printf("A palavra nao foi encontrada na arvore binária.\n");
    }
    if (palavraAVL != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na arvore AVL.\n", stringBuscada);
        imprime_Palavra(palavraAVL);
    }
    else
    {
        printf("A palavra nao foi encontrada na arvore AVL.\n");
    }
    /*
    if (palavraTrie != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na arvore trie.\n", stringBuscada);
        imprime_Palavra(palavraTrie);
    }
    else
    {
        printf("A palavra nao foi encontrada na arvore trie.\n");
    }
    */
    if (palavraHash != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na tabela hash.\n", stringBuscada);
        imprime_Palavra(palavraHash);
    }
    else
    {
        printf("A palavra nao foi encontrada na hash.\n");
    }

    printf("\nFim da leitura. Liberando estruturas...\n");
    libera_RandPal(palavrasAleatorias);
    fclose(f);
    libera_Lista(lista);
    libera_ArvBin(arvBin);
    libera_ArvAVL(arvAVL);
    // libera_ArvTrie(arvAVL);
    libera_Hash(tabela);
    printf("Estruturas liberadas com sucesso. Talvez. hehe\n");

    return 0;
}
