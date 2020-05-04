#ifndef EVENTO_H
#define EVENTO_H

#include "Menu.h"
#include "Data.h"
#include "Hora.h"
#include "Endereco.h"

class Evento
{
    public:
        string getNome() { return nome; }
        void setNome(string n) { nome = n; }
        Data getData() { return data; }
        void setData(Data d) { data = d; }
        Hora getHorario() { return horario; }
        void setHorario(Hora h) { horario = h; }
        Endereco getEndereco() { return endereco; }
        void setEndereco(string,string,string,string,int);
        void criarEvento();
    private:
        string nome;
        Data data;
        Hora horario;
        Endereco endereco;
};

#endif 
