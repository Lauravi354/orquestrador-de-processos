#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orquestrador.h"

int main() {
    Orquestrador *orq = criar_orquestrador();

    if (orq == NULL) {
        return 1;
    }

    char linha[1024];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break;
        }

        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) == 0) {
            continue;
        }

        char *args[100];
        int qtd = 0;

        char *token = strtok(linha, " ");

        while (token != NULL && qtd < 100) {
            args[qtd++] = token;
            token = strtok(NULL, " ");
        }

        if (qtd == 0) {
            continue;
        }

        if (strcmp(args[0], "task") == 0) {
            if (qtd < 3) {
                printf("Uso: task <nome> <programa> [argumentos...]\n");
                continue;
            }

            printf("Comando task reconhecido.\n");

        } else if (strcmp(args[0], "run") == 0) {
            if (qtd < 2) {
                printf("Uso: run <tarefa>\n");
                continue;
            }

            if (executar(orq, SEQUENCIAL, &args[1], qtd - 1) != 0) {
                printf("Erro ao executar tarefa.\n");
            }

        } else if (strcmp(args[0], "start") == 0) {
            if (qtd != 2) {
                printf("Uso: start <tarefa>\n");
                continue;
            }

            Job *job = start_tarefa(orq, args[1]);

            if (job != NULL) {
                printf("Job iniciado: %d\n", job->job_id);
            } else {
                printf("Erro ao iniciar tarefa.\n");
            }

        } else if (strcmp(args[0], "jobs") == 0) {
            listar_jobs(orq);

        } else if (strcmp(args[0], "wait") == 0) {
            if (qtd != 2) {
                printf("Uso: wait <id>\n");
                continue;
            }

            int id = atoi(args[1]);

            if (aguardar_job(orq, id) != 0) {
                printf("Erro ao aguardar job.\n");
            }

        } else if (strcmp(args[0], "exit") == 0) {
            break;

        } else {
            printf("Comando desconhecido.\n");
        }
    }

    liberar_orquestrador(orq);

    return 0;
}