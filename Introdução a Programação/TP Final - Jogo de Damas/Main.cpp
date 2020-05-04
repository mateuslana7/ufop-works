#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include "Tabuleiro.h"
#include "Peca.h"
#include "Jogadores.h"
using namespace std;
int Menu()
{
    int i, op;
    char a=205;
    cout<<endl<<endl<<endl<<endl;
    cout<<"                   ";
    for (i=0; i<97; i++)
    {
		Sleep(5);
        cout<<a;
    }
	cout<<endl<<endl;
	Sleep (100);
    cout<<"                   ###########           ###           #####       #####           ###           #############   ###"<<endl;
	Sleep (100);
	cout<<"                   ############         #####          ######     ######          #####          #############   ###"<<endl;
	Sleep (100);
	cout<<"                   ###       ###       ### ###         ### ###   ### ###         ### ###         ###             ###"<<endl;
	Sleep (100);
	cout<<"                   ###        ###     ###   ###        ###  #######  ###        ###   ###        #############   ###"<<endl;
	Sleep (100);
	cout<<"                   ###         ###   ###########       ###   #####   ###       ###########       #############   ###"<<endl;
	Sleep (100);
	cout<<"                   ###        ###   #############      ###    ###    ###      #############                ###   ###"<<endl;
	Sleep (100);
	cout<<"                   ###       ###   ###         ###     ###           ###     ###         ###               ###      "<<endl;
	Sleep (100);
	cout<<"                   ############   ###           ###    ###           ###    ###           ###    #############   ###"<<endl;
	Sleep (100);
	cout<<"                   ###########   ###             ###   ###           ###   ###             ###   #############   ###"<<endl;
	cout<<endl;
	cout<<"                   ";
    for (i=0; i<97; i++)
    {
		Sleep(5);
        cout<<a;
    }
    cout<<endl<<endl;
    cout<<"  INSIRA O NUMERO REFERENTE A OPCAO DESEJADA"<<endl<<endl;
	for (i=0; i<20; i++)
	{
		Sleep(5);
		cout<<a;
	}
    cout<<"\n\n1-NOVO JOGO\n\n2-REGRAS\n\n3-SAIR(X)"<<endl<<endl;
	for (i=0; i<20; i++)
	{
		Sleep(5);
		cout<<a;
	}
	cout<<endl;
    cin>>op;
    return op;
}
int main()
{
	fstream arquivo;
	string regras[100];
    system("mode 640");
	system("color f9");
    int op, numpecas1=12, numpecas2=12, cont=0;
	char resp;
    tTab t;
	tPeca p;
	tJog J;
	system("cls");
	do{
		switch (op = Menu())
		{
			case 1:
                system("cls");
				InsereNome(&J);
				CriaTab(&t);
				Simbolos(&p);
				PreencheTab(&t, &p, &J);
				MostraTab(&t, &J, &numpecas1, &numpecas2);
				Movimenta(&t, &J, &numpecas1, &numpecas2);
				numpecas1=12;
				numpecas2=12;
				break;
			case 2:
				arquivo.open("regras.txt");
				while (! arquivo.eof())
				{
					getline (arquivo, regras[cont]);
					cont++;
				}
                system("cls");
				for (int i=0; i<cont; i++)
				{
                    cout<<"                          ";
					cout<<regras[i]<<endl;
				}
				cout<<endl<<"PARA SAIR DIGITE 'S'."<<endl;
				cin>>resp;
                system("cls");
				if (resp == 's' || resp == 'S')
				{
					break;
				}
			case 3:
				system("cls");
				break;
			default:
				system("cls");
				cout<<"Opcao invalida. Tente novamente.";
		} 
	}while (op != 3);
	return 0;
}
