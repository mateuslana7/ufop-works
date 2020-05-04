#include "Recurso.h"
//Implementaçoes

//Inicializando um recurso
void Inicializar_Rec(TRecurso** rec)
{
	*rec = new TRecurso;
	setTipo(*rec, 0);
	setCapacidade(*rec, 0);
	setEmUso(*rec, 0);
	setVelocidade(*rec, 0);
}

//gets e sets para cada campo
//Tipo
int getTipo(TRecurso* rec)
{
	return rec->tipo;
}
void setTipo(TRecurso* rec, int tipo)
{
	rec->tipo = tipo;
}
//Capacidade
double getCapacidade(TRecurso* rec)
{
	return rec->capacidade;
}
void setCapacidade(TRecurso* rec, double cpcd)
{
	rec->capacidade = cpcd;
}
//EmUso
double getEmUso(TRecurso* rec)
{
	return rec->EmUso;
}
void setEmUso(TRecurso* rec, double qtd)
{
	rec->EmUso = qtd;
}
//Velocidade
double getVelocidade(TRecurso* rec)
{
	return rec->velocidade;
}
void setVelocidade(TRecurso* rec, double vel)
{
	rec->velocidade = vel;
}

//Outras implementaçoes
int EstaDisponivel(TRecurso* rec, double dem)
{
	if (rec->tipo == 1)//Verifica se é CPU
	{	
		if (rec->capacidade - rec->EmUso > 0)//Ver se a CPU ta disponivel
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if ((rec->capacidade - rec->EmUso) >= dem)//Caso nao seja CPU
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int Reservar(TRecurso* rec, double dem)
{
	if (rec->tipo == 1)//Verifica se é CPU
	{
		if ((rec->capacidade - rec->EmUso) > 0)
		{
			rec->EmUso += 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if ((rec->capacidade - rec->EmUso) >= dem)
	{
		rec->EmUso += dem;
		return 1;
	}
	else
	{
		return 0;
	}
}
int Liberar_Rec(TRecurso* rec, double dem)
{
	if (rec->EmUso >= dem)
	{
		rec->EmUso -= dem;
		return 1;
	}
	else
	{
		return 0;
	}
}
double CalcularTempo(TRecurso* rec, double dem)
{
	return rec->velocidade * dem;
}

//Liberando memoria alocada
void LiberarMemoria (TRecurso* rec)
{
	delete rec;
}
