#include <string.h>

void sortAscending(int *burst_time, char (*process_name)[10], int *process, int *line_count) 
{
    int pos, temp = 0;

    int number_of_processes = *line_count;

    int i, j;
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
}

void sortDescending(int *burst_time, char (*process_name)[10], int *process, int *line_count) 
{
    int pos, temp = 0;
    int number_of_processes = *line_count;

    int i, j;
    char temps[20];
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
}