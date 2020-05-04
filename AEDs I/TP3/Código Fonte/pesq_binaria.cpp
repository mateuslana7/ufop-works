#include"pesq_binaria.h"

void TBinario_Construir_Binario(TBinario* binario,int num)
{
	binario->n=0;
	binario->max=num;
	binario->v=new TDados[num];
	for(int i=0; i<num; i++)
	{
		binario->v[i].cont = 0;
	}
}

void TBinario_Inserir(TBinario* binario,TDados* dados,int *comp)
{
	int i;
	TDados aux;
	if(binario->n==binario->max)
	{
		cout<<"\nNAO EH POSSIVEL INSERIR DADOS, MEMORIA CHEIA."<<endl;
	}
	//Procurando a posicao correta para insercao!!!
	i = TBinario_Pesquisar(binario,dados->palavra,comp);
	if(i!= -1)
	{
		dados->cont=1;
		while(i<=binario->n)
		{
			//Inserindo a palavra na posicao correta!!!
			aux.palavra = binario->v[i].palavra;
			aux.cont = binario->v[i].cont;
			aux.chave = binario->v[i].chave;
			
			binario->v[i].palavra = dados->palavra;
			binario->v[i].cont = dados->cont;
			binario->v[i].chave = i;
			
			dados->palavra = aux.palavra;
			dados->cont = aux.cont;
			dados->chave = aux.chave;
			i++;
		}
		binario->n++;	
	}
}

int TBinario_Pesquisar(TBinario* binario,string pesq,int *comp)
{
	return TBinario_Recursivo(binario,0,binario->n,pesq,comp);
}

int TBinario_Recursivo(TBinario* binario,int esq,int dir,string pesq,int *comp)
{
	int meio = (esq+dir)/2;
	if(binario->v[meio].palavra!=pesq && esq>=dir)
	{
		return meio;
	}
	else
	{
		(*comp)++;
		if(pesq>binario->v[meio].palavra)
		{
			return TBinario_Recursivo(binario,meio+1,dir,pesq,comp);
		}
		else
		{
			(*comp)++;
			if(pesq<binario->v[meio].palavra)
			{
				return TBinario_Recursivo(binario,esq,meio,pesq,comp);
			}
			else
			{
				//Achou palavra repetida!!!
				binario->v[meio].cont++;
				return -1;
			}
		}
	}
}

void Padronizar_Dados(string *v,int n)
{
	char ch;
	int i,j;
	int tam;
	for(i=0;i<n;i++)
	{
		tam = v[i].size();
		for(j=0;j<tam;j++)
		{
			//Transformar todas as letras em minusculas!!!
			ch = v[i][j];
			ch = tolower(ch);
			v[i][j] = ch;
		}
	}
	for(i=0;i<n;i++)
	{
		tam = v[i].size();
		for(j=0;j<tam;j++)
		{
			if(ispunct(v[i][j]))
			{
				//Retirar sinais de pontuacao da palavra!!!
				v[i].erase(j,1);
			}
		}
	}
}