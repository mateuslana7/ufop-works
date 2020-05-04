#include "QuickSort.h"
//Implementaçao Recursiva

void Quick(TItem* v,unsigned long int* n_comp,unsigned long int* n_mov,int pos)
{
	Quick_Ordena(v,0,n-1,n_comp,n_mov,pos);
}

void Quick_Ordena(TItem* v,long int esq,long int dir,unsigned long int* n_comp,unsigned long int* n_mov,int pos)
{
	long int i,j;
	Particao(v,esq,dir,&i,&j,n_comp,n_mov,pos);
	if(esq<j)
	{
		Quick_Ordena(v,esq,j,n_comp,n_mov,pos);
	}
	if(i<dir)
	{
		Quick_Ordena(v,i,dir,n_comp,n_mov,pos);
	}
}

void Particao(TItem* v,long int esq,long int dir,long int *i,long int *j,unsigned long int *n_comp,unsigned long int *n_mov,int pos)
{
	TItem pivo,aux;
	*i=esq;
	*j=dir;
	pivo=v[(*i+*j)/2];
	do{
		while(!(pivo.chave<=v[*i].chave))
		{
			(*i)++;
			n_comp[pos]+=1;
		}
		while(pivo.chave<v[*j].chave)
		{
			(*j)--;
			n_comp[pos]+=1;
		}
		if(*i<=*j)
		{
			aux=v[*i];
			v[*i]=v[*j];
			v[*j]=aux;
			(*i)++;
			(*j)--;
			n_comp[pos]+=1;
			n_mov[pos]+=3;
		}
	}while(*i<=*j);
}