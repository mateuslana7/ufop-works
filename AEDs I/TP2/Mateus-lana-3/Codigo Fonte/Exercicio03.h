#ifndef EXERCICIO03_H
#define EXERCICIO03_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#define n 1000000 //SE JULGAR NECESSARIO ALTERE A CONSTANTE PARA TESTES COM NUMEROS MENORES

using namespace std;

typedef struct
{
	long int chave;
}TItem;

void Inicializar_Item(TItem**);
void Copiar_Vetores(TItem*,TItem*);
void Liberar_Memoria(TItem*);

#endif