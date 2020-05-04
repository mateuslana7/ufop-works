#include "Jogadores.h"
void InsereNome(tJog *J)
{
    cin.ignore();
    cout<<"\n Insira o nome do primeiro jogador: ";
    getline (cin, J->Jogador1);
    cout<<"\n Insira o nome do segundo jogador: ";
    getline (cin, J->Jogador2);
}