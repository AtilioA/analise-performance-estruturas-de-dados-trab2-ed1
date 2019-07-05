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

#define LISTA 1
#define ARVORE 2
#define AVL 3
#define TRIE 4
#define HASH 5
#define TODAS 6

void AvaliaDesempenho(int n, int estrutura, int argc, char *argv[])
{
    printf("Iniciando indexador...\n");
    clock_t t;                 // Para estimar tempo de execução
    struct timeval time;       // Para gerar semente do srand
    char strTexto[TAM_STRING]; // Vetor para armazenamento temporário de strings do texto
    int nArquivos = argc - 2, posicao = 0, i = 0;
    Palavra *palavraAleatoria, *palavraBusca;

    char vetBusca[n][TAM_STRING]; // Vetor para busca de palavras
    FILE *fs;
    SentRandPal *palavrasAleatorias = cria_RandPal(); // Lista para busca de palavras
    Palavra *palavra;
    printf("Lista de busca de palavras criada com sucesso.\n");

    gettimeofday(&time, NULL); // Para gerar semente do srand
    srand((unsigned int)time.tv_usec);

    printf("AVALIA DESEMPENHO\n");
    if (estrutura == LISTA)
    {
        printf("AVALIA DESEMPENHO LISTA\n");
        t = clock();
        Lista *lista;
        lista = cria_Lista();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            printf("%io arquivo aberto com sucesso.\n", i + 1);

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
            printf("%io arquivo lido.\n", i + 1);
            fclose(fs);
        }
        t = clock() - t;
        double tempoInsercaoLista = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("Preenchendo vetor de palavras aleatorias para busca...\n");
        for (i = 0; i < n; i++)
        {
            // Carregando o vetor com palavras aleatórias da lista
            strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
        }
        printf("Vetor de palavras aleatorias preenchido.\n");

        printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
        printf("\n\nLISTA ENCADEADA\n\n\n");
        // imprime_Lista(lista);

        printf("BUSCAS ALEATORIAS:\n");
        t = clock();
        for (int i = 0; i < n; i++)
        {
            palavraAleatoria = busca_Lista(vetBusca[i], lista);

            if (palavraAleatoria != NULL)
            {
                // printf("PALAVRA ENCONTRADA.\n");
                // imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            // printf("\n");
        }
        t = clock() - t;
        double tempoBuscaLista = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("\nTEMPO DE INSERCAO LISTA: %f\n", tempoInsercaoLista);
        printf("TEMPO DE BUSCA LISTA: %f\n\n", tempoBuscaLista);

        libera_Lista(lista);
    }
    else if (estrutura == ARVORE)
    {
        printf("AVALIA DESEMPENHO ARVORE\n");
        t = clock();
        ArvBin *arvore;
        arvore = cria_ArvBin();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo arvore de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavra = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_ArvBin(arvore, palavra);
            }
            printf("%io arquivo lido.\n", i + 1);
            fclose(fs);
        }
        t = clock() - t;
        double tempoInsercaoArvore = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("Preenchendo vetor de palavras aleatorias para busca...\n");
        for (i = 0; i < n; i++)
        {
            // Carregando o vetor com palavras aleatórias da arvore
            strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
        }
        printf("Vetor de palavras aleatorias preenchido.\n");

        printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
        printf("\n\nARVORE BINARIA\n\n\n");
        // imprime_em_ordem_ArvBin(arvore);

        printf("BUSCA ALEATORIA:\n");
        t = clock();
        for (int i = 0; i < n; i++)
        {
            palavraAleatoria = busca_ArvBin(arvore, vetBusca[i]);

            if (palavraAleatoria != NULL)
            {
                // printf("PALAVRA ENCONTRADA.\n");
                // imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            // printf("\n");
        }
        t = clock() - t;
        double tempoBuscaArvore = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("\nTEMPO DE INSERCAO ARVORE: %f\n", tempoInsercaoArvore);
        printf("TEMPO DE BUSCA ARVORE: %f\n\n", tempoBuscaArvore);

        libera_ArvBin(arvore);
    }
    else if (estrutura == AVL)
    {
        printf("AVALIA DESEMPENHO ARVORE AVL\n");
        t = clock();
        ArvAVL *avl;
        avl = cria_ArvAVL();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo avl de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavra = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_ArvAVL(avl, palavra);
            }
            printf("%io arquivo lido.\n", i + 1);
            fclose(fs);
        }
        t = clock() - t;
        double tempoInsercaoAVL = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("Preenchendo vetor de palavras aleatorias para busca...\n");
        for (i = 0; i < n; i++)
        {
            // Carregando o vetor com palavras aleatórias da avl
            strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
        }
        printf("Vetor de palavras aleatorias preenchido.\n");

        printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
        printf("\n\nARVORE AVL\n\n\n");
        // imprime_em_ordem_ArvAVL(avl);

        t = clock();
        printf("BUSCA ALEATORIA:\n");
        for (int i = 0; i < n; i++)
        {
            palavraAleatoria = busca_ArvAVL(avl, vetBusca[i]);

            if (palavraAleatoria != NULL)
            {
                // printf("PALAVRA ENCONTRADA.\n");
                // imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            // printf("\n");
        }
        t = clock() - t;
        double tempoBuscaAVL = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("\nTEMPO DE INSERCAO AVL: %f\n", tempoInsercaoAVL);
        printf("\nTEMPO DE BUSCA AVL: %f\n", tempoBuscaAVL);

        libera_ArvAVL(avl);
    }
    else if (estrutura == TRIE)
    {
        printf("AVALIA DESEMPENHO ARVORE TRIE\n");
        t = clock();
        ArvTrie *trie;
        trie = cria_ArvTrie();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo trie de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavra = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_ArvTrie(palavra, trie);
            }
            printf("%io arquivo lido.\n", i + 1);
            fclose(fs);
        }
        t = clock() - t;
        double tempoInsercaoTrie = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("Preenchendo vetor de palavras aleatorias para busca...\n");
        for (i = 0; i < n; i++)
        {
            // Carregando o vetor com palavras aleatórias da trie
            strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
        }
        printf("Vetor de palavras aleatorias preenchido.\n");

        printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
        printf("\n\nARVORE TRIE\n\n\n");
        // imprime_ArvTrie(trie);

        printf("BUSCA ALEATORIA:\n");
        t = clock();
        for (int i = 0; i < n; i++)
        {
            palavraAleatoria = busca_ArvTrie(trie, vetBusca[i]);

            if (palavraAleatoria != NULL)
            {
                // printf("PALAVRA ENCONTRADA.\n");
                // imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            // printf("\n");
        }
        t = clock() - t;
        double tempoBuscaTrie = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("TEMPO DE INSERCAO ARVORE TRIE: %f\n", tempoInsercaoTrie);
        printf("TEMPO DE BUSCA ARVORE TRIE: %f\n\n", tempoBuscaTrie);

        libera_ArvTrie(trie);
    }
    else if (estrutura == HASH)
    {
        printf("AVALIA DESEMPENHO TABELA HASH\n");
        t = clock();
        TabelaHash *tabela;
        tabela = cria_Hash();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo tabela de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavra = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_Hash(palavra, tabela);
            }
            printf("%io arquivo lido.\n", i + 1);
            fclose(fs);
        }
        t = clock() - t;
        double tempoInsercaoHash = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("Preenchendo vetor de palavras aleatorias para busca...\n");
        for (i = 0; i < n; i++)
        {
            // Carregando o vetor com palavras aleatórias da tabela
            strcpy(vetBusca[i], busca_RandPal(rand() % (palavrasAleatorias->qtd), palavrasAleatorias));
        }
        printf("Vetor de palavras aleatorias preenchido.\n");

        printf("\n\nLEITURA CONCLUIDA! IMPRIMINDO RESULTADOS:");
        printf("\n\nTABELA HASH\n\n\n");
        // imprime_Hash(tabela);

        printf("BUSCA ALEATORIA:\n");
        t = clock();
        for (int i = 0; i < n; i++)
        {
            palavraAleatoria = busca_Hash(vetBusca[i], tabela);

            if (palavraAleatoria != NULL)
            {
                // printf("PALAVRA ENCONTRADA.\n");
                // imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            // printf("\n");
        }
        t = clock() - t;
        double tempoBuscaHash = ((double)t) / CLOCKS_PER_SEC; // in seconds

        printf("TEMPO DE INSERCAO TABELA HASH: %f\n", tempoInsercaoHash);
        printf("TEMPO DE BUSCA TABELA HASH: %f\n\n", tempoBuscaHash);

        libera_Hash(tabela);
    }

    libera_RandPal(palavrasAleatorias);
}

void menu(int argc, char *argv[])
{
    /* inicialização do programa */
    int listaInserida = 0, arvoreBinariaInserida = 0, arvoreAVLInserida = 0,
        arvoreTrieInserida = 0, hashInserida = 0;
    int nArquivos = argc - 2;
    int nBuscasAleatorias = atoi(argv[1]);
    int i = 0, escolha = -1;

    printf("Arquivos passados como entrada:\n");
    for (i = 0; i < nArquivos; i++)
    {
        printf("%s\n", argv[i + 2]);
    }
    printf("Informe a quantidade de buscas aleatorias a serem realizadas:\n");
    // scanf("%i", &nBuscasAleatorias);

    while (escolha != 0 && (listaInserida != 1 && arvoreBinariaInserida != 1 && arvoreAVLInserida != 1 && arvoreTrieInserida != 1 && hashInserida != 1))
    {
        printf("Informe em qual estrutura deseja indexar os arquivos:\n");
        printf("1 - LISTA ENCADEADA\n");
        printf("2 - ÁRVORE BINÁRIA (NÃO BALANCEADA)\n");
        printf("3 - ÁRVORE AVL\n");
        printf("4 - ÁRVORE TRIE\n");
        printf("5 - TABELA HASH\n");
        printf("\n6 - INDEXAR EM TODAS AS ESTRUTURAS\n");
        while (escolha < 0 || escolha > 6)
        {
            scanf("%i", &escolha);
            while (getchar() != '\n');
        }
        printf("\n\n");

        switch (escolha)
        {
        case 0:
            break;
        case 1:
            if (listaInserida == 0)
            {
                listaInserida = 1;
                AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            }
            else
            {
                printf("\nArquivos ja indexados na lista.\n\n");
            }
            break;

        case 2:
            if (arvoreBinariaInserida == 0)
            {
                arvoreBinariaInserida = 1;
                AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
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
                AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
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
                AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
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
                AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            }
            else
            {
                printf("\nArquivos ja indexados na tabela hash.\n\n");
            }
            break;

        case 6:
            if (listaInserida == 0)
            {
                listaInserida = 1;
                AvaliaDesempenho(nBuscasAleatorias, 1, argc, argv);
            }
            if (arvoreBinariaInserida == 0)
            {
                arvoreBinariaInserida = 1;
                AvaliaDesempenho(nBuscasAleatorias, 2, argc, argv);
            }
            if (arvoreAVLInserida == 0)
            {
                arvoreAVLInserida = 1;
                AvaliaDesempenho(nBuscasAleatorias, 3, argc, argv);
            }
            if (arvoreTrieInserida == 0)
            {
                arvoreTrieInserida = 1;
                AvaliaDesempenho(nBuscasAleatorias, 4, argc, argv);
            }
            if (hashInserida == 0)
            {
                hashInserida = 1;
                AvaliaDesempenho(nBuscasAleatorias, 5, argc, argv);
            }
            printf("Todas as estruturas indexaram arquivos. Fim do programa.\n");
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
    return 0;
}
