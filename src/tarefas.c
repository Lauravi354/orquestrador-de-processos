#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int verificar_programa_existe(char *caminho_programa){
    if (access(caminho_programa, X_OK) == 0) {
        return 1;
    }
    return 0; 
}