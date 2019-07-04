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

    USUÁRIO: a
    PROGRAMA: INICIALIZA TUDO QUE TIVER QUE INICIALIZAR ANTES DE INSERÇÃO, CHECA ARGV, ETC


    PEDE NÚMERO DE BUSCAS ATÉ USUÁRIO ARREGAR
    LIBERA TUDO

*/

/*
void AvaliaDesempenho(int n, int estrutura, int argc, char *argv)
{
    struct timeval t;          // Para gerar semente do srand
    char strTexto[TAM_STRING]; // Vetor para armazenamento temporário de strings do texto
    int nArquivos = argc - 2, posicao = 0, i = 0;
    Palavra *palavraAleatoria, *palavraBusca;


    char vetBusca[n][TAM_STRING]; // Vetor para busca de palavras
    FILE *fs;
    Lista *lista;
    SentRandPal *palavrasAleatorias = cria_RandPal(); // Lista para busca de palavras
    Palavra *palavra;
    printf("Lista de busca de palavras criada com sucesso.\n");

    gettimeofday(&t, NULL); // Para gerar semente do srand
    srand((unsigned int)t.tv_usec);

    printf("Criando estruturas...\n");

    lista = cria_Lista();
    for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
    {
        fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
        printf("%io arquivo aberto com sucesso.\n", i + 1);
        printf("%ia estrutura criada com sucesso.\n", i + 1);

        printf("Lendo %io arquivo...\n", i + 1);
        while (!feof(fs))
        {
            posicao = le_palavra(fs, strTexto);

            // Preenchendo lista de palavras aleatórias
            insere_RandPal(strTexto, palavrasAleatorias);

            // Preenchendo estruturas de dados do projeto
            palavra = cria_Palavra(argv[i + 2], strTexto, posicao);
            insere_Lista(palavra, lista);
        }
        fclose(fs);
    }
    printf("\nEstruturas criadas com sucesso.\n");

    for (i = 0; i < n; i++)
    {
        // Carregando o vetor com palavras aleatórias da lista
        strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
    }


    printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");

    imprime_Lista(lista);

    printf("\n\n\nLISTA ENCADEADA\n\n\n");
    for (int i = 0; i < n; i++)
    {
        palavraAleatoria = busca_Lista(vetBusca[i], lista);

        if (palavraAleatoria != NULL)
        {
            printf("PALAVRA ENCONTRADA.\n");
            imprime_Palavra(palavraAleatoria);
        }
        else
        {
            printf("Palavra %s nao encontrada.\n", vetBusca[i]);
        }
        printf("\n");
    }
}
*/

void menu(int argc, char *argv[])
{
    /* inicialização do programa */
    int listaInserida = 0, arvoreInserida = 0, arvoreAVLInserida = 0,
        arvoreTrieInserida = 0, hashInserida = 0;
    int nArquivos = argc - 2;
    int nBuscasAleatorias = 0;
    int i = 0, escolha = -1;

    printf("Arquivos passados como entrada:\n");
    for (i = 0; i < nArquivos; i++)
    {
        printf("%s\n", argv[i + 2]);
    }
    printf("Informe a quantidade de buscas aleatorias a serem realizadas:\n");
    scanf("%i", &nBuscasAleatorias);

    while (escolha != 0)
    {
        printf("Informe em qual estrutura deseja indexar os arquivos:\n");
        printf("1 - LISTA ENCADEADA\n");
        printf("2 - ÁRVORE BINÁRIA (NÃO BALANCEADA)\n");
        printf("3 - ÁRVORE AVL\n");
        printf("4 - ÁRVORE TRIE\n");
        printf("5 - TABELA HASH\n");
        printf("0 - COMECAR BUSCAS\n");
        scanf("%i", &escolha);

        switch (escolha)
        {
        case 0:
            break;
        case 1:
            if (listaInserida == 0)
            {
                listaInserida = 1;
                // AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            }
            else
            {
                printf("\nArquivos ja indexados na lista.\n\n");
            }
                break;

        case 2:
            if (arvoreInserida == 0)
            {
                arvoreInserida = 1;
                // AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            }
            else
            {
                printf("\nArquivos ja indexados na arvore binaria.\n\n");
            }
            break;

        case 3:
            if (arvoreAVLInserida == 0)
            {
                arvoreAVLInserida = 1;
                // AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            }
            else
            {
                printf("\nArquivos ja indexados na arvore AVL.\n\n");
            }
            break;

        case 4:
            if (arvoreTrieInserida == 0)
            {
                arvoreTrieInserida = 1;
                // AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            }
            else
            {
                printf("\nArquivos ja indexados na arvore trie.\n\n");
            }
            break;

        case 5:
            if (hashInserida == 0)
            {
                hashInserida = 1;
                // AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            }
            else
            {
                printf("\nArquivos ja indexados na tabela hash.\n\n");
            }

            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;

        }
    }
}


int main(int argc, char *argv[])
{
    menu(argc, argv);
    printf("\n\n");
    return 0;
}
