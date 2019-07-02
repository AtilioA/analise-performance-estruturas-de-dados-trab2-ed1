/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD árvore binária balanceada para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __ARVORE_AVL_H
#define __ARVORE_AVL_H

#include "arvore_binaria.h"

typedef struct No *ArvAVL;

ArvAVL *cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, Palavra *pal);
int esta_vazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int total_No_ArvAVL(ArvAVL *raiz);
Palavra *busca_ArvAVL(ArvAVL *raiz, char *strat);
void imprime_pre_ordem_ArvAVL(ArvAVL *raiz);
void imprime_em_ordem_ArvAVL(ArvAVL *raiz);
void imprime_pos_ordem_ArvAVL(ArvAVL *raiz);

#endif
