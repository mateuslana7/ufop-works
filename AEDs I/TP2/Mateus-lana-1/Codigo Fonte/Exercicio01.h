#ifndef EXERCICIO01_H
#define EXERCICIO01_H

#include <iostream>
using namespace std;
 //Definiçao de todas as structs
typedef struct
{
	int n;
}TItem;

typedef struct Celula
{
	struct Celula *prox;
	TItem item;
}TCelula;

typedef struct
{
	TCelula* Fundo;
	TCelula* Topo;
	int tam;
}TPilha;

//Cabeçalho de todas as funçoes e procedimentos
int Menu();
void InicializarItem(TItem**);
void InicializarPilha(TPilha**);
void Inicia(TPilha*);
bool EhVazia(TPilha*);
void Push(TPilha*,TPilha*, TItem*);
bool Pop(TPilha*, TItem*);
int Tamanho(TPilha*);
void Imprime(TPilha*);
void Liberar_Mem_Item(TItem*);
void Liberar_Mem_Pilha(TPilha*);

#endif