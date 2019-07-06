#! /bin/bash

tester(){
    # $1 = quantidade de busca
    # $2 = id da estrutura a ser testada
    # $3 = arquivos
    # $4 = numero de repetições
    COUNT=0
    INSERT_SUM=0
    SEARCH_SUM=0
    if [[ ! -e id_$2.csv ]]; then
        echo "QTD DE BUSCAS,ARQUIVOS,N DE REPETIÇÕES,TEMPO DE INSERÇÃO,TEMPO DE BUSCA,BUSCA/QTD DE BUSCAS" > id_$2.csv
    fi
    while [[ $COUNT -lt $4 ]]; do
        OUTPUT="$(echo $2 | ./indexador $1 $3)"
        T_INSERT=$(echo "$OUTPUT" | grep -w "TEMPO DE INSERCAO" | cut -d ":" -f2)
        T_SEARCH=$(echo "$OUTPUT" | grep -w "TEMPO DE BUSCA" | cut -d ":" -f2)
        INSERT_SUM=$(echo "$T_INSERT + $INSERT_SUM" | bc -l)
        SEARCH_SUM=$(echo "$T_SEARCH + $SEARCH_SUM" | bc -l)
        echo "RESULTADOS DA $(expr $COUNT + 1)ª EXECUÇÃO: T_Inserção = $T_INSERT, T_Busca = $T_SEARCH"
        COUNT=$(expr $COUNT + 1)
    done
    MEAN_INSERT=$(echo "$INSERT_SUM / $4" | bc -l | sed 's/^\./0./')
    MEAN_SEARCH=$(echo "$SEARCH_SUM / $4" | bc -l | sed 's/^\./0./')
    echo "MEDIA TEMPO INSERÇÃO = $MEAN_INSERT, MEDIA TEMPO BUSCA = $MEAN_SEARCH, BUSCA/QTD DE BUSCAS = $(echo "$MEAN_SEARCH / $1" | bc -l | sed 's/^\./0./')"
    echo -e "$1,$3,$4,\"$(echo $MEAN_INSERT | tr . ,)\",\"$(echo $MEAN_SEARCH | tr . ,)\",\"$(echo "$MEAN_SEARCH / $1" | bc -l | sed 's/^\./0./' | tr . ,)\"" >> id_$2.csv
}

# agr pra multiplas buscas

tester_repeat(){
    # $1 = lista de buscas. Ex : "10 100 1000 10000 100000 1000000"
    # $2 = lista de ids. Ex : "3 4 2 1"
    # $3 = arquivos (serão carregados no argv juntos)
    # $4 = n de repetições para cada execução do programa

    for busca in $1; do
        for id in $2; do
            echo -e "\n--------  BUSCA = $busca, ID = $id, ARQUIVOS = "$3", REPETIÇÕES = $4  --------\n"
            tester $busca $id "$3" $4
        done
    done
}
