// Guard para evitar dupla inclusão
#ifndef __INDEXADOR_H
#define __INDEXADOR_H

typedef struct ocorre{
    int ocorreu;
    struct ocorre *prox;
}tOcorre;

typedef struct ocorrencias{
    tOcorre *prim;
    tOcorre *ult;
    int n;
}tOcorrencias;


typedef struct Palavra
{
    char *string;
    tOcorrencias *ocorrencias;
} Palavra;

// pra pesquisar aleatoriamente
typedef struct pal_rand{
    char *string;
    struct pal_rand *prox;
}tRandPal;

typedef struct set_pal_rand{
    tRandPal *prim;
    tRandPal *ult;
    int qtd;
}tSentRandPal;

char *get_string(Palavra *palavra);

int get_ocorrencias(Palavra *palavra);

tOcorrencias *get_posicoes(Palavra *palavra);

void imprimePalavra(Palavra *palavra);
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
