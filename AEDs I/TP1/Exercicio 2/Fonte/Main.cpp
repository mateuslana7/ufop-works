#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Pintura.h"
using namespace std;
int main()
{
	int w, h, i, x, y, c, cant;
	cout<<"\nInforme a largura e altura da imagem:\n";
	cout<<"\nLargura: ";
	cin>>w;
	cout<<"\nAltura: ";
	cin>>h;
	int** I = new int*[w];
	for(i=0; i<w; i++)
	{
		I[i] = new int[h];
	}
	PreencherMatriz(I, w, h);
	cout<<"\nImagem inicial:\n\n";
	MostrarMatriz(I, w, h);
	//Recebendo os pontos do usuario
	cin.ignore();
	cout<<"Insira o uma coordenada (x,y) dentro da matriz que deseja preencher e o codigo da cor(de 1 a 254):\n";
	cout<<"\nx: ";
	cin>>x;
	cout<<"\ny: ";
	cin>>y;
	while (x > w-1 || y > h-1)
	{
		cout<<"\nCoordenadas nao existentes! Insira novamente.\n";
		cout<<"\nx: ";
		cin>>x;
		cout<<"\ny: ";
		cin>>y;
	}
	cout<<"\nCor: ";
	cin>>c;
	while (c < 1 || c > 254)
	{
		cout<<"\nCodigo de cor invalido! Insira novamente.\n";
		cout<<"\nCor: ";
		cin>>c;
	}
	cant = I[x][y];
	Boundaryfill(I, w, h, x, y, cant, c);
	cout<<"\nImagem Final:\n\n";
	MostrarMatriz(I, w, h);
	//liberar memória
	for(i=0; i<w; ++i)
	{
		delete []I[i];
	}
	delete []I;

	return 0;
}