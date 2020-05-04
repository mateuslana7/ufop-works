/*
	Feito por: Felipe Fontenele de Ávila Magalhães
			   Mateus Vitor Pereira Lana
	Data: 10/03/2016
	Disciplina: BCC 202 - Estrutura de Dados I
	Prof(a): Amanda Sávio Nascimento e Silva
*/
#include"pesq_binaria.h"
#include"arvore_pesquisa.h"
#include"arvore_avl.h"

int main()
{
	cout<<endl<<endl;
	cout<<"                                       EXERCICIO 1                                              "<<endl;
	cout<<"   ============================================================================================ "<<endl;
	cout<<"  || Neste programa, trabalha-se os conceitos de pesquisa binaria, arvore binaria de pesquisa ||"<<endl;
	cout<<"  || sem balanceamento e arvore binaria de pesquisa com balanceamento(AVL). O programa recebe ||"<<endl;
	cout<<"  || um arquivo .txt de entrada, e imprime em ordem alfabetica as palavras e suas frequencias ||"<<endl;
	cout<<"  || no texto, alem de indicadores de perfomance dos algoritmos implementados.                ||"<<endl;
	cout<<"   ============================================================================================ "<<endl<<endl;
	
	ifstream entrada;
	entrada.open("entrada.txt");
	//Vetor temporario para armazenar as palavras!!!
	string* temp;
	int i,cont,n=0;
	char espaco_branco;
	//Variaveis para fazer a contagem de tempo!!!
	clock_t inicio,fim,total;
	double tempo;
	while(!entrada.eof())
	{
		entrada.get(espaco_branco);
		cont=1;
		while(espaco_branco != '\n' && !entrada.eof())
		{
			if(espaco_branco == ' ')
			{
				//Contagem de palavras existentes no arquivo!!!
				cont++;
			}
			entrada.get(espaco_branco);
		}
	}
	entrada.close();
	entrada.open("entrada.txt");
	//Alocacao dinamica do vetor temporario!!!
	temp = new string[cont];
	while(!entrada.eof())
	{
		//Extraindo dados do arquivo!!!
		entrada>>temp[n];
		n++;
	}
	entrada.close();
	Padronizar_Dados(temp,n);
	
	int opcao;
	cout<<"   Escolha o metodo de impressao da frequencia de palavras:    "<<endl<<endl;
	cout<<"   ============================MENU============================"<<endl;
	cout<<"  ||                                                          ||"<<endl;
	cout<<"  || 1 - Pesquisa binaria.                                    ||"<<endl;
	cout<<"  || 2 - Arvore binaria de pesquisa sem balanceamento.        ||"<<endl;
    cout<<"  || 3 - Arvore binaria de pesquisa balanceada(AVL).          ||"<<endl;
	cout<<"  ||                                                          ||"<<endl;
	cout<<"   ============================MENU============================"<<endl;
    cout<<endl;
	cout<<"   Escolha: ";  
	cin>>opcao;
	while(opcao<1 || opcao>3)
	{
		cout<<"\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE."<<endl;
		cout<<endl;
		cout<<"   Escolha a forma de impressao da frequencia de palavras:     "<<endl<<endl;
		cout<<"   ============================MENU============================"<<endl;
		cout<<"  ||                                                          ||"<<endl;
		cout<<"  ||                                                          ||"<<endl;
		cout<<"  || 1 - Pesquisa binaria.                                    ||"<<endl;
		cout<<"  || 2 - Arvore binaria de pesquisa sem balanceamento.        ||"<<endl;
		cout<<"  || 3 - Arvore binaria de pesquisa balanceada(AVL).          ||"<<endl;
		cout<<"  ||                                                          ||"<<endl;
		cout<<"   ============================MENU============================"<<endl;
		cout<<endl;
		cout<<"   Escolha: ";
		cin>>opcao;
	}
	
	//Pesquisa Binaria!!!
	if(opcao==1)
	{
		inicio = clock();
		TBinario *pesq_binaria;
		TDados *dados_binario;
		pesq_binaria = new TBinario;
		dados_binario = new TDados;
		TBinario_Construir_Binario(pesq_binaria,cont);
		int comp1=0;
		for(i=0; i<n; i++)
		{
			dados_binario->palavra = temp[i];
			TBinario_Inserir(pesq_binaria,dados_binario,&comp1);
		}
		cout<<endl;
		cout<<"FREQUENCIA DAS PALAVRAS:"<<endl<<endl;
		cout<<"Pesquisa binaria:"<<endl<<endl;
		for(i=0; i<n; i++)
		{
			if(pesq_binaria->v[i].cont>0)
			{
				cout<<pesq_binaria->v[i].palavra<<": "<<pesq_binaria->v[i].cont<<endl;
			}
		}
		fim = clock();
		total = fim - inicio;
		tempo = (((double)total)/CLOCKS_PER_SEC)*1000;
		cout<<endl<<endl;
		cout<<"Pesquisa Binaria:"<<endl<<endl;
		cout<<setfill(' ')<<setw(10)<<comp1<<" comparacoes"<<endl;
		cout<<setfill(' ')<<setw(10)<<tempo<<" milissegundos"<<endl<<endl;
		delete [] pesq_binaria->v;
		delete pesq_binaria;
		delete dados_binario;
	}

	
	//Arvore Binaria!!!
	if(opcao==2)
	{
		inicio = clock();
		Arvore *arvore;
		TItem *item;
		arvore = new Arvore;
		item = new TItem;
		Arvore_Inicia(arvore);
		int comp2 = 0;
		for(i=0; i<n; i++)
		{
			item->palavra = temp[i];
			item->cont = 1;
			item->chave = i;
			if(Arvore_Inserir(arvore,*item,&comp2));
		}
		cout<<endl;
		cout<<"FREQUENCIA DAS PALAVRAS:"<<endl<<endl;
		cout<<"Arvore binaria de pesquisa sem balanceamento:"<<endl<<endl;
		Central(arvore);
		fim = clock();
		total = fim - inicio;
		tempo = (((double)total)/CLOCKS_PER_SEC)*1000;
		cout<<endl<<endl;
		cout<<"Arvore Binaria de Pesquisa sem Balanceamento:"<<endl<<endl;
		cout<<setfill(' ')<<setw(10)<<comp2<<" comparacoes"<<endl;
		cout<<setfill(' ')<<setw(10)<<tempo<<" milissegundos"<<endl<<endl;
		Limpar_Arvore(arvore);
		delete arvore;
		delete item;
	}
	
	
	//Arvore AVL!!!
	if(opcao==3)
	{
		inicio = clock();
		ArvoreAVL *avl;
		TItemAVL *item_avl;
		avl = new ArvoreAVL;
		item_avl = new TItemAVL;
		ArvoreAVL_Inicia(avl);
		int comp3 = 0;
		for(i=0; i<n; i++)
		{
			item_avl->palavra = temp[i];
			item_avl->cont = 1;
			item_avl->chave = i;
			if(InsereAVL(avl,item_avl,&comp3));
		}
		cout<<endl;
		cout<<"FREQUENCIA DAS PALAVRAS:"<<endl<<endl;
		cout<<"Arvore AVL:"<<endl<<endl;
		CentralAVL(avl);
		fim = clock();
		total = fim - inicio;
		tempo = (((double)total)/CLOCKS_PER_SEC)*1000;
		cout<<endl<<endl;
		cout<<"Arvore Binaria de Pesquisa com Balanceamento AVL:"<<endl<<endl;
		cout<<setfill(' ')<<setw(10)<<comp3<<" comparacoes"<<endl;
		cout<<setfill(' ')<<setw(10)<<tempo<<" milissegundos"<<endl<<endl;
		Limpar_ArvoreAVL(avl);
		delete avl;
		delete item_avl;
	}
	
	delete [] temp;
	return 0;
}