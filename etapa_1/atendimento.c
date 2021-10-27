#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#define ATENDENDO 1
#define CAFEZINHO 0

pthread_t threads[3];

int ncadeiras;
int *cadeiras;
bool gerente;
int posicao;

void *menu()
{
    int escolha;
    for (;;)
    {
        printf("Escolha a acao\n1: Entra 1 pessoa\n2: Encerra o programa\n");

        scanf("%d", &escolha);

        switch (escolha)
        {
            case 1:
                pthread_join(threads[2], NULL);
                break;
            case 2:
                return NULL;
                break;
            default:
                break;
        }
    }
}

void *atendimento()
{

    if (cadeiras[0] > 0)
    {
        gerente = ATENDENDO;
        for(int i = 0; i < ncadeiras - 2; i++) 
            cadeiras[i] = cadeiras[i + 1];
        cadeiras[posicao--] = 0;
        printf("Iniciando atendimento (%ds)\n", cadeiras[0]);
        sleep(cadeiras[0] * 1000);
        printf("Atendimento terminado\n");
    }
    else
    {
        gerente = CAFEZINHO;
        printf("\n     (  )   (   )  )\n      ) (   )  (  (\n      ( )  (    ) )\n      _____________\n     <_____________> ___\n     |             |/ _ \\\n     |               | | |\n     |               |_| |\n  ___|             |\\___/\n /    \\___________/    \\\n \\_____________________/\n");
    }
}

void *chegaGente()
{
    int aux = 0, complexidade;

    if (cadeiras[ncadeiras - 1] != 0)
    {
        printf("\033[0;31mTa lotado!\n");
        printf("\033[0m");
        return NULL;
    }
    printf("\nEntre complexidade : ");
    scanf("%d", &complexidade);
    cadeiras[++posicao] = complexidade;
    printf("\033[0;32mNovo cliente chegou\n");
    printf("\033[0m");
}

int main()
{
    int posicao = 0;
    printf("Quantidade de cadeiras: ");
    scanf("%d", &ncadeiras);

    cadeiras = (int *)malloc(sizeof(int) * ncadeiras);

    pthread_create(&(threads[0]), NULL, atendimento, NULL);
    pthread_create(&(threads[1]), NULL, menu, NULL);
    pthread_create(&(threads[2]), NULL, chegaGente, NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);

    free(cadeiras);

    return 0;
}