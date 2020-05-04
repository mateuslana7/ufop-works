#include "Exercicio02.h"

bool Verifica_Pontuacao(string *lista)
{
	int i,tam;
	tam = (*lista).size();
	for (i=0; i<tam; i++)
	{
		if((*lista)[i]=='.')
		{
			return true;
		}
	}
	return false;
}

void OrdenacaoMexida(string *vet1,string *vet2,string *vet3,int *v4,int cont)
{
	int i,j,k;
	for (i=0, j=0, k=0; i<cont; i++)
	{
		if (v4[i]==1)
		{
			vet1[i]=vet2[j++];
		}
		else
		{
			vet1[i]=vet3[k++];
		}
	}
}

void Extrair(string *vet,string lista)
{
	int i,j,k,tam,cont=0,inicio=0;
	tam=lista.size();
	//Extrai numeros e palavras da lista e coloca em um vetor
	for (i=0, j=1, k=0; i<tam; i++, j++)
	{
		cont++;
		if (lista[i]==',')
		{
			if (lista[j]==' ')
			{
				vet[k++]=lista.substr(inicio,cont-1);
				inicio=j+1;
				cont=-1;
			}
		}
	}
	vet[k]=lista.substr(inicio,cont-1);
}

void Separar(string *vet,string *vet2,string *vet3,int cont)
{
	//Separando em 2 vetores diferentes um de palavras e outro de numeros
	int i,j,k;
	for (i=0, j=0, k=0; i<cont; i++)
	{
		if (isalpha(vet[i][0]))
		{
			vet2[j++]=vet[i];
		}
		else
		{
			vet3[k++]=vet[i];
		}
	}
}

void Imprime(string *v, int cont)
{
	cout<<endl<<endl<<"Lista ordenada: ";
	int i;
	for (i=0; i<cont; i++)
	{
		if (i!=cont-1)
		{
			cout<<v[i]<<", ";
		}
		else
		{
			cout<<v[i]<<".";
		}
	}
	cout<<endl<<endl;
}