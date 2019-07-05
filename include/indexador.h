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
} CelulaOcorr;

typedef struct ocorrencias
{
    CelulaOcorr *primeiro;
    CelulaOcorr *ultimo;
    int qtd;
} ListaOcorr;

// Lista encadeada para pesquisar palavras aleatoriamente (?)
typedef struct celula_pal_rand
{
    char *string;
    struct pal_rand *prox;
} CelulaRandPal;

typedef struct sent_pal_rand
{
    CelulaRandPal *primeiro;
    CelulaRandPal *ultimo;
    int qtd;
} SentRandPal;

/* Estrutura de dados para guardar nomes de arquivos e ocorrências de palavras nestes arquivos */
typedef struct Arq
{
    char *nomeArquivo;
    ListaOcorr *ocorrencias;
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

/*
char *get_string(Palavra *palavra);

int get_ocorrencias(Palavra *palavra);
*/
ListaOcorr *get_posicoes(Palavra *palavra);

ListaOcorr *nova_Ocorre();

void insere_Ocorrencias(ListaOcorr *l, int ocorre);

void imprime_Palavra(Palavra *palavra);

Palavra *cria_Palavra(char *nomeArquivo, char *string, int ocorre);

void imprime_vet_h(int *vet, int tamVet);

// Libera os elementos de uma palavra
void libera_Palavra(Palavra *palavra);

SentRandPal *cria_RandPal();

void insere_RandPal(char *strat, SentRandPal *l);

char *busca_RandPal(int indice, SentRandPal *l);

void libera_RandPal(SentRandPal *l);

/* Limpa a tela do terminal */
void clr_scr();

#endif
