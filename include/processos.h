#ifndef PROCESSOS_H
#define PROCESSOS_H
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "orquestrador.h"

void executar_tarefa_simples(Tarefa *tarefa);
int executar_sequencial(Orquestrador *orq, char **nomes_tarefas, int qtd);
int executar_paralelo(Orquestrador *orq, char **nomes_tarefas, int qtd);
int executar_pipe(Orquestrador *orq, char **nomes_tarefas, int qtd);

#endif