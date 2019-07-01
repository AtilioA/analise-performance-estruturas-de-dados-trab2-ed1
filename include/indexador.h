// Guard para evitar dupla inclusão
#ifndef __INDEXADOR_H
#define __INDEXADOR_H

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

typedef struct Palavra
{
    char *string;
    ListaOcorr *ocorrencias;
} Palavra;

// pra pesquisar aleatoriamente
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

char *get_string(Palavra *palavra);

int get_ocorrencias(Palavra *palavra);

ListaOcorr *get_posicoes(Palavra *palavra);

ListaOcorr *nova_Ocorre();

void insere_Ocorrencias(ListaOcorr *l, int ocorre);

void imprime_Palavra(Palavra *palavra);

Palavra *cria_Palavra(char *string, int ocorre);

//Palavra *inicia_Palavra();
void imprime_vet_h(int *vet, int tamVet);

// Libera os elementos de uma palavra
void destroi_Palavra(Palavra *palavra);

/* Limpa a tela do terminal */
void clr_scr();

SentRandPal *cria_RandPal();

void insere_RandPal(char *strat, SentRandPal *l);

char *busca_RandPal(int indice, SentRandPal *l);

void destroi_RandPal(SentRandPal *l);

#endif
