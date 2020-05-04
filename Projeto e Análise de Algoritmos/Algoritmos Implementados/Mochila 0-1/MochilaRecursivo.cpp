//Problema da Mochila - Algoritmo Recursivo
#include <iostream>
#include <cmath>
using namespace std;
//CONSIDERANDO O VETOR ORDENADO

typedef struct Item
{
	double valor;
	double peso;
}TItem;

double mochilaRecursivo(TItem* itens, int n, double capacidade)
{
	double K1, K2;
	if(capacidade == 0)
		return 0;
	if(n == 0)
		return 0;
	else 
	{
		K1 = mochilaRecursivo(itens, n-1, capacidade);
		
		if(itens[n].peso <= capacidade)
			K2 = mochilaRecursivo(itens, n-1, capacidade - itens[n].peso) + itens[n].valor;
		else
			K2 = 0;
		
		return max(K1, K2);
	}
}

int main()
{
	int qnt = 4;
	TItem itens[qnt];
	double cap = 10;
	for(int i=0; i<qnt; i++)
	{
		cin>>itens[i].peso;
		cin>>itens[i].valor;
	}
	double lucro = mochilaRecursivo(itens, qnt, cap);
	cout<<lucro<<endl;
	return 0;
}