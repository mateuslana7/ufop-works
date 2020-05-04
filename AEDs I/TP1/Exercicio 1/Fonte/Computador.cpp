#include "Computador.h"
//Implementaçoes

//Inicializando computador
void Inicializar_PC(TComputador** PC, int nrec, int nproc)
{
	*PC = new TComputador;
	(*PC)->cont_REC = 0;
	(*PC)->num_REC = nrec;
	(*PC)->cont_PROC = 0;
	(*PC)->num_PROC = nproc;
	(*PC)->recursos = new TRecurso*[nrec];
	(*PC)->processos = new TProcesso*[nproc];
	(*PC)->tempoTotal = 0;
	
	for (int i=0; i<nrec; i++)
	{
		Inicializar_Rec(&(*PC)->recursos[i]);
	}
}

//Verificando se o computador suporta
int Verificar_Disp(TComputador* PC,int t, double dem)
{
	int d = 0;
	if(dem == 0)
	{
		return 1;
	}
	for(int i=0; i<PC->num_REC; i++)
	{
		if(PC->recursos[i]->tipo == t)
		{
			if(EstaDisponivel(PC->recursos[i], dem) == 1)
			{
				d = 1;
				break;
			}
		}			
	}
	return d;
}
//Adicionando recurso
void AddRecurso(TComputador* PC, TRecurso* rec)
{
	PC->recursos[PC->cont_REC] = rec;
	PC->cont_REC = PC->cont_REC + 1;
}

//Adicionando processo
void AddProcesso(TComputador* PC, TProcesso* vet)
{
	PC->processos[PC->cont_PROC] = vet;
	PC->cont_PROC += 1;
	for(int i=0; i<(vet->cont); i++)
	{
		TTarefa* aux = vet->tarefas[i];
		for(int j=0; j<(PC->num_REC); j++)
		{
			if(aux->recurso == PC->recursos[j]->tipo)
			{
				if((Reservar(PC->recursos[j],aux->demanda)))
				{
					//Se reservar sai do for
					break;
				}
			}
		}
	}
}

//Executando os processos
void Executar_PC(TComputador* PC, int id)
{
	int i, j, k;
	for (i=0; i<(PC->cont_PROC); i++)
	{
		double contTempo = 0;
		Executar_PROC(PC->processos[i]);
		for (j=0; j<PC->processos[i]->cont; j++)
		{
			TTarefa* aux = PC->processos[i]->tarefas[j];
			for(k=0; k<(PC->num_REC); k++)
			{
				if(aux->recurso == PC->recursos[k]->tipo)
				{
					if((Liberar_Rec(PC->recursos[k],aux->demanda)))
					{
						contTempo += CalcularTempo(PC->recursos[k],aux->demanda);
						//Se for possivel liberar, sai do laço
						break;
					}
				}
			}
			PC->processos[i]->tempo_PROC = contTempo;
		}
		PC->tempoTotal += PC->processos[i] ->tempo_PROC;
	}
}

//Liberando memoria

void liberarMemoria_PC(TComputador* PC, int qtd)
{
	int i;
	for (i=0; i<qtd; i++)
	{
		delete [] PC->recursos[i];
		delete [] PC->processos[i];
	}
	delete PC->recursos;
	delete PC->processos;
	delete PC;
}