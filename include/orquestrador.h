#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


typedef enum {
    SEQUENCIAL,
    PARALELO,
    PIPE
} TipoExecucao;

typedef struct Job {
    int job_id;
    int pid;
    char *nome_tarefa;
} Job;

typedef struct Orquestrador {
    Tarefa tarefas[100];
    int qtd_tarefas;
    
    Job jobs[100];
    int qtd_jobs;
    
    char diretorio_trabalho[256];
} Orquestrador;

Orquestrador* criar_orquestrador();

int cadastrar_tarefa(Orquestrador *orq, char *nome, char *programa, char **argumentos, int qtd_args);

int executar(Orquestrador *orq, TipoExecucao tipo, char **nomes_tarefas, int qtd_tarefas);

int mudar_diretorio(Orquestrador *orq, char *novo);

Job* start_tarefa(Orquestrador *orq, char *nome);

void listar_jobs(Orquestrador *orq);

int aguardar_job(Orquestrador *orq, int ID);

int redirecionar(Orquestrador *orq, char *nome_tarefa, char *tipo, char *arquivo);