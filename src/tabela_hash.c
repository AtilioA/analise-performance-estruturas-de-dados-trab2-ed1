#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "../include/tabela_hash.h"

void cria_ListaHash(ListaHash *lista)
{
    lista->primeiro = (Celula *)malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
    // lista->primeiro->qtd = 0; to bugado com essa implementação do VM, vai ter que mudar a estrutura pq eu mudei e zoou a lógica

    lista->qtd = 0;
    lista->colisoes = 0;
}

short Vazia(ListaHash *lista)
{
    return (lista->primeiro == lista->ultimo);
}

void Ins(Palavra x, ListaHash *lista)
{
    lista->ultimo->prox = (Celula *)malloc(sizeof(Celula));
    // lista->ultimo->prox->qtd = 1; ?
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->palavra = &x;
    lista->ultimo->prox = NULL;
    lista->qtd++;
    if (lista->qtd > 1)
    {
        lista->colisoes++;
    }
}

void Ret(Celula *p, ListaHash *lista, Palavra *palavra)
{ /* -- Obs.: o item a ser retirado o seguinte ao apontado por p -- */
    Celula *q;
    if (Vazia(lista) || p == NULL || p->prox == NULL)
    {
        printf("Erro. Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p->prox;
    *palavra = *(q->palavra);
    p->prox = q->prox;
    if (p->prox == NULL)
        lista->ultimo = p;
    free(q);
    lista->qtd--;
    if (lista->qtd > 1)
    {
        lista->colisoes--;
    }
}

void GeraPesos(TipoPesos p)
{ /* Gera valores randomicos entre 1 e 10.000 */
    int i, j;
    struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    //gettimeofday(&semente, NULL);
    //srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    /* Usando semente fixa para garantir resultados iguais*/
    srand(1000);
    for (i = 0; i < N; i++)
        for (j = 0; j < TAMALFABETO; j++)
            p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

Indice h(TipoChave Chave, TipoPesos p)
{
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++)
        Soma += p[i][(unsigned int)Chave[i]];
    return (Soma % M);
}

void Inicializa(TipoDicionario T)
{
    int i;
    for (i = 0; i < M; i++)
        cria_ListaHash(&T[i]);
}

Celula *Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T)
{ // Obs.: Celula* de retorno aponta para o item anterior da lista
    Indice i;
    Celula *Ap;
    i = h(Ch, p);
    if (Vazia(&T[i]))
        return NULL; // Pesquisa sem sucesso
    else
    {
        Ap = T[i].primeiro;
        while (Ap->prox->prox != NULL &&
               strncmp(Ch, Ap->prox->palavra.string, sizeof(TipoChave)))
            Ap = Ap->prox;
        if (!strncmp(Ch, Ap->prox->palavra.string, sizeof(TipoChave)))
            return Ap;
        else
            return NULL; // Pesquisa sem sucesso
    }
}

void Insere(Palavra x, TipoPesos p, TipoDicionario T)
{
    Celula *aux = Pesquisa(x.string, p, T);
    if (aux == NULL)
    {
        Ins(x, &T[h(x.string, p)]);
    }
    else
    {
        aux->palavra->ocorrencias++;
        printf(" Registro ja  esta  presente\n");
    }
}

void Retira(Palavra x, TipoPesos p, TipoDicionario T)
{
    Celula *Ap;
    Ap = Pesquisa(x.string, p, T);
    if (Ap == NULL)
        printf(" Registro nao esta  presente\n");
    else
        Ret(Ap, &T[h(x.string, p)], &x);
}

void Imp(ListaHash lista)
{
    Celula *Aux;
    Aux = lista.primeiro->prox;
    while (Aux != NULL)
    {
        printf("%.*s %i ", N, Aux->palavra->string, Aux->palavra->ocorrencias);
        Aux = Aux->prox;
    }
}

void Imprime(TipoDicionario Tabela)
{
    int i;
    for (i = 0; i < M; i++)
    {
        printf("%d: ", i);
        if (!Vazia(&Tabela[i]))
            Imp(Tabela[i]);
        putchar('\n');
    }
}

int n_elementos(TipoDicionario tabela)
{
    int i = 0, qtd = 0;

    for (i = 0; i < M; i++)
    {
        qtd += tabela[i].qtd;
    }

    return qtd;
}

int n_colisoes(TipoDicionario tabela)
{
    int i = 0, colisoes = 0;

    for (i = 0; i < M; i++)
    {
        colisoes += tabela[i].colisoes;
    }

    return colisoes;
}

float carga_pesada(TipoDicionario tabela)
{
    int qtd = n_elementos(tabela);

    return (float)qtd / M;
}
