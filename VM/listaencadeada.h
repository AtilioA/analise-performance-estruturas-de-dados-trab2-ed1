#ifndef LISTAENC_H_
#define LISTAENC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  int codigo;
}Produto;


typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  Produto Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;


/* Faz a lista ficar vazia */
void FLVazia(TipoLista *Lista);

/*Verifica se a lista esta vazia*/
int Vazia(TipoLista Lista);

/* Insere x apos o ultimo elemento da lista */
void insere_Lista_antigo(Produto x, TipoLista *Lista);

/** Busca um produto pelo codigo - retornando a celula inteira*/
TipoApontador BuscaCodigo(int codigo, TipoLista *Lista);

/*Retira um elemento da lista */
void retira_Lista(int codigo, TipoLista *Lista, Produto *Item);


/*Imprime a lista */
void imprime_Lista(TipoLista Lista);

/*Quantidade de elementos na lista*/
int Quantidade(TipoLista Lista);

/**FUNCOES OPACAS DO STRUCT PRODUTO **/
Produto  criaProduto(int cod);

void ImprimeProduto(Produto p);

void libera_lista(TipoLista *Lista);


#endif /* LISTAENC_H_ */
