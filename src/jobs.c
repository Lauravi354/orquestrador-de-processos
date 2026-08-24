#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/jobs.h"
#include "../include/orquestrador.h"

Job* buscar_job_por_id(Orquestrador *orq, int job_id) {

    if (orq == NULL || job_id < 0) {
        return NULL;
    }

    for (int i = 0; i < orq->qtd_jobs; i++) {

        if (orq->jobs[i].job_id == job_id) {
            return &orq->jobs[i];
        }
    }

    return NULL;
}

void listar_jobs(Orquestrador *orq) {
    if (orq == NULL || orq->qtd_jobs == 0) {
        printf("Nenhum job cadastrado.\n");
        return;
    }

    for (int i = 0; i < orq->qtd_jobs; i++) {
        printf("[%d] %d %s\n",
               orq->jobs[i].job_id,
               orq->jobs[i].pid,
               orq->jobs[i].nome_tarefa);
    }
}

Job* adicionar_job(Orquestrador *orq, int job_id, int pid, char *nome_tarefa) {
    if (orq == NULL || nome_tarefa == NULL) {
        return NULL;
    }

    if (orq->qtd_jobs >= 100) {
        return NULL;
    }

    int i = orq->qtd_jobs;

    orq->jobs[i].job_id = job_id;
    orq->jobs[i].pid = pid;
    orq->jobs[i].nome_tarefa = nome_tarefa;

    orq->qtd_jobs++;

    return &orq->jobs[i];
}