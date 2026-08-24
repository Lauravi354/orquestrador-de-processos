#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orquestrador.h"

static void processar_linha(Orquestrador *orq, char *linha, int *deve_sair) {

    linha[strcspn(linha, "\n")] = '\0';

    if (strlen(linha) == 0) {
        return;
    }

    char *args[100];
    int qtd = 0;

    char *token = strtok(linha, " ");
    while (token != NULL && qtd < 100) {
        args[qtd++] = token;
        token = strtok(NULL, " ");
    }

    if (qtd == 0) {
        return;
    }

    if (strcmp(args[0], "task") == 0) {
        if (qtd < 3) {
            printf("Uso: task <nome> <programa> [argumentos...]\n");
            return;
        }

        char *nome = args[1];
        char *programa = args[2];
        char **argumentos = (qtd > 3) ? &args[3] : NULL;
        int qtd_args = qtd - 3;

        if (cadastrar_tarefa(orq, nome, programa, argumentos, qtd_args) != 0) {
            printf("Erro ao cadastrar tarefa.\n");
        }

    } else if (strcmp(args[0], "run") == 0) {
    printf("Comando 'run' nao implementado nesta entrega.\n");

    } else if (strcmp(args[0], "input") == 0 || strcmp(args[0], "output") == 0 || strcmp(args[0], "append") == 0) {
        printf("Redirecionamento (%s) nao implementado nesta entrega.\n", args[0]);

    } else if (strcmp(args[0], "workdir") == 0) {
        printf("Comando 'workdir' nao implementado nesta entrega.\n");

    } else if (strcmp(args[0], "start") == 0) {
            if (qtd != 2) {
        printf("Uso: start <tarefa>\n");
        return;
    }

        Job *job = start_tarefa(orq, args[1]);

        if (job != NULL) {
            printf("[%d] %d\n", job->job_id, job->pid);
        } else {
            printf("Erro ao iniciar tarefa '%s'.\n", args[1]);
        }

    } else if (strcmp(args[0], "jobs") == 0) {
        listar_jobs(orq);

    } else if (strcmp(args[0], "wait") == 0) {
        if (qtd != 2) {
            printf("Uso: wait <id>\n");
            return;
        }

        int id = atoi(args[1]);

        if (aguardar_job(orq, id) != 0) {
            printf("Erro ao aguardar job %d.\n", id);
        }

    } else if (strcmp(args[0], "exit") == 0) {
        *deve_sair = 1;

    } else {
        printf("Comando desconhecido: %s\n", args[0]);
    }
}

int main(int argc, char *argv[]) {

    if (argc > 2) {
        fprintf(stderr, "Uso: %s [workflowFile]\n", argv[0]);
        return 1;
    }

    Orquestrador *orq = criar_orquestrador();

    if (orq == NULL) {
        fprintf(stderr, "Erro ao inicializar o orquestrador.\n");
        return 1;
    }

    char linha[1024];
    int deve_sair = 0;

    if (argc == 2) {
        
        FILE *arquivo = fopen(argv[1], "r");

        if (arquivo == NULL) {
            fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'.\n", argv[1]);
            free(orq);
            return 1;
        }

        while (!deve_sair && fgets(linha, sizeof(linha), arquivo) != NULL) {
            char copia[1024];
            strncpy(copia, linha, sizeof(copia));
            copia[sizeof(copia) - 1] = '\0';
            copia[strcspn(copia, "\n")] = '\0';

            printf("%s\n", copia);

            processar_linha(orq, linha, &deve_sair);
        }

        fclose(arquivo);

    } else {
        
        while (!deve_sair) {
            printf("processflow> ");
            fflush(stdout);

            if (fgets(linha, sizeof(linha), stdin) == NULL) {
                printf("\n");
                break;
            }

            processar_linha(orq, linha, &deve_sair);
        }
    }

    free(orq);

    return 0;
}