#include "../Headers/arvoreABP.h"

extern int comparacoes;

ptrNodoArvore* inicializaArvore () /* Funcao para criar uma arvore. */
{
    return NULL; 
}

ptrNodoArvore* consultaComum (ptrNodoArvore *a, char *chave) /* Funcao para determinar se uma determinada palavra ja esta inserida na arvore. */
{
    while (a != NULL)
    {
        comparacoes++;

        if (strcmp(a->info.palavra, chave) == 0) 
            return a;
        else 
        {
            if (strcmp(a->info.palavra, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL; 
}

ptrNodoArvore* insereABP (ptrNodoArvore *a, TipoInfoAux chave) /* Funcao para inserir nos na ABP de acordo com a ordem lexicografica das palavras. */
{
    comparacoes++; 

    if (a == NULL)
    {
        a = (ptrNodoArvore*) malloc (sizeof(ptrNodoArvore));
        a->info.ptrListaTweet = inicializaLista(); 
        a->info.ptrListaTweet = insereInicioLista(a->info.ptrListaTweet, chave.numero);
        strcpy (a->info.palavra, chave.word);
        a->esq = NULL; 
        a->dir = NULL; 
    }
    else
    {
        if (strcmp (chave.word, a->info.palavra) < 0)
            a->esq = insereABP(a->esq, chave);
        else
            a->dir = insereABP(a->dir, chave);
    }

    return a;
}

int contaNodos(ptrNodoArvore *a) /* Funcao para determinar o total de nodos de uma arvore binaria. */
{
    int totalNodos = 0; 

    if (a == NULL)
        return 0;
    else
    {
        totalNodos++;
        totalNodos += contaNodos(a->esq);
        totalNodos += contaNodos(a->dir);

        return totalNodos;
    }
}

int calculaAltura (ptrNodoArvore *a) /* Funcao para determinar a altura de uma arvore cuja raiz e passada como parametro. */
{
    int alt_esq, alt_dir; 

    if (a == NULL)
        return 0;
    else
    {
         alt_esq = calculaAltura (a->esq); 
         alt_dir = calculaAltura (a->dir);

         if (alt_esq > alt_dir) 
            return (1 + alt_esq);
         else
            return (1 + alt_dir);
    }
}

ptrNodoArvore* indexaArvoreABP (ptrNodoArvore *a, char *nomeArquivoEntrada) /* Funcao para realizar as indexacoes das palavras e dos tweets em uma arvore binaria de pesquisa. */
{
    FILE *arq; 
    char linha[MAX_LINHA]; 
    char *aux; 
    TipoInfoAux estruturaAux;
    ptrNodoArvore* ptaux;

    if (!(arq = fopen (nomeArquivoEntrada, "r"))) 
    {
        system("clear");
        printf ("Erro na abertura do arquivo texto de entrada. Fim do programa.\n");
        
        exit(1); 
    }

    while (!feof(arq))
    {
        fgets (linha, MAX_LINHA, arq); 
        aux = strtok (linha, ";"); 
        estruturaAux.numero = atoi(aux);

        while (aux != NULL) 
        {
            aux = strtok (NULL, SEPARADORES); 

            if (aux != NULL)
            {
                converteMinuscula(aux);
                ptaux = consultaComum (a, aux); 

                if (ptaux == NULL)
                {
                    strcpy (estruturaAux.word, aux);
                    a = insereABP(a, estruturaAux);
                }
        
                else if (!consultaLSE(ptaux->info.ptrListaTweet, estruturaAux.numero))
                    ptaux->info.ptrListaTweet = insereInicioLista(ptaux->info.ptrListaTweet, estruturaAux.numero);
            }
        }
    }
    fclose(arq);

    return a;
}

/* Funcao para realizar a consulta das palavras do arquivo de consultas na arvore e imprimi-las no arquivo de saida, com seus respectivos tweets. */
void consultaArvoreABP (ptrNodoArvore *a, char *nomeArquivoConsultas, char *nomeArquivoSaida)
{
    int aux_comparacoes_index;
    FILE *arqConsulta; 
    FILE *arqSaida; 
    char linha[MAX_LINHA];
    char stringAux[MAXIMOCARACTERES];
    ptrNodoArvore* ptaux; 
    int i; 

    aux_comparacoes_index = comparacoes;
    comparacoes = 0; 

    if (!(arqConsulta = fopen (nomeArquivoConsultas, "r"))) 
    {
        system("clear");
        printf ("Erro na abertura do arquivo texto de consultas. Fim do programa.\n");
        
        exit(1);
    }

    if (!(arqSaida = fopen (nomeArquivoSaida, "w"))) 
    {
        system("clear");
        printf ("Erro na abertura do arquivo texto de saida. Fim do programa.\n");
        
        exit(1); 
    }

    memset(stringAux, 0, sizeof(stringAux));

    while (!feof(arqConsulta))
    {
        fgets (linha, MAX_LINHA, arqConsulta); 

        for (i = 0; linha[i] != '\n' && linha[i] != '\0'; i++) 
            stringAux[i] = linha[i];

        converteMinuscula(stringAux);
        ptaux = consultaComum(a, stringAux);

        if (ptaux != NULL) 
        {
            fprintf (arqSaida, "Consulta: %s\t\tPalavra encontrada nos tweets ", ptaux->info.palavra);
            imprimeListaArquivo(ptaux->info.ptrListaTweet, arqSaida); 
            fprintf (arqSaida, "\n\n"); 
        }
        else 
            fprintf (arqSaida, "Consulta: %s\t\tPalavra não encontrada.\n\n", stringAux);

        memset(stringAux, 0, sizeof(stringAux)); 
    }

    imprimeEstatisticas (arqSaida, a, aux_comparacoes_index); 

    fclose (arqConsulta); 
    fclose (arqSaida); 
}

void liberaArvore(ptrNodoArvore *raiz) /* Funcao recursiva para desalocar a arvore e suas listas de tweets. */
{
    if (raiz == NULL) 
        return; 

    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);
    liberaLista(raiz->info.ptrListaTweet);
    free(raiz);
}