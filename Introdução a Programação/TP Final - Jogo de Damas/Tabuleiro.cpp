#include <iostream>
#include <cstdlib>
#include "Peca.h"
#include "Jogadores.h"
#include "Tabuleiro.h"
using namespace std;
void CriaTab(tTab *t)
{
	char x=178, y=' ';
	int i, j;
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			if (i%2 == 0 && j%2 == 0)
			{
				t->tabu[i][j]=x;
				t->tabu[i][++j]=y;
			}
			else 
			{
				t->tabu[i][j]=y;
				t->tabu[i][++j]=x;
			}
		}
	}
	cout<<endl<<endl;
}
void MostraTab(tTab *t, tJog *J, int *numpecas1, int *numpecas2)
{
	int i, j, k;
	char z=201, w=205, e=187,r=200, u=188, q=186; 
	system("cls"); 
	cout<<endl<<"                                  DAMAS"<<endl;
	cout<<"Peca de "<<J->Jogador1<<": o."<<endl;
	cout<<"Peca de "<<J->Jogador2<<": x."<<endl<<endl;//VER AQUI
	cout<<J->Jogador1<<": "<<*numpecas1<<"       "<<J->Jogador2<<": "<<*numpecas2<<endl;//MEXER
	cout<<"________________________________________________________________________________"<<endl<<endl;
	cout<<"                                ";
	cout<<"01234567\n";
	cout<<"                               ";
	for (k=0; k<10; k++)
	{
		if (k==0)
		cout<<z;
		if (k>=1 && k<=8)
		{
			cout<<w;
		}
		if (k==9)
		cout<<e;
	}
	cout<<endl;	
	for (i=0; i<8; i++)
	{
		cout<<"                             "<<i<<" "<<q;
		for (j=0; j<8; j++)
		{
			cout<<t->tabu[i][j];
		}
		cout<<q;
		cout<<endl;
	}
	cout<<"                               ";
	for (k=0; k<10; k++)
	{
		if (k==0)
		cout<<r;
		if (k>=1 && k<=8)
		{
			cout<<w;
		}
		if (k==9)
		cout<<u;
	}
	cout<<endl;
}
