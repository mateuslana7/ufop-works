#ifndef FLUXOIMPL_H
#define FLUXOIMPL_H

#include "Fluxo.h"
#include "EstoqueImpl.h"

using namespace std;

class FluxoImpl : public Fluxo
{
    public:

        FluxoImpl();
        FluxoImpl(Estoque*, Estoque*);
        FluxoImpl(Fluxo*);//forma canonica
		
        virtual double executa() = 0;
        virtual void setOrigem(Estoque*);
        virtual Estoque* getOrigem();
        virtual void setDestino(Estoque*);
        virtual Estoque* getDestino();
		
        FluxoImpl& operator = (const FluxoImpl&);//forma canonica
		virtual ~FluxoImpl();//forma canonica
	
	protected:

        Estoque *origem;
        Estoque *destino;
};

//CRIA UM FLUXO EXPONENCIAL
class FluxoExponencial : public FluxoImpl
{
    public:

    FluxoExponencial()
    {
        Estoque* aux = new EstoqueImpl;
        setOrigem(aux);
        setDestino(aux);
    }
    FluxoExponencial(Estoque* origem, Estoque* destino):FluxoImpl(origem, destino){}
    FluxoExponencial(FluxoExponencial *fluxo):FluxoImpl(fluxo){}

    double executa()
    {
        return 0.01 * getOrigem()->getValor();
    }
};

//CRIA UM FLUXO LOGISTICO
class FluxoLogistico : public FluxoImpl
{
    public:

    FluxoLogistico()
    {
        Estoque* aux = new EstoqueImpl;
        setOrigem(aux);
        setDestino(aux);
    }
    FluxoLogistico(Estoque* origem, Estoque* destino):FluxoImpl(origem, destino){}
    FluxoLogistico(FluxoLogistico *fluxo):FluxoImpl(fluxo){}

    double executa()
    {
        return 0.01 * getDestino()->getValor() * (1 - getDestino()->getValor() / 70);
    }
};

#endif 
