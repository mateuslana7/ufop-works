#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

class PortalDeInformacoes;

class Cadastro;

class Usuario;

class Menu
{
    public:
        int getOpcao() { return opcao; }
        void setOpcao(int op) { opcao = op; }
        void exibirMenu(Cadastro*, PortalDeInformacoes*);
        void abrirPortal(PortalDeInformacoes*, Cadastro*);
        void abrirCalendario(Usuario*);
        void desalocaUser(Usuario*);
    private:
        int opcao;
};

#endif
