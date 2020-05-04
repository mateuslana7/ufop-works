#include "Exercicio03.h"

void Inicializar_Item(TItem** num)
{
	(*num) = new TItem[n];
}

void Copiar_Vetores(TItem* v,TItem* aux)
{
	long int i;
	for(i=0;i<n;i++)
	{
		aux[i].chave=v[i].chave;
	}
}

void Liberar_Memoria(TItem* num)
{
	delete []num;
}