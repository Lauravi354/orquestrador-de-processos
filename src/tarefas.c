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