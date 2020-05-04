#ifndef PECA_H
#define PECA_H

#include <iostream>
#include "Tabuleiro.h"
#include "Jogadores.h"
using namespace std;
typedef struct Peca
{
	char peca1, peca2, dama1, dama2;
}tPeca;
void Simbolos(tPeca *p);
void PreencheTab(tTab *t, tPeca *p, tJog *J);
void Movimenta(tTab *t, tJog *J, int *numpecas1, int *numpecas2);


#endif
