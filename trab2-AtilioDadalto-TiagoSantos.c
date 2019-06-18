#include "include/ListaEncadeada.h"
#include "include/ArvoreBinaria.h"
#include "include/Indexador.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    clrscr();

    tLista *lista = Cria_Lista();

    printf("Boa noite. Nao esta funcionando.\n");

    tPalavra *palavra1 = criaPalavra("sim");
    tPalavra *palavra2 = criaPalavra("sim");
    Insere_Lista(palavra1, lista);
    Insere_Lista(palavra1, lista);
    Insere_Lista(palavra2, lista);
    Insere_Lista(palavra2, lista);
    Insere_Lista(palavra2, lista);
    Insere_Lista(palavra2, lista);
    Insere_Lista(palavra2, lista);
    Insere_Lista(palavra2, lista);
    ImprimeLista(lista);

DestroiLista(lista);
DestroiPalavra(palavra1);
DestroiPalavra(palavra2);
DestroiLista(lista);
return 0;
}
