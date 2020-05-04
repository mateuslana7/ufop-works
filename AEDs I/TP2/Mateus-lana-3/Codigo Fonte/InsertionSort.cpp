#include "InsertionSort.h"

void Insertion(TItem* num,unsigned long int *n_comp,unsigned long int *n_mov,int pos)
{
	long int i,j;
	TItem aux;
	//Implementação sem sentinela.
	for(i=1;i<n;i++)
	{
		aux=num[i];
		j=i-1;
		if(aux.chave>num[j].chave)
		{
			n_comp[pos]+=1;
		}
		while(j>=0 && aux.chave<num[j].chave)
		{
			num[j+1]=num[j];
			j--;
			n_comp[pos]+=1;
			n_mov[pos]+=1;
		}
		num[j+1]=aux;
	}
}
