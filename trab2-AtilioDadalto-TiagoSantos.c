#include "include/lista_encadeada.h"
#include "include/arvore_binaria.h"
#include "include/indexador.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
 * CONVENÇÕES PARA O TRABALINDO:
 * Constantes em CAPS: UNUSED, TRUE, FALSE.
 * Structs e typedefs em CamelCase: ArvBin, Lista.
 * Funções em snake_case: pre_ordem_ArvBin(), insere_lista().
 * Ponteiros com asterisco do lado do nome da variável: ArvBin *foo, int *bar.
 */

int main(int argc, char *argv[])
{
    clr_scr();

    Lista *lista = cria_Lista();
    Palavra *pal;
    char strat[80];
    int kkkeae;
    FILE *f = fopen(argv[1], "r");
    int k = atoi(argv[2]);
    char vet[k][80];
    printf("Boa noite. Esta quase funcionando.\n");
    srand(time(NULL));
    int pos = 0;
    while(!feof(f)){
        fscanf(f, "%s", strat);
        if(rand()%3 == 2 && pos < k){
            strcpy(vet[pos], strat);
            pos++;
        }
        kkkeae = ftell(f) - strlen(strat) + 1;
        pal = cria_Palavra(strat, kkkeae);
        insere_Lista(pal, lista);
    }
    printf("%s\n", vet[pos - 1]);
    imprime_lista(lista);
    for(int i = 0; i < k; i++){
        if(busca_Lista(vet[i], lista)){
            printf("A palavra %s foi encontrada\n", vet[i]);
        }
    }
    fclose(f);
    destroi_lista(lista);
    return 0;
}
