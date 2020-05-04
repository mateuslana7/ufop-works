#ifndef FLUXO_H
#define FLUXO_H

using namespace std;

#include "Estoque.h"


class Fluxo
{
    public:

        virtual double executa() = 0;
        virtual void setOrigem(Estoque*) = 0;
        virtual Estoque* getOrigem() = 0;
        virtual void setDestino(Estoque*) = 0;
        virtual Estoque* getDestino() = 0;
};


#endif 
