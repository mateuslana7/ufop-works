#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H
#include<iostream>
#include<string>
using namespace std;

typedef struct
{
	string palavra;
	int cont;
	int chave;
}TItemAVL;

typedef struct NoAVL
{
	TItemAVL item;
	struct NoAVL *esq,*dir;
}TNoAVL;

typedef TNoAVL *ArvoreAVL;

void ArvoreAVL_Inicia(TNoAVL**);
int FB(TNoAVL*);
int Altura(TNoAVL*);
void RotacaoSimplesEsquerda(TNoAVL**);
void RotacaoSimplesDireita(TNoAVL**);
int BalancaEsquerda(TNoAVL**);
int BalancaDireita(TNoAVL**);
int Balanceamento(TNoAVL**);
int InsereAVL(TNoAVL**,TItemAVL*,int*);
void CentralAVL(TNoAVL**);
int ArvoreAVL_EhVazia(TNoAVL**);
void Limpar_ArvoreAVL(TNoAVL**);

#endif