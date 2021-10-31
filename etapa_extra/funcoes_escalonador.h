#ifndef FUNCOES_ESCALONADOR
#define FUNCOES_ESCALONADOR

void ordenaCrescente(int *tempo_execucao, char (*nome_processos)[10], int *processo, int *num_linhas);
void ordenaDecrescente(int *tempo_execucao, char (*nome_processos)[10], int *processo, int *num_linhas);
FILE *separaAsTarefasImprimeArquivo(int *tempo_execucao, char (*nome_processos)[10], int *num_linhas, int n_nucleos, const char *nome_arquivo);

#endif