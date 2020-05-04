#ifndef COMPUTADOR_H
#define COMPUTADOR_H

#include "Recurso.h"
#include "Processo.h"

typedef struct
{
	TRecurso** recursos;
	TProcesso** processos;
	//Campos para cauculos e saida
	int cont_REC, num_REC, cont_PROC, num_PROC;
	double tempoTotal;
}TComputador;

//Cabeçalhos
//Inicializando um computador
void Inicializar_PC(TComputador**, int, int);

//Verificando se o computador suporta
int Verificar_Disp(TComputador*, int, double);

//Adicionando recursos e processos
void AddRecurso(TComputador*, TRecurso*);
void AddProcesso(TComputador*, TProcesso*);

//Executando os processos
void Executar_PC(TComputador*, int);

//liberando 
void liberarMemoria_PC(TComputador*, int);

#endif