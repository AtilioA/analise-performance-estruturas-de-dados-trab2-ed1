#include "include/lista_encadeada.h"
#include "include/arvore_binaria.h"
#include "include/indexador.h"
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
    clr_scr();

    Lista *lista = cria_Lista();

    printf("Boa noite. Esta quase funcionando.\n");

    Palavra *palavra1 = cria_Palavra("sim", 2);
    insere_Lista(palavra1, lista);
    palavra1 = cria_Palavra("sim", 4);
    insere_Lista(palavra1, lista);
    palavra1 = cria_Palavra("não", 3);
    insere_Lista(palavra1, lista);
    palavra1 = cria_Palavra("sim", 7);
    insere_Lista(palavra1, lista);
    imprime_lista(lista);
/*
    destroi_Palavra(palavra1);
    destroi_Palavra(palavra2);
    destroi_Lista(lista);
*/
    return 0;
}
