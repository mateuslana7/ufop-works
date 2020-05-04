#ifndef MODELO_H
#define MODELO_H

using namespace std;

#include "Estoque.h"
#include "Fluxo.h"

//CRIA OS TIPOS DE ITERADORES DE ESTOQUE E FLUXO
typedef vector<Fluxo*>::iterator FluxoIterator;
typedef vector<Estoque*>::iterator EstoqueIterator;

class Modelo
{
    public:

        virtual void setNome(string) = 0;
        virtual string getNome() = 0;

        virtual void add(Estoque*) = 0;
        virtual void add(Fluxo*) = 0;

        virtual FluxoIterator getFluxosInicio() = 0;
        virtual FluxoIterator getFluxosFim() = 0;

        virtual EstoqueIterator getEstoquesInicio() = 0;
        virtual EstoqueIterator getEstoquesFim() = 0;

        virtual void executa(const int, const int, const int) = 0;

        virtual Estoque* criarEstoque () = 0;
        virtual Estoque* criarEstoque (double, string) = 0;
        virtual Estoque* criarEstoque(Estoque*)= 0;

        template <typename TFluxo>
        Fluxo* criarFluxo()
        {
            TFluxo *fl = new TFluxo;
            add(fl);
            return fl;
        }

        template <typename TFluxo>
        Fluxo* criarFluxo(Estoque *origem, Estoque *destino)
        {
            TFluxo *fl = new TFluxo(origem, destino);
            add(fl);
            return fl;
        }

        template <typename TFluxo>
        Fluxo* criarFluxo(TFluxo* fluxo)
        {
            TFluxo *fl = new TFluxo(fluxo->getOrigem(), fluxo->getDestino());
            add(fl);
            return fl;
        }

        static Modelo* criarModelo();
        static Modelo* criarModelo(vector <Fluxo*>, vector <Estoque*>, string);
        //static Modelo* criarModelo(Modelo*);
};

#endif 
