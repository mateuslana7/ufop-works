#include "MergeSort.h"
//Implementaçao Recursiva

void Merge(TItem* v,unsigned long int* n_comp,unsigned long int* n_mov,int pos)
{
	Merge_Ordena(v,0,n-1,n_comp,n_mov,pos);
}

void Merge_Ordena(TItem* v,long int esq,long int dir,unsigned long int* n_comp,unsigned long int* n_mov,int pos)
{
	if(esq>=dir)
	{
		return;
	}
	int meio= (esq + dir)/2;
	Merge_Ordena(v,esq,meio,n_comp,n_mov,pos);
	Merge_Ordena(v,meio+1,dir,n_comp,n_mov,pos);
	Intercala(v,esq,meio,dir,n_comp,n_mov,pos);
	return;
}

void Intercala(TItem* v,long int esq,long int meio,long int dir,unsigned long int *n_comp,unsigned long int *n_mov,int pos)
{
	long int i,j,k;
	TItem* a;
	TItem* b;
	long int a_tam = meio -esq+1;
	long int b_tam = dir - meio;
	a = new TItem[a_tam];
	b = new TItem[b_tam];
	for(i=0;i<a_tam;i++)
	{
		a[i]=v[i+esq];
	}
	for(i=0;i<b_tam;i++)
	{
		b[i]=v[i+meio+1];
	}
	for(i=0,j=0,k=esq;k<=dir;k++)
	{
		if(i==a_tam)
		{
			v[k]=b[j++];
			n_comp[pos]+=1;
		}
		else
		{		
			if(j==b_tam)
			{
				v[k]=a[i++];
				n_comp[pos]+=1;
			}
			else
			{
				n_comp[pos]+=1;
				if(a[i].chave<b[j].chave)
				{
					v[k]=a[i++];
					n_mov[pos]+=1;	
				}
				else
				{
					v[k]=b[j++];
					n_mov[pos]+=1;
				}
			}
		}
	}
	delete []a;
	delete []b;
}