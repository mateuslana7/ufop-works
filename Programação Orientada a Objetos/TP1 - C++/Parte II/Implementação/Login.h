#ifndef LOGIN_H
#define LOGIN_H

#include "Menu.h"
#include "Cadastro.h"

class Login
{
    public:
        string getEmail() { return email; }
        void setEmail(string e) { email = e; }
        string getSenha() { return senha; }
        void setSenha(string psw) { senha = psw; }
        void fazerLogin(Cadastro*, Menu*, PortalDeInformacoes*);
    private:
        string email;
        string senha;
};

#endif 
