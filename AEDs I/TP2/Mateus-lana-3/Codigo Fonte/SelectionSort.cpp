#include "SelectionSort.h"

void Selection(TItem* num,unsigned long int *n_comp,unsigned long int *n_mov,int pos)
{
	long int i,j,min;
	TItem aux;
	for(i=0;i<n-1;i++)
	{
		min=i;
		for(j=i+1;j<n;j++)
		{
			n_comp[pos]+=1;
			if(num[j].chave<num[min].chave)
			{
				min=j;
			}
			if(i!=min)
			{
				aux=num[min];
				num[min]=num[i];
				num[i]=aux;
				n_mov[pos]+=3;
			}
		}
	}
}