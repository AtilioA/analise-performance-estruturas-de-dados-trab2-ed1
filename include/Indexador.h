// Guard para evitar dupla inclusão
#ifndef __INDEXADOR_H
#define __INDEXADOR_H

typedef struct Palavra
{
    char *string;
    int ocorrencias;
    int *posicoes;
} Palavra;

char *get_string(Palavra *palavra);

int get_ocorrencias(Palavra *palavra);

int *get_posicoes(Palavra *palavra);

void imprimePalavra(Palavra *palavra);
Palavra *cria_Palavra(char *string);
Palavra *inicia_Palavra();
void imprime_vet_h(int *vet, int tamVet);

// Libera os elementos de uma palavra
void destroi_Palavra(Palavra *palavra);

/* Limpa a tela do terminal */
void clr_scr();

#endif
