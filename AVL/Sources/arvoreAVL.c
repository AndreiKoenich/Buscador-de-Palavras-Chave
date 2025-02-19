#include "../Headers/arvoreAVL.h"

extern int comparacoes;
extern int rotacoes;

ptrNodoArvore* inicializaArvore () /* Funcao para criar uma arvore. */
{
    return NULL; 
}

ptrNodoArvore* rotacaoDireita(ptrNodoArvore *pt)
{
    ptrNodoArvore* ptu;

    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;

    return pt;
}

ptrNodoArvore* rotacaoEsquerda(ptrNodoArvore *pt)
{
    ptrNodoArvore* ptu; 

    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;

    return pt;
}

ptrNodoArvore* rotacaoDuplaDireita (ptrNodoArvore* pt)
{
    ptrNodoArvore* ptu, *ptv; 

    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;

    if (ptv->FB == 1)
        pt->FB = -1;

    else
        pt->FB = 0;

    if (ptv->FB == -1)
        ptu->FB = 1;

    else
        ptu->FB = 0; 

    pt = ptv;

    return pt;
}

ptrNodoArvore* rotacaoDuplaEsquerda (ptrNodoArvore* pt)
{
    ptrNodoArvore *ptu, *ptv;

    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;

    if (ptv->FB == -1)
        pt->FB = 1;

    else
        pt->FB = 0;

    if (ptv->FB == 1)
        ptu->FB = -1; 

    else
        ptu->FB = 0; 

    pt = ptv;

    return pt; 
}


ptrNodoArvore* caso1 (ptrNodoArvore* a, int *ok)
{
    ptrNodoArvore *ptu; 
    ptu = a->esq;

    if (ptu->FB == 1) 
    {
        rotacoes++; 
        a = rotacaoDireita(a); 
    }
    else
    {
        rotacoes += 2;
        a = rotacaoDuplaDireita(a); 
    }

    a->FB = 0;
    *ok = 0; 
    return a;
}

ptrNodoArvore* caso2 (ptrNodoArvore *a, int *ok)
{
    ptrNodoArvore *ptu;

    ptu = a->dir;

    if (ptu->FB == -1)
    {
        rotacoes++; 
        a = rotacaoEsquerda(a); 
    }
    else
    {
        rotacoes += 2;
        a = rotacaoDuplaEsquerda(a);
    }

    a->FB = 0; 
    *ok = 0;

    return a; 
}

ptrNodoArvore* insereAVL (ptrNodoArvore *a, TipoInfoAux x, int *ok) /* Funcao para inserir nos na arvore AVL de acordo com a ordem lexicografica das palavras. */
{
    comparacoes++;

    if (a == NULL)
    {
        a = (ptrNodoArvore*) malloc (sizeof(ptrNodoArvore)); 
        a->info.ptrListaTweet = inicializaLista(); 
        a->info.ptrListaTweet = insereInicioLista(a->info.ptrListaTweet, x.numero); 
        strcpy (a->info.palavra, x.word); 
        a->esq = NULL; 
        a->dir = NULL; 
        a->FB = 0; 

        *ok = 1;
    }

    else if (strcmp(x.word, a->info.palavra) < 0) 
    {
        a->esq = insereAVL (a->esq, x, ok);

        if (*ok)
        {
            switch (a->FB)
            {
                case -1:
                {
                    a->FB = 0; 
                    *ok = 0; 
                    break;
                }
                case 0:
                {
                    a->FB = 1; 
                    break;
                }
                case 1:
                {
                    a = caso1 (a, ok); 
                    break;
                }
            }
        }
    }
    else 
    {
        a->dir = insereAVL (a->dir, x, ok);

        if (*ok)
        {
            switch (a->FB)
            {
                case 1:
                {
                    a->FB = 0; 
                    *ok = 0; 
                    break;
                }
                case 0:
                {
                    a->FB = -1;
                    break;
                }
                case -1:
                {
                    a = caso2 (a, ok);
                    break;
                }
            }
        }
    }

    return a;
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

ptrNodoArvore* indexaArvoreAVL(ptrNodoArvore *a, char *nomeArquivoEntrada)  /* Funcao para realizar as indexacoes das palavras e dos tweets em uma arvore binaria de pesquisa. */
{
    int ok;
    FILE *arqEntrada;
    char linha[MAX_LINHA];
    char *aux;
    TipoInfoAux estruturaAux;
    ptrNodoArvore* ptaux;

    if (!(arqEntrada = fopen(nomeArquivoEntrada, "r")))
    {
        system("clear");
        printf("Erro na abertura do arqEntradauivo texto de entrada. Fim do programa.\n");
        
        exit(1);
    }

    while (!feof(arqEntrada))
    {
        fgets(linha, MAX_LINHA, arqEntrada);

        aux = strtok(linha, ";");
        estruturaAux.numero = atoi(aux);

        while (aux != NULL)
        {
            aux = strtok(NULL, SEPARADORES);

            if (aux != NULL)
            {
                converteMinuscula(aux);
                ptaux = consultaComum(a, aux);

                if (ptaux == NULL)
                {
                    strcpy(estruturaAux.word, aux);
                    a = insereAVL(a, estruturaAux, &ok);
                }
                else if (!consultaLSE(ptaux->info.ptrListaTweet, estruturaAux.numero))
                    ptaux->info.ptrListaTweet = insereInicioLista(ptaux->info.ptrListaTweet, estruturaAux.numero);
            }
        }
    }

    fclose(arqEntrada);

    return a;
}

/* Funcao para realizar a consulta das palavras do arquivo de consultas na arvore e imprimi-las no arquivo de saida, com seus respectivos tweets. */
void consultaArvoreAVL (ptrNodoArvore *a, char *nomeArquivoConsultas, char *nomeArquivoSaida)
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
        printf("Erro na abertura do arquivo texto de consultas. Fim do programa.\n");
        
        exit(1);
    }

    if (!(arqSaida = fopen (nomeArquivoSaida, "w"))) 
    {
        system("clear");
        printf("Erro na criacao do arquivo texto de saida. Fim do programa.\n");
        
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