/* Autor: Andrei Pochmann Koenich

/* O programa a seguir simula o funcionamento de um buscador de palavras-chave.

Inicialmente, o programa abre um arquivo texto de entrada contendo frases que possuem, cada uma, um índice numérico (chamado de tweet).

Em seguida, realiza-se o processo de indexacao. O programa armazena cada palavra de cada tweet em um no de uma arvore AVL, sendo que
cada no contendo uma palavra tambem ira conter uma lista simplesmente encadeada contendo todos os tweets em que aquela palavra aparece
no arquivo texto de entrada.

Por fim, realiza-se o processo de consulta. O programa abre um arquivo texto de consulta e verifica quais das palavras do arquivo estao
contidas na arvore AVL criada na indexacao, e imprime em um arquivo texto de saida a palavra em si e os tweets em que ela ocorre.

Os numeros de operacoes de comparacao e de rotacao que sao executadas ao longo do programa sao contabilizados e tambem impressos
no arquivo texto de saida, assim como o numero de nos e a altura da arvore AVL criada durante a indexacao. */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>

#define MAX_CARACTERES 50
#define MAX_LINHA 500
#define SEPARADORES " 0123456789,.&*%\?!;/-'@\"$#=~><)(][}{:\n\t_"

int comparacoes = 0; /* Variavel global para contabilizar a quantida de comparacoes realizadas ao longo do programa. */
int rotacoes = 0; /* Variavel global para contabilizar a quantida de rotacoes realizadas na arvore AVL ao longo do programa. */

typedef struct pLista /* Estrutura com informacoes de cada no da lista de tweets que pertence a cada um dos nos da arvore. */
{
    int tweet; /* Numero tweet de cada no da lista. */
    struct pLista *prox; /* Ponteiro para o proximo da lista. */

} ptLista;

typedef struct /* Estrutura com informacoes dos nos na arvore. */
{
    ptLista *ptListaTweet; /* Ponteiro para o inicio da lista simplesmente encadeada contendo os tweets em que a palavra aparece. */
    char palavra[MAX_CARACTERES]; /* String para armazenar a palavra do no em questao. */

} TipoInfo;

typedef struct /* Estrutura auxiliar a ser usada durante a indexacao. */
{
    int numero; /* Variavel inteira auxiliar da estrutura. */
    char word[MAX_CARACTERES]; /* String auxiliar da estrutura. */

} TipoInfoAux;

typedef struct TNodoA /* Estrutura contendo os filhos dos nos. */
{
    TipoInfo info; /* Estrutura contendo a palavra do no e a lista simplesmente encadeada contendo os seus tweets. */
    int FB; /* Fator de balanceamento do no na arvore AVL. */
    struct TNodoA *esq; /* Ponteiro para o filho esquerdo do no na arvore. */
    struct TNodoA *dir; /* Ponteiro para o filho direito do no na arvore. */

} pNodoA;

pNodoA* inicializa_arvore () /* Funcao para criar uma arvore. */
{
    return NULL; /* Retorna um ponteiro nulo. */
}

ptLista* inicializa_lista () /* Funcao para criar uma lista. */
{
    return NULL; /* Retorna um ponteiro nulo. */
}

ptLista* insere_inicio_lista (ptLista *first, int number) /* Funcao para inserir nos contendo numeros no final de uma lista simplesmente encadeada. */
{
    ptLista *novo; /* Declaracao do ponteiro do no a ser alocado na lista. */

    novo = (ptLista*) malloc (sizeof(ptLista)); /* Alocacao de espaco de memoria. */
    novo->tweet = number; /* Atribui o numero passado como parametro ao novo no da lista. */
    novo->prox = first; /* Atribui ponteiro nulo para o no posterior ao novo no inserido. */

    return novo; /* Retorna o ponteiro para o primeiro da lista. */
}

void imprime_lista_arquivo (ptLista* ptListaTweet, FILE *arq) /* Funcao para a impressao de toda a lista de numeros em um arquivo texto, utilizando comando iterativo. */
{
    ptLista *ptaux; /* Declaracao de ponteiro auxiliar para percorrer a lista. */

    if (ptListaTweet == NULL) /* Controle dos casos em que a lista esta vazia e nao ha nada a ser impresso. */
        fprintf (arq, "A lista esta vazia.\n");

    else /* Se a lista nao estiver vazia, imprime todos os numeros. */
    {
        for (ptaux = ptListaTweet; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao usada na impressao. */
            fprintf (arq, "%d, ", ptaux->tweet);
    }
}

int consultaLSE (ptLista *ptListaTweet, int number) /* Funcao para determinar se um determinado tweet ja esta inserido na lista. */
{
    if (ptListaTweet == NULL) /* Se a lista estiver vazia, retorna zero. */
        return 0;

    else if (ptListaTweet->tweet == number) /* Se o primeiro numero de tweet da lista for igual ao numero passado como parametro, retorna um. */
        return 1;

    else /* Se o numero nao foi encontrado na primeira posicao da lista, retorna zero. */
        return 0;
}

pNodoA* consulta_comum (pNodoA *a, char *chave) /* Funcao para determinar se uma determinada palavra ja esta inserida na arvore. */
{
    while (a != NULL)
    {
        comparacoes++; /* Incrementa o contador de comparacoes. */

        if (strcmp(a->info.palavra, chave) == 0) /* Se encontrar a palavra, retorna o ponteiro do no que a contem. */
            return a;

        else /* Se nao encontrar a palavra, continua a pesquisa na arvore. */
        {
            if (strcmp(a->info.palavra, chave) > 0)
                a = a->esq;

            else
                a = a->dir;
        }
    }

    return NULL; /* Se nao encontrar a palavra apos a pesquisa, retorna um ponteiro nulo. */
}

void converte_minuscula (char *s) /* Funcao para converter os caracteres de uma string em minusculo. */
{
    int i; /* Declaracao de variavel de controle a ser utilizada em iteracao. */

    for (i = 0; i < strlen(s); i++) /* Iteracao para converter cada caractere da string em minusculo. */
        s[i] = tolower(s[i]);
}

pNodoA* rotacao_direita(pNodoA *pt)
{
    pNodoA* ptu; /* Declaracao de ponteiro auxiliar a ser utilizado durante a rotacao. */

    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0; /* Atualiza o fator de balanceamento do nodo. */
    pt = ptu;

    return pt; /* Retorna o ponteiro do nodo passado como parametro, apos a atualizacao da arvore. */
}

pNodoA* rotacao_esquerda(pNodoA *pt)
{
    pNodoA* ptu; /* Declaracao de ponteiro auxiliar a ser utilizado durante a rotacao. */

    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0; /* Atualiza o fator de balanceamento do nodo. */
    pt = ptu;

    return pt; /* Retorna o ponteiro do nodo passado como parametro, apos a atualizacao da arvore. */
}

pNodoA* rotacao_dupla_direita (pNodoA* pt)
{
    pNodoA* ptu, *ptv; /* Declaracoes de ponteiros auxiliares a serem utilizados durante a rotacao. */

    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;

    if (ptv->FB == 1)
        pt->FB = -1; /* Atualiza o fator de balanceamento do nodo. */

    else
        pt->FB = 0; /* Atualiza o fator de balanceamento do nodo. */

    if (ptv->FB == -1)
        ptu->FB = 1; /* Atualiza o fator de balanceamento do nodo. */

    else
        ptu->FB = 0; /* Atualiza o fator de balanceamento do nodo. */

    pt = ptv;

    return pt; /* Retorna o ponteiro do nodo passado como parametro, apos a atualizacao da arvore. */
}

pNodoA* rotacao_dupla_esquerda (pNodoA* pt)
{
    pNodoA *ptu, *ptv; /* Declaracoes de ponteiros auxiliares a serem utilizados durante a rotacao. */

    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;

    if (ptv->FB == -1)
        pt->FB = 1; /* Atualiza o fator de balanceamento do nodo. */

    else
        pt->FB = 0; /* Atualiza o fator de balanceamento do nodo. */

    if (ptv->FB == 1)
        ptu->FB = -1; /* Atualiza o fator de balanceamento do nodo. */

    else
        ptu->FB = 0; /* Atualiza o fator de balanceamento do nodo. */

    pt = ptv;

    return pt; /* Retorna o ponteiro do nodo passado como parametro, apos a atualizacao da arvore. */
}


pNodoA* Caso1 (pNodoA* a, int *ok)
{
    pNodoA *ptu; /* Declaracao de ponteiro auxiliar para decidir qual rotacao executar. */

    ptu = a->esq;

    if (ptu->FB == 1) /* Analise do fator de balanceamento. */
    {
        rotacoes++; /* Incrementa o contador de rotacoes em uma unidade. */
        a = rotacao_direita(a); /* Executa a rotacao apos analise do fator de balanceamento. */
    }
    else
    {
        rotacoes += 2; /* Incrementa o contador de rotacoes em duas unidades. */
        a = rotacao_dupla_direita(a); /* Executa a rotacao apos analise do fator de balanceamento. */
    }

    a->FB = 0; /* Atualiza o fator de balanceamento do nodo. */
    *ok = 0; /* Atualiza a variavel de controle. */

    return a; /* Retorna o ponteiro para a raiz da arvore AVL. */
}

pNodoA* Caso2 (pNodoA *a, int *ok)
{
    pNodoA *ptu; /* Declaracao de ponteiro auxiliar para decidir qual rotacao executar. */

    ptu = a->dir;

    if (ptu->FB == -1) /* Analise do fator de balanceamento. */
    {
        rotacoes++; /* Incrementa o contador de rotacoes em uma unidade. */
        a = rotacao_esquerda(a); /* Executa a rotacao apos analise do fator de balanceamento. */
    }
    else
    {
        rotacoes += 2; /* Incrementa o contador de rotacoes em duas unidades. */
        a = rotacao_dupla_esquerda(a); /* Executa a rotacao apos analise do fator de balanceamento. */
    }

    a->FB = 0; /* Atualiza o fator de balanceamento do nodo. */
    *ok = 0; /* Atualiza a variavel de controle. */

    return a; /* Retorna o ponteiro para a raiz da arvore AVL. */
}

pNodoA* InsereAVL (pNodoA *a, TipoInfoAux x, int *ok) /* Funcao para inserir nos na arvore AVL de acordo com a ordem lexicografica das palavras. */
{
    comparacoes++; /* Incrementa o contador de comparacoes. */

    if (a == NULL)
    {
        a = (pNodoA*) malloc (sizeof(pNodoA)); /* Alocacao de espaco de memoria. */
        a->info.ptListaTweet = inicializa_lista(); /* Cria a lista de tweets presente no nodo. */
        a->info.ptListaTweet = insere_inicio_lista(a->info.ptListaTweet, x.numero); /* Insere um numero de tweet no fim da lista. */
        strcpy (a->info.palavra, x.word); /* Insere uma palavra no nodo. */
        a->esq = NULL; /* Atribui ponteiro nulo para o filho esquerdo. */
        a->dir = NULL; /* Atribui ponteiro nulo para o filho direito. */
        a->FB = 0; /* Atualiza o fator de balanceamento do nodo. */

        *ok = 1; /* Atualiza a variavel de controle. */
    }

    else if (strcmp(x.word, a->info.palavra) < 0) /* Enquanto nao chegar em um ponteiro nulo, segue a pesquisa na arvore de forma recursiva. */
    {
        a->esq = InsereAVL (a->esq, x, ok);

        if (*ok)
        {
            switch (a->FB)
            {
                case -1:
                {
                    a->FB = 0; /* Atualiza o fator de balanceamento. */
                    *ok = 0; /* Atualiza a variavel de controle. */
                    break;
                }
                case 0:
                {
                    a->FB = 1; /* Atualiza o fator de balanceamento. */
                    break;
                }
                case 1:
                {
                    a = Caso1 (a, ok); /* Direciona a arvore para a rotacao adequada. */
                    break;
                }
            }
        }
    }
    else /* Enquanto nao chegar em um ponteiro nulo, segue a pesquisa na arvore de forma recursiva. */
    {
        a->dir = InsereAVL (a->dir, x, ok);

        if (*ok)
        {
            switch (a->FB)
            {
                case 1:
                {
                    a->FB = 0; /* Atualiza o fator de balanceamento do nodo. */
                    *ok = 0; /* Atualiza a variavel de controle. */
                    break;
                }
                case 0:
                {
                    a->FB = -1; /* Atualiza o fator de balanceamento do nodo. */
                    break;
                }
                case -1:
                {
                    a = Caso2 (a, ok); /* Direciona a arvore para a rotacao adequada. */
                    break;
                }
            }
        }
    }

    return a; /* Retorna o ponteiro para a raiz da arvore AVL. */
}

int conta_nodos(pNodoA *a) /* Funcao para determinar o total de nodos de uma arvore binaria. */
{
    int total_nodos = 0; /* Declaracao de variavel que representa a quantidade de nodos. */

    if (a == NULL) /* Controle dos casos em que o ponteiro passado como parametro e nulo. */
        return 0;

    else
    {
        total_nodos++; /* Incrementa o contador de nodos em uma unidade. */
        total_nodos += conta_nodos(a->esq); /* Incrementa o contador de nodos de forma recursiva. */
        total_nodos += conta_nodos(a->dir); /* Incrementa o contador de nodos de forma recursiva. */

        return total_nodos; /* Retorna o numero total de nodos da arvore. */
    }
}

int calcula_altura (pNodoA *a) /* Funcao para determinar a altura de uma arvore cuja raiz e passada como parametro. */
{
    int alt_esq, alt_dir; /* Declaracoes de variaveis auxiliares. */

    if (a == NULL) /* Controle dos casos em que o ponteiro passado como parametro e nulo. */
        return 0;

    else
    {
         alt_esq = calcula_altura (a->esq); /* Chamada recursiva da funcao para percorrer a sub-arvore esquerda. */
         alt_dir = calcula_altura (a->dir); /* Chamada recursiva da funcao para percorrer a sub-arvore direita. */

         if (alt_esq > alt_dir) /* Comparacao entre as altura dos dois nodos filhos, antes de retornar o valor da altura. */
            return (1 + alt_esq);

         else
            return (1 + alt_dir);
    }
}

void imprime_estatisticas (FILE *arq2, pNodoA *a, int aux_comparacoes_index) /* Funcao para realizar as impressoes dos dados das estatisticas de indexacao e consulta no arquivo de saida. */
{
    fprintf (arq2, "********** Estatísticas da Indexação **********\n\n");
    fprintf (arq2, "Nodos = %d\n", conta_nodos(a)); /* Impressao do numero de nodos da arvore criada na indexacao. */
    fprintf (arq2, "Comparações = %d\n", aux_comparacoes_index); /* Impressao do numero de comparacoes realizadas durante a indexacao. */
    fprintf (arq2, "Rotações = %d\n", rotacoes); /* Impressao do numero de rotacoes realizadas durante a indexacao, na insercao dos nos na arvore. */
    fprintf (arq2, "Altura da Árvore = %d\n\n", calcula_altura(a)); /* Impressao da altura da arvore criada durante a indexacao. */
    fprintf (arq2, "********** Estatísticas da Consulta **********\n\n");
    fprintf (arq2, "Comparações = %d\n", comparacoes); /* Impressao do numero de comparacoes realizadas durante a consulta. */
}

pNodoA* indexa_arvoreAVL (pNodoA *a, char *arquivo_entrada) /* Funcao para realizar as indexacoes das palavras e dos tweets em uma arvore binaria de pesquisa. */
{
    int ok; /* Declaracao de variavel de controle a ser utilizada nas operacoes envolvendo a arvore AVL. */
    FILE *arq; /* Declaracao de variavel correspondente ao arquivo texto de entrada. */
    char linha[MAX_LINHA]; /* Variavel para receber cada linha do arquivo texto de entrada. */
    char *aux; /* Variavel que representa uma string auxiliar, que recebera cada palavra de cada linha. */
    TipoInfoAux estrutura_aux; /* Estrutura auxiliar para receber numero de tweet e string. */
    pNodoA* ptaux; /* Ponteiro auxiliar a ser usado nas operacoes de consulta, a fim de evitar insercoes repetidas na arvore. */

    if (!(arq = fopen (arquivo_entrada, "r"))) /* Abertura do arquivo texto de entrada para leitura, com controle dos casos em que nao e possivel abri-lo. */
    {
        system("cls");
        printf("Erro na abertura do arquivo texto de entrada. Fim do programa.\n");
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    while (!feof(arq)) /* Iteracao para percorrer o arquivo texto de entrada ate o seu fim. */
    {
        fgets (linha, MAX_LINHA, arq); /* Armazena uma string correspondente a uma linha do arquivo texto. */

        aux = strtok (linha, ";"); /* Armazena o numero do tweet da linha em questao do arquivo texto. */
        estrutura_aux.numero = atoi(aux); /* Converte a string em um numero inteiro e armazena na estrutura auxiliar. */

        while (aux != NULL) /* Iteracao para armazenar cada palavra de cada linha do arquivo texto. */
        {
            aux = strtok (NULL, SEPARADORES); /* Armazena cada palavra na variavel auxiliar. */

            if (aux != NULL) /* Verifica se chegou ao final da respectiva linha do arquivo texto. */
            {
                converte_minuscula(aux);
                ptaux = consulta_comum (a, aux); /* Verifica se a palavra em questao ja esta inserida na arvore. */

                if (ptaux == NULL) /* Se a palavra nao estiver na arvore, entao ela sera inserida junto com o numero do seu respectivo tweet. */
                {
                    strcpy (estrutura_aux.word, aux);
                    a = InsereAVL(a, estrutura_aux, &ok);
                }
                /* Se a palavra em questao ja estiver na arvore, insere-se somente o numero do tweet na sua lista encadeada, com controle para evitar numeros repetidos na lista. */
                else if (!consultaLSE(ptaux->info.ptListaTweet, estrutura_aux.numero))
                    ptaux->info.ptListaTweet = insere_inicio_lista(ptaux->info.ptListaTweet, estrutura_aux.numero);
            }
        }
    }

    fclose(arq); /* Fechamento do arquivo texto de entrada. */

    return a; /* Retorna o ponteiro para a raiz da arvore. */
}

/* Funcao para realizar a consulta das palavras do arquivo de consultas na arvore e imprimi-las no arquivo de saida, com seus respectivos tweets. */
void consulta_arvoreAVL (pNodoA *a, char *arquivo_consultas, char *arquivo_saida)
{
    int aux_comparacoes_index; /* Declaracao de variavel para armazenar a quantidade de comparacoes realizadas na indexacao. */
    FILE *arq1; /* Declaracao de variavel correspondente ao arquivo texto de consulta. */
    FILE *arq2; /* Declaracao de variavel correspondente ao arquivo texto de saida. */
    char linha[MAX_LINHA]; /* Variavel para receber cada linha do arquivo texto de consulta. */
    char string_aux[MAX_CARACTERES]; /* Variavel para receber cada linha do arquivo texto de consulta, apos sua adequacao para consulta. */
    pNodoA* ptaux; /* Ponteiro auxiliar a ser usado nas operacoes de consulta, a fim de evitar repeticoes de palavras no arquivo texto de saida. */
    int i; /* Declaracao de variavel de controle a ser utilizada em iteracao. */

    aux_comparacoes_index = comparacoes; /* Armazena a quantidade de comparacoes realizadas na indexacao. */
    comparacoes = 0; /* Zera o contador de comparacoes, para em seguida armazenar as comparacoes das operacoes de consulta. */

    if (!(arq1 = fopen (arquivo_consultas, "r"))) /* Abertura do arquivo texto de consulta para leitura, com controle dos casos em que nao e possivel abri-lo. */
    {
        system("cls");
        printf("Erro na abertura do arquivo texto de consultas. Fim do programa.\n");
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    if (!(arq2 = fopen (arquivo_saida, "w"))) /* Criacao do arquivo texto de saida para escrita, com controle dos casos em que nao e possivel cria-lo. */
    {
        system("cls");
        printf("Erro na criacao do arquivo texto de saida. Fim do programa.\n");
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    memset(string_aux, 0, sizeof(string_aux)); /* Zera todo o array de caracteres da string auxiliar antes da iteracao. */

    while (!feof(arq1)) /* Iteracao para percorrer o arquivo texto de consulta ate o seu fim. */
    {
        fgets (linha, MAX_LINHA, arq1); /* Armazena uma string correspondente a uma linha do arquivo texto. */

        for (i = 0; linha[i] != '\n' && linha[i] != '\0'; i++) /* Iteracao para adequar a string da linha, antes de realizar a operacao de consulta. */
            string_aux[i] = linha[i];

        converte_minuscula(string_aux); /* Converte todos os caracteres da string auxiliar para minusculo. */
        ptaux = consulta_comum(a, string_aux); /* Verifica se a string em questao ja esta na arvore. */

        if (ptaux != NULL) /* Se a string ja esta na arvore, ela sera impressa junto com os seus tweets no arquivo texto de saida. */
        {
            fprintf (arq2, "Consulta: %s\t\tPalavra encontrada nos tweets ", ptaux->info.palavra);
            imprime_lista_arquivo(ptaux->info.ptListaTweet, arq2); /* Imprime a lista de numeros tweet no arquivo de saida. */
            fprintf (arq2, "\n\n"); /* Impressao de quebra de linha no arquivo de saida. */
        }
        else /* Se a string nao estiver na arvore, ela sera impressa junto com a informacao de que e inexistente na estrutura. */
            fprintf (arq2, "Consulta: %s\t\tPalavra não encontrada.\n\n", string_aux);

        memset(string_aux, 0, sizeof(string_aux)); /* Zera todo o array de caracteres da string auxiliar ao fim de cada iteracao. */
    }

    imprime_estatisticas (arq2, a, aux_comparacoes_index); /* Funcao para realizar as impressoes dos dados das estatisticas de indexacao e consulta no arquivo de saida. */

    fclose (arq1); /* Fechamento do arquivo texto de consulta. */
    fclose (arq2); /* Fechamento do arquivo texto de saida. */
}

int main ()
{
    clock_t starting_time, finishing_time;

    starting_time = clock();
    setlocale (LC_ALL, ""); /* Permite a impressao de caracteres acentuados na tela. */

    char arquivo_entrada[MAX_CARACTERES];
    char arquivo_consultas[MAX_CARACTERES];
    char arquivo_saida[MAX_CARACTERES];

    printf("BUSCADOR DE PALAVRAS-CHAVE COM ARVORE AVL\n");
    printf("\nAndrei Pochmann Koenich - 05/2021\n");
    printf("\n--------------------------------\n");

    printf("\nDigite o nome do arquivo texto de entrada, contendo os tweets:\n");
    gets(arquivo_entrada);

    pNodoA *raiz = inicializa_arvore(); /* Inicializa uma arvore AVL. */
    raiz = indexa_arvoreAVL (raiz, arquivo_entrada); /* Realiza a indexacao das palavras e dos tweets do arquivo de entrada na arvore AVL. */

    printf("\nDigite o nome do arquivo texto de consultas:\n");
    gets(arquivo_consultas);
    printf("\nDigite o nome do arquivo texto de saida:\n");
    gets(arquivo_saida);
    system("cls");

    consulta_arvoreAVL (raiz, arquivo_consultas, arquivo_saida); /* Realiza a consulta das palavras do arquivo de consultas na arvore e as imprime no arquivo de saida. */

    printf("Operacoes realizadas com sucesso.\n");
    finishing_time = clock();
    printf("\nTempo de execucao: %ld ms\n", finishing_time - starting_time);

    system("pause");
    return 0; /* Retorna zero para indicar que o programa foi executado corretamente. */
}
