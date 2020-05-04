#include "arvore_pesquisa.h"

void Arvore_Inicia(TNo **arvore)
{
	(*arvore)=NULL;
}

TNo* TNo_Cria(TItem x)
{
	TNo *aux = new TNo;
	aux->item.palavra = x.palavra;
	aux->item.cont = x.cont;
	aux->item.chave = x.chave;
	aux->esq = NULL;
	aux->dir = NULL;
	return aux;
}

bool Arvore_Inserir(TNo **no,TItem x,int *comp)
{
	if((*no)==NULL)
	{
		(*no)=TNo_Cria(x);
		return true;
	}
	(*comp)++;
	if(x.palavra<(*no)->item.palavra)
	{
		return Arvore_Inserir(&((*no)->esq),x,comp);
	}
	(*comp)++;
	if(x.palavra>(*no)->item.palavra)
	{
		return Arvore_Inserir(&((*no)->dir),x,comp);
	}
	//Elemento ja existe na arvore!!!
	(*no)->item.cont += 1;
	return false;
}

bool Arvore_Pesquisa(Arvore raiz,int valor,TItem *pX)
{
	if(raiz==NULL)
	{
		return false;
	}
	if(valor<raiz->item.chave)
	{
		return Arvore_Pesquisa(raiz->esq,valor,pX);
	}
	if(valor>raiz->item.chave)
	{
		return Arvore_Pesquisa(raiz->dir,valor,pX);
	}
	*pX = raiz->item;
	return true;
}

void Central(TNo **no)
{
	if((*no)==NULL)
	{
		return;
	}
	Central(&(*no)->esq);
	cout<<(*no)->item.palavra<<": "<<(*no)->item.cont<<endl;
	Central(&(*no)->dir);
}

int Arvore_EhVazia(TNo **no)
{
	return (*no)==NULL;
}

void Limpar_Arvore(TNo **no)
{
	if(!Arvore_EhVazia(no))
	{
		Limpar_Arvore(&(*no)->esq);
		Limpar_Arvore(&(*no)->dir);
		delete (*no);
	}
}