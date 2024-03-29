/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD árvore binária balanceada para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __ARVORE_AVL_H
#define __ARVORE_AVL_H

#include "arvore_binaria.h"

typedef struct No *ArvAVL; // raiz

// Inicializa uma árvore AVL
ArvAVL *cria_ArvAVL();

// Libera os elementos da árvore AVL
void libera_ArvAVL(ArvAVL *raiz);

// Retorna a altura de um nó da árvore
int altura_No(struct No *no);

// Calcula o fator de balanceamento de um nó
int fator_balanceamento_No(struct No *no);

/* Rotações na árvore binária:
 * LR = Left rotation
 * RL = Right rotation
 * LRR = Left-right rotation
 * RLR = Right-left rotation
 */
void rotacao_LR(ArvAVL *A);
void rotacao_RR(ArvAVL *A);
void rotacao_LRR(ArvAVL *A);
void rotacao_RLR(ArvAVL *A);

// Insere uma Palavra na árvore AVL
int insere_ArvAVL(ArvAVL *raiz, Palavra *palavra);

/* Busca na árvore AVL se existe um nó com a string de entrada,
 * retorna a Palavra do nó se for encontrada
 * NULL caso contrário
 */
Palavra *busca_ArvAVL(ArvAVL *raiz, char *stringBuscada);

// Imprime árvore AVL, pré-ordem
void imprime_pre_ordem_ArvAVL(ArvAVL *raiz);

// Imprime árvore AVL, em-ordem
void imprime_em_ordem_ArvAVL(ArvAVL *raiz);

#endif
