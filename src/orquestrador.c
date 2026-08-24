#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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

int cadastrar_tarefa(Orquestrador *orq, char *nome, char *programa, char **argumentos, int qtd_args) {
    if (orq == NULL || nome == NULL || programa == NULL) {
        return -1;
    }

    if (orq->qtd_tarefas >= 100) {
        return -1;
    }

    int i = orq->qtd_tarefas;

    orq->tarefas[i].id = i;
    orq->tarefas[i].nome = strdup(nome);
    orq->tarefas[i].comando = strdup(programa);
    orq->tarefas[i].qtd_argumentos = qtd_args;
    orq->tarefas[i].status = AGUARDANDO;
    orq->tarefas[i].arquivo_entrada = NULL;
    orq->tarefas[i].arquivo_saida = NULL;

    if (qtd_args > 0) {
        orq->tarefas[i].argumentos = malloc(qtd_args * sizeof(char*));
        for (int j = 0; j < qtd_args; j++) {
            orq->tarefas[i].argumentos[j] = strdup(argumentos[j]);
        }
    } else {
        orq->tarefas[i].argumentos = NULL;
    }

    orq->qtd_tarefas++;
    return 0;
}