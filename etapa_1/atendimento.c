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
int posicao = 0;

void *chegaGente();
void *menu();
void *atendimento();

int main()
{
    printf("Quantidade de cadeiras de espera : ");
    scanf("%d", &ncadeiras);

    cadeiras = (int *)malloc(sizeof(int) * ncadeiras);

    pthread_create(&(threads[0]), NULL, menu, NULL);
    pthread_create(&(threads[2]), NULL, atendimento, NULL);

    pthread_join(threads[0], NULL);

    free(cadeiras);
    return 0;
}

void *chegaGente()
{
    int aux = 0, complexidade;

    if (cadeiras[ncadeiras - 1] != 0)
    {
        printf("\n\033[0;31mTa lotado!\n");
        printf("\033[0m");
        return NULL;
    }
    printf("\nEntre complexidade : ");
    scanf("%d", &complexidade);
    cadeiras[posicao++] = complexidade;
    printf("\n\033[0;32mNovo cliente chegou\n");
    printf("\033[0m");
    return 0;
}

void *menu()
{
    int escolha;
    for (;;)
    {
        printf("Escolha a acao\n1: Entra 1 pessoa\n2: Encerra o programa\n");
        escolha = 0;
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            pthread_create(&(threads[1]), NULL, chegaGente, NULL);
            pthread_join(threads[1], NULL);
            break;
        case 2:
            pthread_cancel(threads[2]);
            return NULL;
            break;
        default:
            printf("entrou no default\n");
            break;
        }
    }
}

void *atendimento()
{
    while (true)
    {
        if (cadeiras[0] > 0)
        {
            gerente = ATENDENDO;
            printf("Iniciando atendimento (%ds)\n", cadeiras[0]);
            int ultimo_atendimento = cadeiras[0];
            for (int i = 0; i < ncadeiras - 1; i++)
                cadeiras[i] = cadeiras[i + 1];
            cadeiras[posicao--] = 0;
            usleep(ultimo_atendimento * 1000000);
            printf("Atendimento de (%ds) terminado\n", ultimo_atendimento);
        }
        else if (gerente == ATENDENDO)
        {
            gerente = CAFEZINHO;
            printf("\n     (  )   (   )  )\n      ) (   )  (  (\n      ( )  (    ) )\n      _____________\n     <_____________> ___\n     |             |/ _ \\\n     |               | | |\n     |               |_| |\n  ___|             |\\___/\n /    \\___________/    \\\n \\_____________________/\n");
        }
    }
}
