#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include <pthread.h>

typedef struct Orquestrador {
    Fila *fila;
    pthread_mutex_t lock;
} Orquestrador;