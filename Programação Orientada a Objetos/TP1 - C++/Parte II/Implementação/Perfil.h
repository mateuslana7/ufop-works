#ifndef PERFIL_H
#define PERFIL_H

#include "Menu.h"
#include "Data.h"

class Perfil
{
    public:
        Perfil();
        string getNome() { return nome; }
        void setNome(string n) { nome = n; }
        string getEmail() { return email; }
        void setEmail(string e) { email = e; }
        string getSenha() { return senha; }
        void setSenha(string psw) { senha = psw; }
        Data getDataNasc() { return dataNasc; }
        void setDataNasc(Data d) { dataNasc = d; }
        char getSexo() { return sexo; }
        void setSexo(char s) { sexo = s; }
        bool getAdm() { return adm; }
        void setAdm(bool a) { adm = a; }
        void criarPerfil();
    private:
        string nome;
        string email;
        string senha;
        Data dataNasc;
        char sexo;
        bool adm;
};

#endif 
