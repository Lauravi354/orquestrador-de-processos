#ifndef JOBS_H
#define JOBS_H
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "orquestrador.h"

Job* adicionar_job(Orquestrador *orq, int job_id, int pid, char *nome_tarefa);

int remover_job(Orquestrador *orq, int job_id);

Job* buscar_job_por_id(Orquestrador *orq, int job_id);

void listar_jobs(Orquestrador *orq);

int aguardar_job(Orquestrador *orq, int job_id);

#endif