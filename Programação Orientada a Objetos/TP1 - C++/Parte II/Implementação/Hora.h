#ifndef HORA_H
#define HORA_H

#include<string>


class Hora
{
    public:
        int getHora();
        void setHora(int h);
        int getMinuto();
        void setMinuto(int);
    private:
        int hora;
        int minuto;
};

#endif 
