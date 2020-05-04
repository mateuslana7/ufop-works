#ifndef RECURSO_H
#define RECURSO_H

#include <iostream>
typedef struct 
{
	int tipo;
	double capacidade;
	double EmUso;
	double velocidade;
}TRecurso;
//Cabeçalhos
//Inicalizando um recurso
void Inicializar_Rec(TRecurso**);

//Gets e sets de cada campo
int getTipo(TRecurso*);
void setTipo(TRecurso*,int);

double getCapacidade(TRecurso*);
void setCapacidade(TRecurso*,double);

double getEmUso(TRecurso*);
void setEmUso(TRecurso*,double);

double getVelocidade(TRecurso*);
void setVelocidade(TRecurso*,double);

//Outras 
int EstaDisponivel(TRecurso*, double);
int Reservar(TRecurso*, double);
int Liberar_Rec(TRecurso*, double);
double CalcularTempo(TRecurso*, double);

//liberando memoria alocada
void LiberarMemoria (TRecurso*);

#endif