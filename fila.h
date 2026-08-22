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

Fila *criar_fila();

int adicionar_tarefa(Fila *fila, Tarefa tarefa);

int remover_tarefa(Fila *fila, Tarefa *saida);

int fila_vazia(Fila *fila);

void liberar_fila(Fila *fila);