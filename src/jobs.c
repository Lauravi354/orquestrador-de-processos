#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/jobs.h"
#include "../include/orquestrador.h"
#include <sys/wait.h>

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

int remover_job(Orquestrador *orq, int job_id) {
    if (orq == NULL) {
        return -1;
    }

    for (int i = 0; i < orq->qtd_jobs; i++) {
        if (orq->jobs[i].job_id == job_id) {

            for (int j = i; j < orq->qtd_jobs - 1; j++) {
                orq->jobs[j] = orq->jobs[j + 1];
            }

            orq->qtd_jobs--;

            return 0;
        }
    }

    return -1;
}

int aguardar_job(Orquestrador *orq, int job_id) {
    if (orq == NULL) {
        return -1;
    }

    Job *job = buscar_job_por_id(orq, job_id);

    if (job == NULL) {
        return -1;
    }

    if (waitpid(job->pid, NULL, 0) == -1) {
        return -1;
    }

    return remover_job(orq, job_id);
}