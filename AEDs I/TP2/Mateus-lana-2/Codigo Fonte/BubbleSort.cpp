#include "BubbleSort.h"

void Bubble(string *vet,int tam)
{
	int i,j,tam1,tam2;
	string aux;
	for (i=0; i<tam-1; i++)
	{
		for (j=1; j<tam-i; j++)
		{
			//Verificaçao para palavras
			if (isalpha(vet[j][0]))
			{
				if (tolower(vet[j][0])==tolower(vet[j-1][0]))
				{
					if (tolower(vet[j][1])==tolower(vet[j-1][1]))
					{
						if (tolower(vet[j][2])==tolower(vet[j-1][2]))
						{
							if (tolower(vet[j][3])<tolower(vet[j-1][3]))
							{
								aux=vet[j];
								vet[j]=vet[j-1];
								vet[j-1]=aux;
							}
						}
						else
						{
							if (tolower(vet[j][2])<tolower(vet[j-1][2]))
							{
								aux=vet[j];
								vet[j]=vet[j-1];
								vet[j-1]=aux;
							}
						}
					}
					else
					{
						if (tolower(vet[j][1])<tolower(vet[j-1][1]))
						{
							aux=vet[j];
							vet[j]=vet[j-1];
							vet[j-1]=aux;
						}	
					}
				}
				else
				{
					if (tolower(vet[j][0])<tolower(vet[j-1][0]))
					{
						aux=vet[j];
						vet[j]=vet[j-1];
						vet[j-1]=aux;
					}
				}
			}
			//Verificaçao para numeros
			else
			{
				tam1=vet[j-1].size();
				tam2=vet[j].size();
				
				if (ispunct(vet[j-1][0]) || ispunct(vet[j][0]))
				{
					if (vet[j]<vet[j-1])
					{
						aux=vet[j];
						vet[j]=vet[j-1];
						vet[j-1]=aux;
					}
				}
				else
				{
					if (tam1==tam2)
					{
						if (vet[j]<vet[j-1])
						{
							aux=vet[j];
							vet[j]=vet[j-1];
							vet[j-1]=aux;
						}
					}
					else
					{
						if (tam1>tam2)
						{
							aux=vet[j-1];
							vet[j-1]=vet[j];
							vet[j]=aux;
						}
					}
				}
			}
		}
	}
}