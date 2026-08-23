#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

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
