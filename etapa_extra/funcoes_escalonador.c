#include <stdio.h>
#include <string.h>

void ordenaCrescente(int *tempo_execucao, char (*nome_processos)[10], int *processo, int *num_linhas)
{
    int pos, temp = 0;

    int numero_de_processos = *num_linhas;

    int i, j;
    char temps[20];
    for (i = 0; i < numero_de_processos; i++)
    {
        pos = i;
        for (j = i + 1; j < numero_de_processos; j++)
        {
            if (tempo_execucao[j] < tempo_execucao[pos])
                pos = j;
        }

        temp = tempo_execucao[i];
        tempo_execucao[i] = tempo_execucao[pos];
        tempo_execucao[pos] = temp;

        strcpy(temps, nome_processos[i]);
        strcpy(nome_processos[i], nome_processos[pos]);
        strcpy(nome_processos[pos], temps);

        temp = processo[i];
        processo[i] = processo[pos];
        processo[pos] = temp;
    }
}

void ordenaDecrescente(int *tempo_execucao, char (*nome_processos)[10], int *processo, int *num_linhas)
{
    int pos, temp = 0;
    int numero_de_processos = *num_linhas;

    int i, j;
    char temps[20];
    for (i = 0; i < numero_de_processos; i++)
    {
        pos = i;
        for (j = i + 1; j < numero_de_processos; j++)
        {
            if (tempo_execucao[j] > tempo_execucao[pos])
                pos = j;
        }

        temp = tempo_execucao[i];
        tempo_execucao[i] = tempo_execucao[pos];
        tempo_execucao[pos] = temp;

        strcpy(temps, nome_processos[i]);
        strcpy(nome_processos[i], nome_processos[pos]);
        strcpy(nome_processos[pos], temps);

        temp = processo[i];
        processo[i] = processo[pos];
        processo[pos] = temp;
    }
}

FILE *separaAsTarefasImprimeArquivo(int *tempo_execucao, char (*nome_processos)[10], int *num_linhas, int n_nucleos, const char *nome_arquivo)
{
    FILE *f_saida = fopen(nome_arquivo, "w");
    int num_processadores = 0;
    while (num_processadores < n_nucleos)
    {
        int proc_inicio = 0, proc_fim = 0;
        fprintf(f_saida, "Processador_%d\n", num_processadores + 1);
        for (int i = 0 + num_processadores; i < *num_linhas; i = i + n_nucleos)
        {
            proc_fim = tempo_execucao[i] + proc_inicio;
            fprintf(f_saida, "%s;%d;%d\n", nome_processos[i], proc_inicio, proc_fim);
            proc_inicio = proc_fim;
        }
        fprintf(f_saida, "\n");
        num_processadores++;
    }
    return f_saida;
}