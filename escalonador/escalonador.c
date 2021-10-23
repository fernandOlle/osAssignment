#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*int cmpAscending(int *a, int *b) {
    if (a == b) 
        return;

    return *a < *b;
}

int cmpDescending(int *a, int *b) {
    if (a == b) 
        return;

    return *a > *b;
}

void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}*/

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

    // if (!access(argv[1], R_OK)){
    //     fprintf(stderr, "File not found.\n");
    //     exit(1);
    // }

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

    // printf("Enter number of process:");
    // scanf("%d", &n);

    // printf("\nEnter Burst Time:\n");
    // for (i = 0; i < n; i++) {
    //     printf("%d:", i + 1);
    //     scanf("%d", &burst_time[i]);
    //     p[i] = i + 1;
    // }
    number_of_processes = line_count;

    //sorting of burst times
    i = 0, j = 0;
    char temps[20];
    for (i = 0; i < number_of_processes; i++)
    {
        pos = i;
        for (j = i + 1; j < number_of_processes; j++)
        {
            if (burst_time[j] < burst_time[pos])
                pos = j;
        }

        temp = burst_time[i];
        burst_time[i] = burst_time[pos];
        burst_time[pos] = temp;

        strcpy(temps, process_name[i]);
        strcpy(process_name[i], process_name[pos]);
        strcpy(process_name[pos], temps);

        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }

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
    //sorting of burst times
    i = 0, j = 0;
    for (i = 0; i < number_of_processes; i++)
    {
        pos = i;
        for (j = i + 1; j < number_of_processes; j++)
        {
            if (burst_time[j] > burst_time[pos])
                pos = j;
        }

        temp = burst_time[i];
        burst_time[i] = burst_time[pos];
        burst_time[pos] = temp;

        strcpy(temps, process_name[i]);
        strcpy(process_name[i], process_name[pos]);
        strcpy(process_name[pos], temps);

        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }

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

/* aqui printa ao contrario */
    // processors_count = 0;
    // while (processors_count < n_cores)
    // {
    //     int proc_start = 0, proc_end = 0;
    //     fprintf(f_out2, "Processador_%d\n", processors_count + 1);
    //     for (i = line_count - processors_count - 1; i >= 0; i = i - n_cores)
    //     {
    //         proc_end = burst_time[i] + proc_start;
    //         fprintf(f_out2, "%s;%d;%d\n", process_name[i], proc_start, proc_end);
    //         printf("%s;%d;%d\n", process_name[i], proc_start, proc_end);
    //         proc_start = proc_end;
    //     }
    //     fprintf(f_out2, "\n");
    //     processors_count++;
    // }

    fclose(f_out1);
    fclose(f_out2);
    return 0;
}
