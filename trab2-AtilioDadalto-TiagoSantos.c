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

    //Lista *lista = cria_Lista();
    ArvBin *arvere = criaArvBin();
    tSentRandPal *pal_al = newRandpal(); //lista de busca
    Palavra *pal;
    char strat[80];
    int kkkeae;
    FILE *f = fopen(argv[1], "r");
    int k = atoi(argv[2]);
    char vet[k][80]; //vetor de busca
    srand(time(NULL));
    while(!feof(f)){
        fscanf(f, "%s", strat); // vo usar o fscanf de placeholder até a gnt fazer uma função de leitura de palavras descente
        insereRandPal(strat, pal_al);
        kkkeae = ftell(f) - strlen(strat) + 1;
        pal = cria_Palavra(strat, kkkeae);
        insere_ArvBin(arvere, pal);
        //insere_Lista(pal, lista);
    }
    for(int i = 0; i < k; i++){
        strcpy(vet[i], buscaRandPal(rand()%(pal_al->qtd), pal_al)); //carrega o vetor com palavras aleatórias da lista
    }
    em_ordem_ArvBin(arvere);
    //imprime_lista(lista);
    for(int i = 0; i < k; i++){
        //Palavra* meu = busca_Lista(vet[i], lista);
        Palavra *meu = consulta_ArvBin(arvere, vet[i]);
        if(meu != NULL){
            printf("A palavra %s foi encontrada\n", vet[i]);
        }
    }
    printf("\n");
    destroiRandPal(pal_al);
    //imprime_lista(lista);
    fclose(f);
    libera_ArvBin(arvere);
    //destroi_lista(lista);
    return 0;
}
