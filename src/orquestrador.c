#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tarefas.h"
#include "jobs.h"
#include "processos.h"
#include "orquestrador.h"

Orquestrador* criar_orquestrador() {
    Orquestrador *orq = malloc(sizeof(Orquestrador));

    if (orq == NULL) {
        return NULL;
    }

    orq->qtd_tarefas = 0;
    orq->qtd_jobs = 0;
    snprintf(orq->diretorio_trabalho, sizeof(orq->diretorio_trabalho), ".");

    return orq;
}

Job* start_tarefa(Orquestrador *orq, char *nome_tarefa) {
    if (orq == NULL || nome_tarefa == NULL) {
        return NULL;
    }

    Tarefa *tarefa = buscar_tarefa_por_nome(orq, nome_tarefa);
    if (tarefa == NULL) {
        return NULL;
    }

    pid_t pid = fork();

    if (pid < 0) {
        return NULL;
    }

    if (pid == 0) {
        executar_tarefa_simples(tarefa);
        exit(EXIT_FAILURE);
    }

    int job_id = orq->qtd_jobs + 1;
    return adicionar_job(orq, job_id, pid, nome_tarefa);
}
