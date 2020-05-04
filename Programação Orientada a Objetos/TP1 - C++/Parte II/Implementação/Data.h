#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

class Data
{
    public:
        int getDia(); 
        void setDia(int);
        int getMes();
        void setMes(int);
        int getAno();
        void setAno(int);
    private:
        int dia;
        int mes;
        int ano;
};

#endif 
