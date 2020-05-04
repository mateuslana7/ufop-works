#include "Processo.h"
//Implementaçoes

//Inicializando processo
void Inicializar_Proc(TProcesso** proc, int qtdTar)
{
	*proc = new TProcesso;
	setConclusao_PROC(*proc, 0);
	(*proc)->cont = 0;
	(*proc)->tarefas = new TTarefa*[qtdTar];
	(*proc)->comp = 0;
	(*proc)->tempo_PROC = 0;
	//setTarefas(*proc, 0);
	for (int i=0; i<tam; i++)
	{
		(*proc)->vet[i] = 0;
	}
	for (int j=0; j<qtdTar; j++)
	{
		Inicializar_Tar(&(*proc)->tarefas[j]);
	}
}

//Somando as demandas cada tipo
void Soma_Dem(TProcesso* proc, int t, double dem)
{
	proc->vet[t] += dem;
}

//Funçao que retorna a soma
double Resultado_Dem(TProcesso* proc, int t)
{
	return proc->vet[t];
}

//gets e sets para cada campo
//tarefas
TTarefa** getTarefas(TProcesso* proc)
{
	return proc->tarefas;
}
/*void setTarefas(TProcesso* proc, TTarefa** qtd)
{
	for (int i=0; i<qtd; i++)
	{
		proc->tarefas = qtd;
	}
}*/
//Concluido
int getConclusao_PROC(TProcesso* proc)
{
	return proc->concluido;
}
void setConclusao_PROC(TProcesso* proc, int num)
{
	proc->concluido = num;
}

//Adicionando tarefa
void AddTarefa(TProcesso* proc, TTarefa* tar)
{
	proc->tarefas[proc->cont]->recurso = tar->recurso;
	proc->tarefas[proc->cont]->demanda = tar->demanda;
	proc->cont += 1;
	Soma_Dem(proc, tar->recurso, tar->demanda);
	
}

//Executando tarefas
void Executar_PROC(TProcesso* proc)
{
	int i;
	for (i=0; i<(proc->cont); i++)
	{
		Executar_TAR(proc->tarefas[i]);
	}
	setConclusao_PROC(proc, 1);
}

//Liberando memoria
void liberarMemoria_PROC(TProcesso* proc, int qtd)
{
	int i;
	for (i=0; i<qtd; i++)
	{
		delete [] proc->tarefas[i];
	}
	delete proc->tarefas;
	delete proc;
}
