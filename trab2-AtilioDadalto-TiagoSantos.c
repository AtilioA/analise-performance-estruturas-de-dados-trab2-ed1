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
#define EXCETO_LISTA 7

void AvaliaDesempenho(int n, int estrutura, int argc, char *argv[])
{
    printf("Iniciando indexador...\n");
    clock_t t;                 // Para estimar tempo de execução
    struct timeval time;       // Para gerar semente do srand
    char strTexto[TAM_STRING]; // Vetor para armazenamento temporário de strings do texto
    int nArquivos = argc - 2, posicao = 0, i = 0;
    Palavra *palavraAleatoria;

    char vetBusca[n][TAM_STRING]; // Vetor para busca de palavras
    FILE *fs;
    ListaRandPal *palavrasAleatorias = cria_RandPal(); // Lista para busca de palavras
    Palavra *palavraInserida;
    printf("Lista de busca de palavras criada com sucesso.\n");

    gettimeofday(&time, NULL); // Para gerar semente do srand
    srand((unsigned int)time.tv_usec);

    printf("AVALIA DESEMPENHO\n");
    if (estrutura == LISTA || estrutura == TODAS)
    {
        printf("AVALIA DESEMPENHO LISTA\n");
        // sleep(1);
        t = clock();
        Lista *lista;
        lista = cria_Lista();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            if (fs == NULL) // se não conseguir ler o arquivo, fs será NULL
            {
                libera_Lista(lista);
                libera_RandPal(palavrasAleatorias);
                printf("\nERRO NA ABERTURA DE ARQUIVO (ARQUIVO PROVAVELMENTE NAO EXISTE)\n");
                printf("LIBERANDO ESTRUTURAS E ENCERRANDO EXECUCAO DO PROGRAMA.\n");
                exit(1);
            }
            if (fs != NULL)
            {
                printf("%io arquivo aberto com sucesso.\n", i + 1);

                printf("Lendo %io arquivo...\n", i + 1);
                while (!feof(fs))
                {
                    posicao = le_palavra(fs, strTexto);

                    // Preenchendo lista de palavras aleatórias
                    insere_RandPal(strTexto, palavrasAleatorias);

                    // Preenchendo estruturas de dados do projeto
                    palavraInserida = cria_Palavra(argv[i + 2], strTexto, posicao);
                    insere_Lista(palavraInserida, lista);
                }
                printf("%io arquivo lido.\n", i + 1);
            }
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
                printf("PALAVRA ENCONTRADA.\n");
                imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            printf("\n");
        }
        t = clock() - t;
        double tempoBuscaLista = ((double)t) / CLOCKS_PER_SEC; // in seconds

        /*
        if (estrutura < 6)
        {
            char stringBuscada[TAM_STRING];
            printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
            scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

            t = clock();
            Palavra *palavraUsuario = busca_Lista(stringBuscada, lista);
            if (palavraUsuario != NULL)
            {
                printf("A palavra \"%s\" foi encontrada na lista encadeada.\n", stringBuscada);
                imprime_Palavra(palavraUsuario);
            }
            else
            {
                printf("A palavra nao foi encontrada na lista encadeada.\n");
            }
            t = clock() - t;
            double tempoBuscaUsuarioLista = ((double)t) / CLOCKS_PER_SEC; // in seconds

            printf("TEMPO DE BUSCA USUARIO LISTA ENCADEADA: %f\n", tempoBuscaUsuarioLista);
        }
        */

        printf("TEMPO DE INSERCAO LISTA ENCADEADA: %f\n", tempoInsercaoLista);
        printf("TEMPO DE BUSCA LISTA ENCADEADA: %f\n\n", tempoBuscaLista);

        libera_Lista(lista);
    }
    if (estrutura == ARVORE || estrutura >= TODAS)
    {
        printf("AVALIA DESEMPENHO ARVORE\n");
        // sleep(1);
        t = clock();
        ArvBin *arvore;
        arvore = cria_ArvBin();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            if (fs == NULL) // se não conseguir ler o arquivo, fs será NULL
            {
                libera_ArvBin(arvore);
                libera_RandPal(palavrasAleatorias);
                printf("\nERRO NA ABERTURA DE ARQUIVO (ARQUIVO PROVAVELMENTE NAO EXISTE)\n");
                printf("LIBERANDO ESTRUTURAS E ENCERRANDO EXECUCAO DO PROGRAMA.\n");
                exit(1);
            }

            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo arvore de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavraInserida = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_ArvBin(arvore, palavraInserida);
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
                printf("PALAVRA ENCONTRADA.\n");
                imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            printf("\n");
        }
        t = clock() - t;
        double tempoBuscaArvore = ((double)t) / CLOCKS_PER_SEC; // in seconds

        /*
        if (estrutura < 6)
        {
            char stringBuscada[TAM_STRING];
            printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
            scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

            t = clock();
            Palavra *palavraUsuario = busca_ArvBin(arvore, stringBuscada);
            if (palavraUsuario != NULL)
            {
                printf("A palavra \"%s\" foi encontrada na arvore binaria.\n", stringBuscada);
                imprime_Palavra(palavraUsuario);
            }
            else
            {
                printf("A palavra nao foi encontrada na arvore binaria.\n");
            }
            t = clock() - t;
            double tempoBuscaUsuarioArvore = ((double)t) / CLOCKS_PER_SEC; // in seconds

            printf("TEMPO DE BUSCA USUARIO ARVORE BINARIA: %f\n", tempoBuscaUsuarioArvore);
        }
        */

        printf("TEMPO DE INSERCAO ARVORE BINARIA: %f\n", tempoInsercaoArvore);
        printf("TEMPO DE BUSCA ARVORE BINARIA: %f\n\n", tempoBuscaArvore);

        libera_ArvBin(arvore);
    }
    if (estrutura == AVL || estrutura >= TODAS)
    {
        printf("AVALIA DESEMPENHO ARVORE AVL\n");
        // sleep(1);
        t = clock();
        ArvAVL *avl;
        avl = cria_ArvAVL();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            if (fs == NULL) // se não conseguir ler o arquivo, fs será NULL
            {
                libera_ArvAVL(avl);
                libera_RandPal(palavrasAleatorias);
                printf("\nERRO NA ABERTURA DE ARQUIVO (ARQUIVO PROVAVELMENTE NAO EXISTE)\n");
                printf("LIBERANDO ESTRUTURAS E ENCERRANDO EXECUCAO DO PROGRAMA.\n");
                exit(1);
            }
            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo avl de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavraInserida = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_ArvAVL(avl, palavraInserida);
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
                printf("PALAVRA ENCONTRADA.\n");
                imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            printf("\n");
        }
        t = clock() - t;
        double tempoBuscaAVL = ((double)t) / CLOCKS_PER_SEC; // in seconds

        /*
        if (estrutura < 6)
        {
            char stringBuscada[TAM_STRING];
            printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
            scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

            t = clock();
            Palavra *palavraUsuario = busca_ArvAVL(avl, stringBuscada);
            if (palavraUsuario != NULL)
            {
                printf("A palavra \"%s\" foi encontrada na arvore AVL.\n", stringBuscada);
                imprime_Palavra(palavraUsuario);
            }
            else
            {
                printf("A palavra nao foi encontrada na arvore AVL.\n");
            }
            t = clock() - t;
            double tempoBuscaUsuarioAVL = ((double)t) / CLOCKS_PER_SEC; // in seconds

            printf("TEMPO DE BUSCA USUARIO ARVORE AVL: %f\n", tempoBuscaUsuarioAVL);
        }

*/
        printf("TEMPO DE INSERCAO ARVORE AVL: %f\n", tempoInsercaoAVL);
        printf("TEMPO DE BUSCA ARVORE AVL: %f\n\n", tempoBuscaAVL);

        libera_ArvAVL(avl);
    }
    if (estrutura == TRIE || estrutura >= TODAS)
    {
        printf("AVALIA DESEMPENHO ARVORE TRIE\n");
        // sleep(1);
        t = clock();
        ArvTrie *trie;
        trie = cria_ArvTrie();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            if (fs == NULL) // se não conseguir ler o arquivo, fs será NULL
            {
                libera_ArvTrie(trie);
                libera_RandPal(palavrasAleatorias);
                printf("\nERRO NA ABERTURA DE ARQUIVO (ARQUIVO PROVAVELMENTE NAO EXISTE)\n");
                printf("LIBERANDO ESTRUTURAS E ENCERRANDO EXECUCAO DO PROGRAMA.\n");
                exit(1);
            }
            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo trie de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavraInserida = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_ArvTrie(palavraInserida, trie);
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
                printf("PALAVRA ENCONTRADA.\n");
                imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            printf("\n");
        }
        t = clock() - t;
        double tempoBuscaTrie = ((double)t) / CLOCKS_PER_SEC; // in seconds

        /*
        if (estrutura < 6)
        {
            char stringBuscada[TAM_STRING];
            printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
            scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

            t = clock();
            Palavra *palavraUsuario = busca_ArvTrie(trie, stringBuscada);
            if (palavraUsuario != NULL)
            {
                printf("A palavra \"%s\" foi encontrada na arvore trie.\n", stringBuscada);
                imprime_Palavra(palavraUsuario);
            }
            else
            {
                printf("A palavra nao foi encontrada na arvore trie.\n");
            }
            t = clock() - t;
            double tempoBuscaUsuarioTrie = ((double)t) / CLOCKS_PER_SEC; // in seconds

            printf("TEMPO DE BUSCA USUARIO ARVORE TRIE: %f\n", tempoBuscaUsuarioTrie);
        }

*/
        printf("TEMPO DE INSERCAO ARVORE TRIE: %f\n", tempoInsercaoTrie);
        printf("TEMPO DE BUSCA ARVORE TRIE: %f\n\n", tempoBuscaTrie);
        libera_ArvTrie(trie);
    }
    if (estrutura == HASH || estrutura >= TODAS)
    {
        printf("AVALIA DESEMPENHO TABELA HASH\n");
        t = clock();
        TabelaHash *tabela;
        tabela = cria_Hash();
        printf("\nEstrutura criada com sucesso.\n");
        for (i = 0; i < nArquivos; i++) // 0 até agrc - 2
        {
            fs = le_arquivo(argv[i + 2]); // se não conseguir ler algum, liberar estrutura
            if (fs == NULL) // se não conseguir ler o arquivo, fs será NULL
            {
                libera_Hash(tabela);
                libera_RandPal(palavrasAleatorias);
                printf("\nERRO NA ABERTURA DE ARQUIVO (ARQUIVO PROVAVELMENTE NAO EXISTE)\n");
                printf("LIBERANDO ESTRUTURAS E ENCERRANDO EXECUCAO DO PROGRAMA.\n");
                exit(1);
            }
            printf("%io arquivo aberto com sucesso.\n", i + 1);

            printf("Lendo %io arquivo...\n", i + 1);
            while (!feof(fs))
            {
                posicao = le_palavra(fs, strTexto);

                // Preenchendo tabela de palavras aleatórias
                insere_RandPal(strTexto, palavrasAleatorias);

                // Preenchendo estruturas de dados do projeto
                palavraInserida = cria_Palavra(argv[i + 2], strTexto, posicao);
                insere_Hash(palavraInserida, tabela);
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
                printf("PALAVRA ENCONTRADA.\n");
                imprime_Palavra(palavraAleatoria);
            }
            else
            {
                printf("Palavra %s nao encontrada.\n", vetBusca[i]);
            }
            printf("\n");
        }

        t = clock() - t;
        double tempoBuscaHash = ((double)t) / CLOCKS_PER_SEC; // in seconds

        /*
        char stringBuscada[TAM_STRING];
        printf("\nDigite uma palavra para procurar no(s) arquivo(s): ");
        scanf("%79s", stringBuscada); // Lê no máximo TAM_STRING - 1

        t = clock();
        Palavra *palavraUsuario = busca_Hash(stringBuscada, tabela);
        if (palavraUsuario != NULL)
        {
            printf("A palavra \"%s\" foi encontrada na tabela hash.\n", stringBuscada);
            imprime_Palavra(palavraUsuario);
        }
        else
        {
            printf("A palavra nao foi encontrada na hash.\n");
        }
        t = clock() - t;
        double tempoBuscaUsuarioHash = ((double)t) / CLOCKS_PER_SEC; // in seconds
        printf("TEMPO DE BUSCA USUARIO TABELA HASH: %f\n", tempoBuscaUsuarioHash);
        */

        printf("TEMPO DE INSERCAO TABELA HASH: %f\n", tempoInsercaoHash);
        printf("TEMPO DE BUSCA TABELA HASH: %f\n\n", tempoBuscaHash);

        libera_Hash(tabela);
    }
    libera_RandPal(palavrasAleatorias);
}

void menu(int argc, char *argv[])
{
    clr_scr();
    /* inicialização do programa */
    int nArquivos = argc - 2;
    int nBuscasAleatorias = atoi(argv[1]);
    int i = 0, escolha = -1;

    printf("Arquivos passados como entrada:\n");
    for (i = 0; i < nArquivos; i++)
    {
        printf("%s\n", argv[i + 2]);
    }

    // while (escolhe != 0)
    {
        printf("OPCOES PARA INDEXACAO:\n");
        printf("1 - LISTA ENCADEADA\n");
        printf("2 - ÁRVORE BINÁRIA (NÃO BALANCEADA)\n");
        printf("3 - ÁRVORE AVL\n");
        printf("4 - ÁRVORE TRIE\n");
        printf("5 - TABELA HASH\n");
        printf("----------------------------------\n");
        printf("6 - INDEXAR EM TODAS AS ESTRUTURAS\n");
        printf("7 - INDEXAR EM TODAS AS ESTRUTURAS, EXCETO LISTA\n");
        printf("8 - MUDAR NUMERO DE BUSCAS\n");
        printf("0 - SAIR\n\n");
        printf("Informe a opcao:\n");
        while (escolha < 0 || escolha > 8)
        {
            scanf("%i", &escolha);
            while (getchar() != '\n'); // Validando entrada
        }
        printf("\n\n");

        switch (escolha)
        {
        case 0:
            break;
        case 1:
            AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            escolha = -1;
            break;

        case 2:
            AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            escolha = -1;
            break;

        case 3:
            AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            escolha = -1;
            break;

        case 4:
            AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            escolha = -1;
            break;

        case 5:
            AvaliaDesempenho(nBuscasAleatorias, escolha, argc, argv);
            escolha = -1;
            break;

        case 6:
            AvaliaDesempenho(nBuscasAleatorias, TODAS, argc, argv);
            escolha = -1;
            break;

        case 7:
            AvaliaDesempenho(nBuscasAleatorias, EXCETO_LISTA, argc, argv);
            escolha = -1;
            break;

        case 8:
            printf("Informe a nova quantidade de buscas aleatorias a serem realizadas:\n");
            scanf("%i", &nBuscasAleatorias);
            escolha = -1;
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            escolha = -1;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    /* Validação de argumentos de entrada */
    if (argv[1] == NULL)
    {
        printf("Entrada de buscas invalida.\n");
        exit(1);
    }

    if (atoi(argv[1]) < 0)
    {
        printf("Numero de buscas invalido.\n");
        exit(1);
    }

    menu(argc, argv);
    return 0;
}
