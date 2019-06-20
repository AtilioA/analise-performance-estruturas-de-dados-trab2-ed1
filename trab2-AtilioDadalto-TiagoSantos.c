#include "include/ListaEncadeada.h"
#include "include/ArvoreBinaria.h"
#include "include/Indexador.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * CONVENÇÕES PARA O TRABALINDO:
 * Constantes em CAPS: UNUSED, TRUE, FALSE.
 * Structs e typedefs em CamelCase: ArvBin, Lista.
 * Funções em snake_case: pre_ordem_ArvBin(), insere_lista().
 * Ponteiros com asterisco do lado do nome da variável: ArvBin *foo, int *bar.
 */

int main()
{
    clrscr();

    Lista *lista = cria_Lista();

    printf("Boa noite. Esta quase funcionando.\n");

    Palavra *palavra1 = cria_Palavra("sim");
    Palavra *palavra2 = cria_Palavra("sim");
    insere_Lista(palavra1, lista);
    insere_Lista(palavra1, lista);
    insere_Lista(palavra2, lista);
    insere_Lista(palavra2, lista);
    insere_Lista(palavra2, lista);
    insere_Lista(palavra2, lista);
    insere_Lista(palavra2, lista);
    insere_Lista(palavra2, lista);
    imprime_lista(lista);

    destroi_Lista(lista);
    destroi_Palavra(palavra1);
    destroi_Palavra(palavra2);
    destroi_Lista(lista);

    return 0;
}
