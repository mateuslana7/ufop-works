#ifndef ESTOQUE_H
#define ESTOQUE_H

using namespace std;

#include <string>

class Estoque
{
    public:

        virtual void setValor(double const) = 0;
        virtual double getValor() = 0;
        virtual void setNome(string) = 0;
        virtual string getNome() = 0;
};

#endif 
