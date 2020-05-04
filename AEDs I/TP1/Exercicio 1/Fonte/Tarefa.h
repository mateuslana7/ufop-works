#ifndef TAREFA_H
#define TAREFA_H

#include "Recurso.h"
typedef struct
{
	int recurso;
	double demanda;
	int concluido;
}TTarefa;
//Cabeçalhos
//Incializando uma tarefa
void Inicializar_Tar(TTarefa**);

//Gets e sets para cada campo
int getRecurso(TTarefa*);
void setRecurso(TTarefa*,int);

double getDemanda(TTarefa*);
void setDemanda(TTarefa*,double);

int getConclusao_TAR(TTarefa*);
void setConclusao_TAR(TTarefa*,int);

//Executando as tarefas
void Executar_TAR(TTarefa*);

#endif