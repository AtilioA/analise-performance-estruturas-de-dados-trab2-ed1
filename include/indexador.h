// Guard para evitar dupla inclusão
#ifndef __INDEXADOR_H
#define __INDEXADOR_H

typedef struct ocorre{
    int ocorreu;
    struct ocorre *prox;
} tOcorre;

typedef struct ocorrencias{
    tOcorre *primeiro;
    tOcorre *ultimo;
    int qtd;
} ListaOcorrencias;


typedef struct Palavra
{
    char *string;
    ListaOcorrencias *ocorrencias;
} Palavra;

// pra pesquisar aleatoriamente
typedef struct pal_rand{
    char *string;
    struct pal_rand *prox;
} tRandPal;

typedef struct set_pal_rand{
    tRandPal *primeiro;
    tRandPal *ultimo;
    int qtd;
} tSentRandPal;

char *get_string(Palavra *palavra);

int get_ocorrencias(Palavra *palavra);

ListaOcorrencias *get_posicoes(Palavra *palavra);

ListaOcorrencias *novaOcorre();

void insereOcorre(ListaOcorrencias *l, int ocorre);

void imprime_Palavra(Palavra *palavra);

Palavra *cria_Palavra(char *string, int ocorre);

//Palavra *inicia_Palavra();
void imprime_vet_h(int *vet, int tamVet);

// Libera os elementos de uma palavra
void destroi_Palavra(Palavra *palavra);

/* Limpa a tela do terminal */
void clr_scr();

tSentRandPal *newRandpal();

void insereRandPal(char *strat, tSentRandPal *l);

char *buscaRandPal(int indice, tSentRandPal *l);

void destroiRandPal(tSentRandPal* l);

#endif
