#include <iostream>

#include "Fluxo.h"
#include "FluxoImpl.h"

FluxoImpl::FluxoImpl()
{
    Estoque  *aux = new EstoqueImpl(0, "");
    origem = aux;
    destino = aux;
}

FluxoImpl::FluxoImpl(Estoque* origem, Estoque* destino)
{
    this->origem = origem;
    this->destino = destino;
}

FluxoImpl::FluxoImpl(Fluxo *fluxo)
{
    origem = fluxo->getOrigem();
    destino = fluxo->getDestino();

}

void FluxoImpl::setOrigem(Estoque* origem)
{
    this->origem->setNome(origem->getNome());
    this->origem->setValor(origem->getValor());
}

Estoque* FluxoImpl::getOrigem()
{
    return origem;
}

void FluxoImpl::setDestino(Estoque* destino)
{
    this->destino->setNome(destino->getNome());
    this->destino->setValor(destino->getValor());
}

Estoque* FluxoImpl::getDestino()
{
    return destino;
}

//FORMA CANONICA
FluxoImpl& FluxoImpl::operator = (const FluxoImpl &fl)
{
    if (this == &fl)
        return *this;

    origem = fl.origem;
    destino = fl.destino;

    return *this;
}

FluxoImpl::~FluxoImpl(){}