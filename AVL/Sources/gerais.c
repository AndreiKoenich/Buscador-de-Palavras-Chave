extern int comparacoes;
extern int rotacoes;

#include "../Headers/gerais.h"

void imprimeEstatisticas (FILE *arqSaida, ptrNodoArvore *a, int aux_comparacoes_index) /* Funcao para realizar as impressoes dos dados das estatisticas de indexacao e consulta no arquivo de saida. */
{
    fprintf (arqSaida, "********** Estatisticas da Indexacao **********\n\n");
    fprintf (arqSaida, "Nodos = %d\n", contaNodos(a));
    fprintf (arqSaida, "Comparacoes = %d\n", aux_comparacoes_index); 
    fprintf (arqSaida, "Rotacoes = %d\n", rotacoes); 
    fprintf (arqSaida, "Altura da Árvore = %d\n\n", calculaAltura(a)); 
    fprintf (arqSaida, "********** Estatisticas da Consulta **********\n\n");
    fprintf (arqSaida, "Comparacoes = %d\n", comparacoes);
}

void converteMinuscula (char *s) /* Funcao para converter os caracteres de uma string em minusculo. */
{
    int i; 

    for (i = 0; i < strlen(s); i++) 
        s[i] = tolower(s[i]);
}