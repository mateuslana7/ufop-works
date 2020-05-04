#include "Pintura.h"
#include <cstdlib>
#include <time.h>
void PreencherMatriz(int** I, int w, int h)
{
	int i, j, op;
	cout<<"\nDeseja preecher a matriz ou gera-la randomicamente?(0-Preencher/1-Gerar)\n";
	cin>>op;
	if (op == 0)
	{
		cout<<"\nInsira os valores da matriz:\n\n";
		for(i=0; i<w; i++)
		{
			for(j=0; j<h; j++)
			{
				cout<<"Linha "<<i<<" Coluna "<<j<<": ";
				cin>>I[i][j];
				cout<<endl;
			}
		}
	}
	else if (op == 1)
	{
		//Incializando randomincamente
		srand((unsigned)time(NULL));
		for(i=0; i<w; i++)
		{
			for(j=0; j<h; j++)
			{
				I[i][j] = rand() % 254 + 1;
			}
		}
	}
}
void MostrarMatriz (int** I, int w, int h)
{
	//Mostrando a Matriz
	int i, j;
	for(i=0; i<w; i++)
	{
		for(j=0; j<h; ++j)
		{
			//Condições para deixar a matriz alinhada na exibiçao
			if (I[i][j] < 10)
			{
				cout<<"  "<<I[i][j]<<"   ";
			}
			else
			{
				if(I[i][j] < 100)
				{
					cout<<"  "<<I[i][j]<<"  ";
				}
				else
				{
					cout<<" "<<I[i][j]<<"  ";
				}
			}
		}
		cout<<endl<<endl;
	}
}
int Boundaryfill(int** I, int w, int h, int x, int y, int cor_ant, int cor)
{
	//Confere os casos base
	if (x<0 || x>=w || y<0 || y>=h)
	{
		return **I;
	}
	else if (cor_ant != I[x][y])
	{
		return **I;
	}
	else if (cor == cor_ant)
	{
		return **I;
	}
	//Altera as cores vizinhas se não entrar nenhum dos casos base
	else 
	{
		I[x][y] = cor;
		Boundaryfill(I, w, h, x+1, y, cor_ant, cor);
		Boundaryfill(I, w, h, x-1, y, cor_ant, cor);
		Boundaryfill(I, w, h, x, y-1, cor_ant, cor);
		Boundaryfill(I, w, h, x, y+1, cor_ant, cor);
	}
	return 0;
}