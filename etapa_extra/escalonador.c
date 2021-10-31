#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "funcoes_escanlonador.h"

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

    ordenaCrescente(tempo_execucao, nome_processo, processo, &num_linhas);

    FILE *f_saida1 = fopen("menor_primeiro.txt", "w");
    FILE *f_saida2 = fopen("maior_primeiro.txt", "w");

    int num_processadores = 0;
    int n_nucleos = atoi(argv[2]);

    while (num_processadores < n_nucleos)
    {
        int proc_inicio = 0, proc_fim = 0;
        fprintf(f_saida1, "Processador_%d\n", num_processadores + 1);
        for (i = 0 + num_processadores; i < num_linhas; i = i + n_nucleos)
        {
            proc_fim = tempo_execucao[i] + proc_inicio;
            fprintf(f_saida1, "%s;%d;%d\n", nome_processo[i], proc_inicio, proc_fim);
            proc_inicio = proc_fim;
        }
        fprintf(f_saida1, "\n");
        num_processadores++;
    }

    num_processadores = n_nucleos;

/* aqui ordena ao contrario */
    ordenaDecrescente(tempo_execucao, nome_processo, processo, &num_linhas);

    num_processadores = 0;
    while (num_processadores < n_nucleos)
    {
        int proc_inicio = 0, proc_fim = 0;
        fprintf(f_saida2, "Processador_%d\n", num_processadores + 1);
        for (i = 0 + num_processadores; i < num_linhas; i = i + n_nucleos)
        {
            proc_fim = tempo_execucao[i] + proc_inicio;
            fprintf(f_saida2, "%s;%d;%d\n", nome_processo[i], proc_inicio, proc_fim);
            proc_inicio = proc_fim;
        }
        fprintf(f_saida2, "\n");
        num_processadores++;
    }

    fclose(f_saida1);
    fclose(f_saida2);
    return 0;
}
