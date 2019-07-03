#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "include/lista_encadeada.h"
#include "include/arvore_binaria.h"
#include "include/arvore_AVL.h"
#include "include/arvore_trie.h"
#include "include/tabela_hash.h"
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

// FODA
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
    int nArquivos = argc + 2;
    Lista *listas[nArquivos];
    ArvBin *arvoresBin[nArquivos];
    ArvAVL *arvoresAVL[nArquivos];
    ArvTrie *arvoresTrie[nArquivos];
    TabelaHash *tabelas[nArquivos];
    SentRandPal *palavrasAleatorias = cria_RandPal(); // Lista para busca de palavras
    Palavra *palavra;
    printf("Lista de busca de palavras criada com sucesso.\n");

    gettimeofday(&t, NULL); // Para gerar semente do srand
    srand((unsigned int)t.tv_usec);

    for (i = 2; i < nArquivos + 2; i++)
    {
        printf("Criando estruturas...\n");
        fs = le_arquivo(argv[i + 2]);
        printf("Arquivo aberto com sucesso.\n");
        printf("Lendo arquivo...\n");
        listas[i] = cria_Lista();
        arvoresBin[i] = cria_ArvBin();
        arvoresAVL[i] = cria_ArvAVL();
        arvoresTrie[i] = cria_ArvTrie();
        tabelas[i] = cria_Hash();
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

            palavra = cria_Palavra(strTexto, posicao);
            insere_ArvBin(arvoresBin[i], palavra);

            palavra = cria_Palavra(strTexto, posicao);
            insere_ArvAVL(arvoresAVL[i], palavra);

            palavra = cria_Palavra(strTexto, posicao);
            insere_ArvTrie(palavra, arvoresTrie[i]);

            palavra = cria_Palavra(strTexto, posicao);
            insere_Hash(palavra, tabelas[i]);
        }

        for (int i = 0; i < nBuscas; i++)
        {
            /* Carregando o vetor com palavras aleatórias da listas[i] */
            strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
        }

        printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
        printf("\n\n\nARVORE BINARIA (em ordem)\n\n\n");
        imprime_em_ordem_ArvBin(arvoresBin[i]);
        printf("\n\n\nARVORE AVL (em ordem)\n\n\n");
        imprime_em_ordem_ArvAVL(arvoresAVL[i]);
        printf("\n\n\nLISTA ENCADEADA\n\n\n");
        imprime_Lista(listas[i]);
        printf("\n\n\nTABELA HASH COM AVL (em ordem)\n\n\n");
        imprime_Hash(tabelas[i]);
        printf("\n\n\nTRIE\n\n\n");
        imprime_ArvTrie(arvoresTrie[i]);
        for (int i = 0; i < nBuscas; i++)
        {
            Palavra *palavraLista = busca_Lista(vetBusca[i], listas[i]);
            Palavra *palavraArvore = busca_ArvBin(arvoresBin[i], vetBusca[i]);
            Palavra *palavraAVL = busca_ArvAVL(arvoresAVL[i], vetBusca[i]);
            Palavra *palavraTrie = busca_ArvTrie(arvoresTrie[i], vetBusca[i]);
            Palavra *palavraHash = busca_Hash(vetBusca[i], tabelas[i]);

            if (palavraLista != NULL)
            {
                printf("A palavra %s foi encontrada na listas[i].\n", vetBusca[i]);
            }
            if (palavraArvore != NULL)
            {
                printf("A palavra %s foi encontrada na arvore.\n", vetBusca[i]);
            }
            if (palavraAVL != NULL)
            {
                printf("A palavra %s foi encontrada na arvore AVL.\n", vetBusca[i]);
            }

            if (palavraTrie != NULL)
            {
                printf("A palavra %s foi encontrada na arvore trie.\n", vetBusca[i]);
            }

            if (palavraHash != NULL)
            {
                printf("A palavra %s foi encontrada na tabelas[i] hash.\n", vetBusca[i]);
            }
        }

        printf("\nFim da leitura. Liberando estruturas...\n");
        libera_RandPal(palavrasAleatorias);
        fclose(fs);
        libera_Lista(listas[i]);
        libera_ArvBin(arvoresBin[i]);
        libera_ArvAVL(arvoresAVL[i]);
        libera_ArvTrie(arvoresTrie[i]);
        libera_Hash(tabelas[i]);
        printf("Estruturas liberadas com sucesso. Talvez. hehe\n");
    }





    /*
    char stringBuscada[TAM_STRING];
    printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
    scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

    Palavra *palavraLista = busca_Lista(stringBuscada, listas[i]);
    Palavra *palavraArvore = busca_ArvBin(arvoresBin[i], stringBuscada);
    Palavra *palavraAVL = busca_ArvAVL(arvoresAVL[i], stringBuscada);
    Palavra *palavraTrie = busca_ArvTrie(arvoresTrie[i], stringBuscada);
    Palavra *palavraHash = busca_Hash(stringBuscada, tabelas[i]);

    if (palavraLista != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na listas[i].\n", stringBuscada);
        imprime_Palavra(palavraLista);
    }
    else
    {
        printf("A palavra nao foi encontrada na listas[i].\n");
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

    if (palavraTrie != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na arvore trie.\n", stringBuscada);
        imprime_Palavra(palavraTrie);
    }
    else
    {
        printf("A palavra nao foi encontrada na arvore trie.\n");
    }

    if (palavraHash != NULL)
    {
        printf("A palavra \"%s\" foi encontrada na tabelas[i] hash.\n", stringBuscada);
        imprime_Palavra(palavraHash);
    }
    else
    {
        printf("A palavra nao foi encontrada na hash.\n");
    }
    */

    return 0;
}
