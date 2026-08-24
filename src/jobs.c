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