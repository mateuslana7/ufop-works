#include "Tarefa.h"
//Implementaçoes

//Inicializando uma tarefa
void Inicializar_Tar(TTarefa** tar)
{
	*tar = new TTarefa;
	setRecurso(*tar, 0);
	setDemanda(*tar, 0);
	setConclusao_TAR(*tar, 0);
}

//gets e sets para cada campo
//Recurso
int getRecurso(TTarefa* tar)
{
	return tar->recurso;
}
void setRecurso(TTarefa* tar, int recu)
{
	tar->recurso = recu;
}
//Demanda
double getDemanda(TTarefa* tar)
{
	return tar->demanda;
}
void setDemanda(TTarefa* tar, double qtd)
{
	tar->demanda = qtd;
}
//Concluido
int getConclusao_TAR(TTarefa* tar)
{
	return tar->concluido;
}
void setConclusao_TAR(TTarefa* tar, int num)
{
	tar->concluido = num;
}

//Executando as tarefas
void Executar_TAR(TTarefa* tar)
{
	tar->concluido = 1;
}