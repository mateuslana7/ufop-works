#ifndef ENDERECO_H
#define ENDERECO_H

#include "Menu.h"

class Endereco
{
    public:
        string getRua();
        void setRua(string);
        string getBairro();
        void setBairro(string b);
        string getNomeLugar();
        void setNomeLugar(string);
        string getCidade();
        void setCidade(string);
        int getNumero();
        void setNumero(int);
    private:
        string rua;
        string bairro;
        string nomeLugar;
        string cidade;
        int numero;
};

#endif 
