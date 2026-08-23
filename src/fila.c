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

int adicionar_tarefa(Fila *fila, Tarefa tarefa){

    if (fila == NULL) {
        return -1;
    }

    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));

    if (novo == NULL){
        return -1;
    }
    else{
        novo->tarefa = tarefa;
        novo->next = NULL;
    
        if (fila->inicio == NULL){
            fila->inicio = novo;
        }
    
        else{
            fila->fim->next = novo;
        }
    
        fila->fim = novo;
        fila->qnt++;
        
        return 0;
    }
}

int remover_tarefa(Fila *fila, Tarefa *saida){

    if (fila == NULL || saida == NULL){
        return -1;
    }

    if (fila->inicio == NULL){
        return -1;
    }

    Elemento *aux = fila->inicio;
    *saida = aux->tarefa;
    fila->inicio = fila->inicio->next;

    if (fila->inicio == NULL){
        fila->fim = NULL;
    }

    fila->qnt--;
    free(aux);
    return 0;
}

int fila_vazia(Fila *fila){
    if (fila == NULL || fila->inicio == NULL){
        return 1;
    }
    return 0;
}