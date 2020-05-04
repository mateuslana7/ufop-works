#include "PortalDeInformacoes.h"
#include <stack>

void PortalDeInformacoes::divulgarInfo(string info)
{
	pilha_info.push(info);
}

void PortalDeInformacoes::excluirPost(string post)
{
	int qtd, i;
	stack<string> pilha_aux;
	qtd = pilha_info.size(); 
	
	for(i=0; i<qtd; i++)
	{
		if(post != pilha_info.top())
		{
			pilha_aux.push(pilha_info.top());
			pilha_info.pop();
		}
		else
		{
			pilha_info.pop();
		}
	}
	pilha_info = pilha_aux;
    cout<<"\nPost retirado com sucesso!"<<endl;
}

void PortalDeInformacoes::visualizarInfos()
{
	int cont;
	stack<string> pilha_aux;
    pilha_aux = pilha_info;
	cont = pilha_aux.size();
	
	cout<<"--------Portal de Informacoes--------"<<endl<<endl;
	cout<<" Ordenado por postagens mais recentes"<<endl<<endl;
	for(int i=0; i<cont; i++)
	{
		cout<<i<<": "<<pilha_aux.top()<<endl<<endl;
		pilha_aux.pop();
	}
}