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