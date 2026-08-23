#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "orquestrador.h"

Tarefa* buscar_tarefa_por_nome(Orquestrador *orq, char *nome_tarefa);

int verificar_se_existe(Orquestrador *orq, char *nome_tarefa);

int verificar_programa_existe(char *caminho_programa);

void listar_tarefas(Orquestrador *orq);