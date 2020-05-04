#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Usuario.h"


class Administrador : public Usuario
{
    public:
        void verPerfil(Cadastro*);
};

#endif 
