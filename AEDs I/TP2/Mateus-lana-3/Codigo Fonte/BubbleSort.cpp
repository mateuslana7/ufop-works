#include "BubbleSort.h"

void Bubble(TItem* num,unsigned long int *n_comp,unsigned long int *n_mov,int pos)
{
	long int i,j;
	int troca;
	TItem aux;
	for(i=0;i<n-1;i++)
	{
		troca=0;
		for(j=1;j<n-i;j++)
		{
			n_comp[pos]+=1;
			if(num[j].chave<num[j-1].chave)
			{
				aux=num[j];
				num[j]=num[j-1];
				num[j-1]=aux;
				troca++;
				n_mov[pos]+=3;
			}
		}
		if(troca==0)
		{
			break;
		}
	}
}