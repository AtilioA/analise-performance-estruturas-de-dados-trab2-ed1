#include "include/ListaEncadeada.h"
#include "include/ArvoreBinaria.h"
#include "include/Indexador.h"
#include <stdlib.h>

int main()
{
    clrscr();

    tLista *lista = Cria_Lista();

    printf("Boa noite. Nao esta funcionando.\n");

    tPalavra *palavra1 = criaPalavra("sim");
    ImprimePalavra(palavra1);
    Insere_Lista(palavra1, lista);
    Insere_Lista(palavra1, lista);
    Insere_Lista(palavra1, lista);

    ImprimeLista(lista);

    DestroiLista(lista);

    free(lista);
    return 0;
}
