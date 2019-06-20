
typedef struct No* ArvAVL;

ArvAVL *cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int valor);
int remove_ArvAVL(ArvAVL *raiz, int valor);
int esta_vazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int total_No_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void pre_ordem_ArvAVL(ArvAVL *raiz);
void em_ordem_ArvAVL(ArvAVL *raiz);
void pos_ordem_ArvAVL(ArvAVL *raiz);
