#ifndef ARVORE_PESQUISA_H
#define ARVORE_PESQUISA_H
#include<iostream>
#include<string>
using namespace std;

typedef struct
{
	string palavra;
	int cont;
	int chave;
}TItem;

typedef struct No
{
	TItem item;
	struct No *esq,*dir;
}TNo;

typedef TNo *Arvore;

void Arvore_Inicia(TNo**);
TNo* TNo_Cria(TItem);
bool Arvore_Inserir(TNo**,TItem,int*);
bool Arvore_Pesquisa(Arvore,int,TItem*);
void Central(TNo**);
int Arvore_EhVazia(TNo**);
void Limpar_Arvore(TNo**);

#endif