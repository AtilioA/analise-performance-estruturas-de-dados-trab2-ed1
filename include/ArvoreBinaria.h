/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD árvore binária para o indexador de arquivos.
 */


/**
Contem um inteiro e dois apontadores (esquerda/direita)
*/
typedef struct NO* ArvBin;

/**
Inicializa a árvore e deixa a raiz NULL
retorna: Raiz alocada e apontada para NULL
*/
ArvBin* criaArvBin();


/**
Insere 'valor' na árvore utilizando a regra que o filho esquerdo é menor que a raiz que é menor o filho direito.

Retorna: 1 em caso de sucesso.
*/
int insereArvBin(ArvBin* raiz, int valor);

/**
Pesquisa um valor a partir da árvore raiz
retorna 1 se encontrar o valor e 0 caso não encontre
*/
int consultaArvBin(ArvBin *raiz, int valor);

/**
Verifica se a árvore está vazia
*/
int estaVaziaArvBin(ArvBin *raiz);

/*
Conta o número de nós não-folha de uma árvore binária
retorna: Numero de nós não folha
*/
int totalNaoFolhaArvbin(ArvBin *raiz);

/**
Conta o número de folhas de uma árvore binária.
retorna: Numero de nós folhas
*/
int totalFolhaArvbin(ArvBin *raiz);

/*conta o número de nós de uma árvore binária. */
int totalNOsArvBin(ArvBin *raiz);

/** Imprime em pre-ordem */
void preOrdemArvBin(ArvBin *raiz);

/** Imprime em-ordem */
void emOrdemArvBin(ArvBin *raiz);

/** Imprime em pós-ordem */
void posOrdemArvBin(ArvBin *raiz);


/**
Libera a árvore binária da memória
*/
void liberaArvBin(ArvBin *raiz);
