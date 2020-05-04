#ifndef CADASTRO_H
#define CADASTRO_H

#include "Perfil.h"

class Cadastro
{
    public:
        Perfil getPerfil() { return perfil; }
        void efetuarCadastro(Menu*);
        void setPerfil(Perfil p) { perfil = p; }
    private:
        Perfil perfil;
};

#endif 
