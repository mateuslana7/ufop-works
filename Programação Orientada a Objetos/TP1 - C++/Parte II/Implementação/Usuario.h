#ifndef USUARIO_H
#define USUARIO_H

#include "Cadastro.h"

class Usuario
{
    public:
        Cadastro getCadastro() { return cadastro; }
        void setCadastro(Cadastro cad) { cadastro = cad; }
        void verPerfil(Cadastro* cad);
    protected:
        Cadastro cadastro;
};

#endif 
