#ifndef PROCESSO_H
#define PROCESSO_H

#define tam 3

#include "Recurso.h"
#include "Tarefa.h"
typedef struct
{
	TTarefa** tarefas;
	int concluido;
	//Campos de verificaçao do sistema
	int cont, vet[tam], comp;
	double tempo_PROC;
}TProcesso;
//Cabeçalhos
//Inicializa processo
void Inicializar_Proc(TProcesso**, int);
void Soma_Dem(TProcesso*, int, double);
double Resultado_Dem(TProcesso*, int);

//Gets e sets para cada campo
TTarefa** getTarefas(TProcesso*);
void setTarefas(TProcesso*,TTarefa**);

int getConclusao_PROC(TProcesso*);
void setConclusao_PROC(TProcesso*,int);

//Adiciona uma tarefa ao processo
void AddTarefa(TProcesso*,TTarefa*);

//Executa as tarefas do processo
void Executar_PROC(TProcesso*);

//Liberando memoria
void liberarMemoria_PROC(TProcesso*,int);

#endif