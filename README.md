# Análise de desempenho de estruturas de dados variadas para um indexador de arquivos utilizando a linguagem C
Indexador de arquivos de texto com 5 estruturas de dados disponíveis -- lista encadeada, árvore binária não balanceada, árvore binária AVL, árvore de prefixos e tabela hash.

## Instruções:

Para compilar, digite o comando `make menu` no terminal dentro da pasta raiz do projeto. Após isso, é possível executar o programa da seguinte forma:
```./indexador [numero de buscas] [arquivo 1] [arquivo 2] ... [arquivo n]```
O número de buscas será utilizado para realizar buscas aleatórias. Após carregar todas as palavras dos arquivos, também será pedido ao usuário que entre com uma string para que seja buscada em todos os arquivos lidos.
Por fim, o programa irá exibir os tempos de inserção, busca aleatória e busca da string informada pelo usuário.
