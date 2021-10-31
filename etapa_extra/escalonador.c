#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "scheduler_functions.h"

int main(int argc, char *argv[])
{
    FILE *f;
    int number_of_processes;
    char process_name[20][10];
    int burst_time[20];
    int process[20];
    int wait_time[20];
    int turn_around_time[20];

    if (argc != 3)
    {
        fprintf(stderr, "Too few/many arguments! Expecting 3.\n");
        exit(1);
    }

    if (!(f = fopen(argv[1], "r")))
    {
        fprintf(stderr, "File not found.\n");
        exit(1);
    }

    f = fopen(argv[1], "r");
    char line[200];

    int i, j = 0;
    int line_count = 0;
    char c = '\0';
    char num[4];
    while (fgets(line, 200, f) && line_count < 20)
    {
        for (i = 0; line[i] != ' '; i++)
        {
            c = line[i];
            process_name[line_count][i] = c;
        }
        process_name[line_count][i++] = '\0';
        for (i = i; line[i] != '\n' && line[i] != '\0'; i++, j++)
        {
            c = line[i];
            num[j] = c;
        }
        num[j++] = '\0';
        burst_time[line_count] = atoi(num);
        line_count++;
        j = 0;
    }
    fclose(f);

    int total, pos, temp = 0;
    float avg_wait_time, avg_turn_around_time = 0.0;

    number_of_processes = line_count;

    i = 0, j = 0;
    char temps[20];

    sortAscending(burst_time, process_name, process, &line_count);

    FILE *f_out1 = fopen("menor_primeiro.txt", "w");
    FILE *f_out2 = fopen("maior_primeiro.txt", "w");

    int processors_count = 0;
    int n_cores = atoi(argv[2]);

    while (processors_count < n_cores)
    {
        int proc_start = 0, proc_end = 0;
        fprintf(f_out1, "Processador_%d\n", processors_count + 1);
        for (i = 0 + processors_count; i < line_count; i = i + n_cores)
        {
            proc_end = burst_time[i] + proc_start;
            fprintf(f_out1, "%s;%d;%d\n", process_name[i], proc_start, proc_end);
            proc_start = proc_end;
        }
        fprintf(f_out1, "\n");
        processors_count++;
    }

    processors_count = n_cores;

/* aqui ordena ao contrario */
    sortDescending(burst_time, process_name, process, &line_count);

    processors_count = 0;
    while (processors_count < n_cores)
    {
        int proc_start = 0, proc_end = 0;
        fprintf(f_out2, "Processador_%d\n", processors_count + 1);
        for (i = 0 + processors_count; i < line_count; i = i + n_cores)
        {
            proc_end = burst_time[i] + proc_start;
            fprintf(f_out2, "%s;%d;%d\n", process_name[i], proc_start, proc_end);
            proc_start = proc_end;
        }
        fprintf(f_out2, "\n");
        processors_count++;
    }

    fclose(f_out1);
    fclose(f_out2);
    return 0;
}
