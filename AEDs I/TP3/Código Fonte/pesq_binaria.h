#ifndef PESQ_BINARIA_H
#define PESQ_BINARIA_H
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;

typedef struct
{
	string palavra;
	int cont;
	int chave;
}TDados;

typedef struct
{
	TDados *v;
	int n;
	int max;
}TBinario;

void TBinario_Construir_Binario(TBinario*,int);
void TBinario_Inserir(TBinario*,TDados*,int*);
int TBinario_Pesquisar(TBinario*,string,int*);
int TBinario_Recursivo(TBinario*,int,int,string,int*);
void Padronizar_Dados(string*,int);

#endif