#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <iostream>
#include "Jogadores.h"
using namespace std;
typedef struct Tab
{
	char tabu[8][8];
}tTab;
void CriaTab(tTab *t);
void MostraTab(tTab *t, tJog *J, int *numpecas1, int *numpecas2);

#endif