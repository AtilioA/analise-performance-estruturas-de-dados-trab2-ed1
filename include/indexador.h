/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD lista encadeada para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __INDEXADOR_H
#define __INDEXADOR_H

/* Lista encadeada para armazenar ocorrências */
typedef struct ocorre
{
    int ocorreu;
    struct ocorre *prox;
} CelulaOcorre;

typedef struct ocorrencias
{
    CelulaOcorre *primeiro;
    CelulaOcorre *ultimo;
    int qtd;
} ListaOcorre;

// Lista encadeada para pesquisar palavras aleatoriamente */
typedef struct CelulaRandPal
{
    char *string;
    struct CelulaRandPal *prox;
} CelulaRandPal;

typedef struct ListaRandPal
{
    CelulaRandPal *primeiro;
    CelulaRandPal *ultimo;
    int qtd;
} ListaRandPal;

/* Estrutura de dados para guardar nomes de arquivos e ocorrências de palavras nestes arquivos */
typedef struct Arq
{
    char *nomeArquivo;
    ListaOcorre *ocorrencias;
    struct Arq *prox;
} Arq;

typedef struct ListaArq
{
    Arq *primeiro;
    Arq *ultimo;
} ListaArq;

/* Estrutura de dados que abstrai uma palavra do texto */
typedef struct Palavra
{
    char *string;
    ListaArq *arquivos;
} Palavra;

// Retorna a string de uma palavra
char *get_string(Palavra *palavra);

// Retorna a lista de ocorrencias de uma palavra
ListaOcorre *get_posicoes(Palavra *palavra);

// Cria uma lista a string de uma palavra
ListaOcorre *nova_Ocorre();

// Insere uma ocorrência na lista de ocorrências
void insere_Ocorrencias(ListaOcorre *l, int ocorre);

// Imprime uma palavra
void imprime_Palavra(Palavra *palavra);

// Cria uma palavra dado uma string, arquivo de origem e sua primeira ocorrência
Palavra *cria_Palavra(char *nomeArquivo, char *string, int ocorre);

// Libera os elementos de uma palavra
void libera_Palavra(Palavra *palavra);

// Cria uma lista encadeada de palavras aleatórias
ListaRandPal *cria_RandPal();

// Insere uma palavra na lista encadeada de palavras aleatórias dada uma string
void insere_RandPal(char *strat, ListaRandPal *l);

// Busca uma palavra na lista encadeada de palavras aleatórias dado um índice
char *busca_RandPal(int indice, ListaRandPal *l);

// Libera a lista encadeada de palavras aleatórias
void libera_RandPal(ListaRandPal *l);

/* Limpa a tela do terminal */
void clr_scr();

#endif
