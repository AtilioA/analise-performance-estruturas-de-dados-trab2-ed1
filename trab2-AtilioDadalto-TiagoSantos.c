#include "include/ListaEncadeada.h"
#include "include/ArvoreBinaria.h"
#include "include/Indexador.h"
#include <stdlib.h>

int main()
{
    clrscr();

    tLista lista;
    FMVazio(&lista);

    printf("Boa noite. Nao esta funcionando.\n");

    tPalavra *palavra1 = criaPalavra("sim");
    ImprimePalavra(palavra1);
    Insere(palavra1, &lista);
    Insere(palavra1, &lista);
    Insere(palavra1, &lista);

    ImprimeLista(&lista);

    DestroiLista(&lista);

    return 0;
}
