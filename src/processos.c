#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/wait.h>

void executar_tarefa_simples(Tarefa *tarefa) {
    if (tarefa == NULL) {
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        int fd;

        if (tarefa->arquivo_entrada != NULL) {
            fd = open(tarefa->arquivo_entrada, O_RDONLY);

            if (fd == -1) {
                exit(1);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (tarefa->arquivo_saida != NULL) {
            fd = open(tarefa->arquivo_saida, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd == -1) {
                exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        char *argv[tarefa->qtd_argumentos + 2];

        argv[0] = tarefa->comando;

        for (int i = 0; i < tarefa->qtd_argumentos; i++) {
            argv[i + 1] = tarefa->argumentos[i];
        }

        argv[tarefa->qtd_argumentos + 1] = NULL;

        execvp(tarefa->comando, argv);

        exit(1);

    } else if (pid > 0) {
        waitpid(pid, NULL, 0);

    } else {
        return;
    }
}