#include <stdio.h>
#include <stdlib.h>

typedef enum {
    AGUARDANDO,
    EXECUTANDO,
    FINALIZADA,
} Status;

typedef struct Tarefa {
    int id;
    char *nome;
    char *comando;
    char **argumentos;

    int qtd_argumentos;

    Status status;

    double tempo_execucao;

    int *dependencias;
    int qtd_dependencias;

} Tarefa;

typedef struct Elemento{
    Tarefa tarefa;
    Elemento *next;
}Elemento;

typedef struct Fila{
    Elemento *incio;
    Elemento *fim;
    int *qnt;
}fila;

