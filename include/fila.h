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
    char *arquivo_entrada;
    char *arquivo_saida;
    int modo_saida;

} Tarefa;

typedef struct Elemento{
    Tarefa tarefa;
    Elemento *next;
}Elemento;

typedef struct Fila{
    Elemento *inicio;
    Elemento *fim;
    int qnt;
}Fila;

Fila *criar_fila();

int adicionar_tarefa(Fila *fila, Tarefa tarefa);

int remover_tarefa(Fila *fila, Tarefa *saida);

int fila_vazia(Fila *fila);

void liberar_fila(Fila *fila);