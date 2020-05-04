#include "ShellSort.h"

void Shell(TItem* num,unsigned long int* n_comp,unsigned long int* n_mov,int pos)
{
	long int i,j,h;
	TItem aux;

	/*Sequencia de KNUTH-1973!!!
	1,4,13,40,121...*/
	
	for(h=1;h<n;h=3*h+1);
	do{
		h=(h-1)/3;
		for(i=h;i<n;i++)
		{
			aux=num[i];
			j=i;
			n_mov[pos]+=1;
			n_comp[pos]+=1;
			while(num[j-h].chave>aux.chave)
			{
				n_mov[pos]+=1;
				num[j]=num[j-h];
				j-=h;
				if(j<h)
				{
					break;
				}
			}
			num[j]=aux;
			n_mov[pos]+=1;
		}
	}while(h!=1);
}