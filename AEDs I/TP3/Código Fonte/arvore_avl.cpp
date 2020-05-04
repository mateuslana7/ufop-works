#include "arvore_avl.h"

void ArvoreAVL_Inicia(TNoAVL **arvore)
{
	(*arvore)=NULL;
}

int FB(TNoAVL *raiz)
{
	if(raiz==NULL)
	{
		return 0;
	}
	return Altura(raiz->esq)-Altura(raiz->dir);
}

int Altura(TNoAVL *raiz)
{
	int esq_aux,dir_aux;
	if(raiz==NULL)
	{
		return 0;
	}
	esq_aux = Altura(raiz->esq);
	dir_aux = Altura(raiz->dir);
	
	if(esq_aux>dir_aux)
	{
		return esq_aux+1;
	}
	else
	{
		return dir_aux+1;
	}
}

void RotacaoSimplesEsquerda(TNoAVL **raiz)
{
	TNoAVL *aux;
	aux = (*raiz)->dir;
	(*raiz)->dir = aux->esq;
	aux->esq = (*raiz);
	(*raiz) = aux;
}

void RotacaoSimplesDireita(TNoAVL **raiz)
{
	TNoAVL *aux;
	aux = (*raiz)->esq;
	(*raiz)->esq = aux->dir;
	aux->dir = (*raiz);
	(*raiz) = aux;
}

int BalancaEsquerda(TNoAVL **raiz)
{
	int fbe = FB((*raiz)->esq);
	if(fbe>0)
	{
		RotacaoSimplesDireita(raiz);
		return 1;
	}
	else
	{
		if(fbe<0)
		{
			RotacaoSimplesEsquerda(&((*raiz)->esq));
			RotacaoSimplesDireita(raiz);
			return 1;
		}
	}
	return 0;
}

int BalancaDireita(TNoAVL **raiz)
{
	int fbd = FB((*raiz)->dir);
	if(fbd<0)
	{
		RotacaoSimplesEsquerda(raiz);
		return 1;
	}
	else
	{
		if(fbd>0)
		{
			RotacaoSimplesDireita(&((*raiz)->dir));
			RotacaoSimplesEsquerda(raiz);
			return 1;
		}
	}
	return 0;
}

int Balanceamento(TNoAVL **raiz)
{
	int fb = FB(*raiz);
	if(fb>1)
	{
		return BalancaEsquerda(raiz);
	}
	else
	{
		if(fb < (-1))
		{
			return BalancaDireita(raiz);
		}
		else
		{
			return 0;
		}
	}
}

int InsereAVL(TNoAVL **raiz,TItemAVL *x,int *comp)
{
	if((*raiz)==NULL)
	{
		(*raiz) = new TNoAVL;
		(*raiz)->item.palavra = x->palavra;
		(*raiz)->item.cont = x->cont;
		(*raiz)->item.chave = x->chave;
		(*raiz)->esq = NULL;
		(*raiz)->dir = NULL;
		return 1;
	}
	else
	{
		(*comp)++;
		if((*raiz)->item.palavra > x->palavra)
		{
			if(InsereAVL(&(*raiz)->esq,x,comp))
			{
				if(Balanceamento(raiz))
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
		}
		else
		{
			(*comp)++;
			if((*raiz)->item.palavra < x->palavra)
			{	
				if(InsereAVL(&(*raiz)->dir,x,comp))
				{
					if(Balanceamento(raiz))
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				//Elemento ja existe na arvore AVL!!!
				(*raiz)->item.cont += 1;
				return 0;
			}
		}
	}
	return 0;
}

void CentralAVL(TNoAVL **no)
{
	if((*no)==NULL)
	{
		return;
	}
	CentralAVL(&(*no)->esq);
	cout<<(*no)->item.palavra<<": "<<(*no)->item.cont<<endl;
	CentralAVL(&(*no)->dir);
}

int ArvoreAVL_EhVazia(TNoAVL **no)
{
	return (*no)==NULL;
}

void Limpar_ArvoreAVL(TNoAVL **no)
{
	if(!ArvoreAVL_EhVazia(no))
	{
		Limpar_ArvoreAVL(&(*no)->esq);
		Limpar_ArvoreAVL(&(*no)->dir);
		delete (*no);
	}
}