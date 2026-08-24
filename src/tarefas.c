#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/tarefas.h"
#include "../include/orquestrador.h"

int verificar_programa_existe(char *caminho_programa){
    if (access(caminho_programa, X_OK) == 0) {
        return 1;
    }
    return 0; 
}

int verificar_se_existe(Orquestrador *orq, char *nome_tarefa){
    if (nome_tarefa == NULL) {
    return 0;
    }
    for (int i = 0; i < orq->qtd_tarefas; i++) {
        if (strcmp(orq->tarefas[i].nome, nome_tarefa) == 0){
            return 1;
        }
    }
    return 0;
}

Tarefa* buscar_tarefa_por_nome(Orquestrador *orq, char *nome_tarefa) {
    if (nome_tarefa == NULL){
        return NULL;
    }

    for (int i = 0; i < orq->qtd_tarefas; i++) {
        if (strcmp(orq->tarefas[i].nome, nome_tarefa) == 0){
            return &orq->tarefas[i];
        }
    }
    return NULL;
}

void listar_tarefas(Orquestrador *orq) {

    if (orq == NULL || orq->qtd_tarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    for (int i = 0; i < orq->qtd_tarefas; i++) {

        printf("ID: %d\n", orq->tarefas[i].id);
        printf("Nome: %s\n", orq->tarefas[i].nome);
        printf("Programa: %s\n", orq->tarefas[i].comando);

        printf("Argumentos: ");

        for (int j = 0; j < orq->tarefas[i].qtd_argumentos; j++) {
            printf("%s ", orq->tarefas[i].argumentos[j]);
        }

        printf("\n\n");
    }
}