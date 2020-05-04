#include "Exercicio02.h"
#include "BubbleSort.h"

int main()
{	
	string lista;
	int k, qtd;
	cout<<endl<<endl;
	cout<<"----------------------------- EXERCICIO 2 -----------------------------"<<endl<<endl;
	cout<<"\nInsira o numero de listas que deseja ordenar:"<<endl<<endl;
	cin>>qtd;
	cout<<"\n Para inserir uma lista digite um dado, em seguida coloque uma virgula,"<<endl<<endl; 
	cout<<" apos a virgula um espaco e o dado seguinte e assim sucessivamente. Ao "<<endl<<endl;
	cout<<" final da lista coloque um ponto final."<<endl<<endl<<endl;
	cout<<" EXEMPLO: Mateus, Thiago, Felipe, Andre, 4, 7, 10, Joao, 1, 3, Caio."<<endl<<endl;
	
	for (k=0; k<qtd; k++)
	{
		cout<<"\n\nLista "<<k+1<<": ";
		if (k==0)
		{
			cin.ignore();
		}
		getline(cin,lista);
		while (!Verifica_Pontuacao(&lista))
		{
			cout<<"\nLista invalida. Nao ha um ponto final '.' para finalizar a lista."<<endl;
			cout<<"\nLista "<<k+1<<":"<<endl;
			if (k==0)
			{
				cin.ignore();
			}
			getline(cin,lista);
		}
		
		int cont=1, i=0, j=1;
		
		while (lista[i]!='.')//loop pra contar o numero de dados
		{
			if (lista[i]==',')
			{
				if (lista[j]==' ')
				{
					cont++;
				}
			}
			i++;
			j++;
		}
		string *vet1,*vet2,*vet3;
		int v4[cont],tam2=0,tam3=0;
		vet1 = new string[cont];
		Extrair(vet1,lista);
		
		for (i=0; i<cont; i++)
		{
			if (isalpha(vet1[i][0]))
			{
				tam2++;
				v4[i]=1;
			}
			else
			{
				tam3++;
				v4[i]=2;
			}
		}
		vet2 = new string[tam2];
		vet3 = new string[tam3];
		Separar(vet1,vet2,vet3,cont);
		Bubble(vet2,tam2);
		Bubble(vet3,tam3);
		OrdenacaoMexida(vet1,vet2,vet3,v4,cont);
		Imprime(vet1,cont);
		delete []vet2;
		delete []vet3;
		delete []vet1;
	}
	cout<<"Fim da execucao!!"<<endl;
	return 0;
}