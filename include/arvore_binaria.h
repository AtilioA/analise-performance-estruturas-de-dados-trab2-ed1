/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD árvore binária para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __ARVORE_BINARIA_H
#define __ARVORE_BINARIA_H

#include "../include/indexador.h"

typedef struct No
{
    Palavra *palavra;
    struct No *esq;
    struct No *dir;
    int altura;
} No;

typedef struct No *ArvBin; // raiz

// Inicializa a árvore e deixa a raiz NULL, retornando a raiz alocada
ArvBin *cria_ArvBin();

// Insere uma Palavra na árvore, retornando 1 em caso de sucesso.
int insere_ArvBin(ArvBin *raiz, Palavra *palavra);

/*
Pesquisa uma string a partir da árvore raiz
retorna a Palavra se encontrar e NULL caso não encontre
*/
Palavra *busca_ArvBin(ArvBin *raiz, char *strat);

/** Imprime em-ordem */
void imprime_em_ordem_ArvBin(ArvBin *raiz);

// Libera a árvore binária da memória
// Libera um nó
void libera_No(struct No *no);
// Libera em pós-ordem
void libera_ArvBin(ArvBin *raiz);

#endif
