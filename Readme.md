BUSCADOR DE PALAVRAS-CHAVE COM ÁRVORE BINÁRIA DE PESQUISA E ÁRVORE AVL

AUTOR: Andrei Pochmann Koenich

Este programa possui como finalidade simular o funcionamento de um buscador de palavras-chave.

Inicialmente, o programa abre um arquivo texto de entrada contendo frases que possuem, cada uma, um índice numérico (chamado de tweet).

Em seguida, realiza-se o processo de indexação. O programa armazena cada palavra de cada tweet em um nó de uma árvore, sendo que
cada no contendo uma palavra tambem ira conter uma lista simplesmente encadeada contendo todos os tweets em que aquela palavra aparece
no arquivo texto de entrada.

Por fim, realiza-se o processo de consulta. O programa abre um arquivo texto de consulta e verifica quais das palavras do arquivo estão
contidas na árvore criada na indexação, e imprime em um arquivo texto de saida a palavra em si e os tweets em que ela ocorre.

O numero de operações de comparação (e de rotações realizadas, no caso da árvore AVL) que são executadas ao longo do programa são contabilizados e também impressos
no final do arquivo texto de saida, assim como o numero de nós e a altura da árvore criada durante a indexação.

Para mais informações sobre o projeto, confira os arquivos na pasta "Descricoes".

Para compilar os programas envolvendo as árvores ABP e AVL, basta executar o comando "make" no terminal do Linux. Depois disso, é possível executar
os programas com os comandos "./buscadorABP" e "./buscadorAVL". Os arquivos texto "tweets.txt" e "consultas.txt" podem ser utilizados como parâmetros
de entrada.