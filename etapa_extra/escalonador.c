#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "funcoes_escalonador.h"

int main(int argc, char *argv[])
{
    FILE *f;
    int numero_processos;
    char nome_processo[20][10];
    int tempo_execucao[20];
    int processo[20];

    if (argc != 3)
    {
        fprintf(stderr, "Numero de parametros incorreto. Esperam-se 3.\n");
        exit(1);
    }

    if (!(f = fopen(argv[1], "r")))
    {
        fprintf(stderr, "Arquivo não encontrado!.\n");
        exit(1);
    }

    f = fopen(argv[1], "r");
    char linha[200];

    int i, j = 0;
    int num_linhas = 0;
    char c = '\0';
    char num[4];
    while (fgets(linha, 200, f) && num_linhas < 20)
    {
        for (i = 0; linha[i] != ' '; i++)
        {
            c = linha[i];
            nome_processo[num_linhas][i] = c;
        }
        nome_processo[num_linhas][i++] = '\0';
        for (i = i; linha[i] != '\n' && linha[i] != '\0'; i++, j++)
        {
            c = linha[i];
            num[j] = c;
        }
        num[j++] = '\0';
        tempo_execucao[num_linhas] = atoi(num);
        num_linhas++;
        j = 0;
    }
    fclose(f);

    numero_processos = num_linhas;

    i = 0, j = 0;
    int n_nucleos = atoi(argv[2]);

    ordenaCrescente(tempo_execucao, nome_processo, processo, &num_linhas);
    FILE *f_saida1 = separaAsTarefasImprimeArquivo(tempo_execucao, nome_processo, &num_linhas, n_nucleos, "menor_primeiro.txt");

    ordenaDecrescente(tempo_execucao, nome_processo, processo, &num_linhas);
    FILE *f_saida2 = separaAsTarefasImprimeArquivo(tempo_execucao, nome_processo, &num_linhas, n_nucleos, "maior_primeiro.txt");

    fclose(f_saida1);
    fclose(f_saida2);
    return 0;
}
