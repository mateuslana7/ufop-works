#include <iostream>

#include "Estoque.h"
#include "EstoqueImpl.h"


EstoqueImpl::EstoqueImpl()
{
    nome = "";
    valor = 0;
}

EstoqueImpl::EstoqueImpl(double const &valorInicial, string nome)
{
    this->nome = nome;
    valor = valorInicial;
}

void EstoqueImpl::setValor(double const valorAtual)
{
    valor = valorAtual;
}

double EstoqueImpl::getValor()
{
    return valor;
}

void EstoqueImpl::setNome(string nome)
{
    this->nome = nome;
}

string EstoqueImpl::getNome()
{
    return nome;
}

//FORMA CANONICA
EstoqueImpl EstoqueImpl::operator = (const EstoqueImpl &estoque)
{
    if (this == &estoque)
        return *this;

    EstoqueImpl aux = (EstoqueImpl&) estoque;

    setNome(aux.getNome());
    setValor(aux.getValor());

    return *this;
}

EstoqueImpl::~EstoqueImpl(){}
