#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

Fila *criar_fila(){
    Fila *fila = (Fila*)malloc(sizeof(Fila));

    if (fila == NULL) {
    return NULL;
    }

    else{
        fila->inicio = NULL;
        fila->fim = NULL;
        fila->qnt = 0;
    }

    return fila;
}