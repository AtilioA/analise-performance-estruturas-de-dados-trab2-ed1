
/**
Contem um inteiro e dois apontadores (esquerda/direita)
*/
typedef struct NO* ArvBin;

/**
Inicializa a árvore e deixa a raiz NULL
retorna: Raiz alocada e apontada para NULL
*/
ArvBin* cria_ArvBin();


/**
Insere 'valor' na árvore utilizando a regra que o filho esquerdo é menor que a raiz que é menor o filho direito.

Retorna: 1 em caso de sucesso. 
*/
int insere_ArvBin(ArvBin* raiz, int valor);


void libera_ArvBin(ArvBin *raiz);

int remove_ArvBin(ArvBin *raiz, int valor);
int estaVazia_ArvBin(ArvBin *raiz);

/* Conta o número de nós não-folha de uma árvore binária 
retorna: Numero de nós não folha
*/
int totalNaoFolha_Arvbin(ArvBin *raiz);

/** conta o número de folhas de uma árvore binária.
retorna: Numero de nós folhas
*/
int totalFolha_Arvbin(ArvBin *raiz);

int altura_ArvBin(ArvBin *raiz);
/*função que conta o número de nós de uma árvore binária. */
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

