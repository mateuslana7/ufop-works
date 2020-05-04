#include <iostream>
#include <vector>
#include <iterator>

#include "Estoque.h"
#include "Fluxo.h"
#include "Modelo.h"
#include "ModeloImpl.h"


//VARIAVEL GLOBAL
vector<Modelo*> ModeloImpl::modelos;


ModeloImpl::ModeloImpl()
{
    nome = "";
}

ModeloImpl::ModeloImpl(vector <Fluxo*> fluxos, vector <Estoque*> estoques, string nome)
{
    this->fluxos = fluxos;
    this->estoques = estoques;
    this->nome = nome;
}

ModeloImpl::ModeloImpl(Modelo *modelo)
{
    //int i;

    setNome(modelo->getNome());

    //EstoqueIterator it = getEstoquesInicio();
    EstoqueIterator it = estoques.begin();
    while (it != modelo->getEstoquesFim())
    {
        add(*it);
        ++it;
    }

    FluxoIterator it1 = getFluxosInicio();
    while (it1 != modelo->getFluxosFim())
    {
        add(*it1);
        ++it1;
    }

}

void ModeloImpl::setNome(string nome)
{
    this->nome = nome;
}

string ModeloImpl::getNome()
{
    return nome;
}

FluxoIterator ModeloImpl::getFluxosInicio()
{
    return fluxos.begin();
}

FluxoIterator ModeloImpl::getFluxosFim()
{
    return fluxos.end();
}

EstoqueIterator ModeloImpl::getEstoquesInicio()
{
    return estoques.begin();
}

EstoqueIterator ModeloImpl::getEstoquesFim()
{
    return estoques.end();
}

ModeloImpl& ModeloImpl::operator = (const ModeloImpl &mod)
{
    int i;

    if (this == &mod)
        return *this;

    //COPIA NOME
    nome = mod.nome;

    //COPIA SISTEMAS
    estoques.clear();
    for (i = 0; i < (int) mod.estoques.size(); i++)
    {
        Estoque *e = mod.estoques[i];
        estoques.push_back(e);
    }

    //COPIA FLUXOS
    fluxos.clear();
    for (i = 0; i < (int) mod.fluxos.size(); i++)
    {
        Fluxo *f = mod.fluxos[i];
        fluxos.push_back(f);
    }

    return *this;
}

void ModeloImpl::add(Estoque* estoque)
{
    estoques.push_back(estoque);
}

void ModeloImpl::add(Fluxo* fluxo)
{
    fluxos.push_back(fluxo);
}

//SIMULA O MODELO
void ModeloImpl::executa(const int inicio, const int fim, const int incremento)
{
    int j, i;
    double valores[fluxos.size()];
	double x;

    FluxoIterator it;


    //CALCULA GANHO/GASTO DE CADA SISTEMA DO MODELO
    for (j = inicio; j < fim; j = j + incremento)
    {
		//cout << "\n----------------------------------------------------------------" << endl;
        i=0;
        for (it = fluxos.begin(); it != fluxos.end(); ++it)
        {
            valores[i] = (*it)->executa();
			//cout << valores[i]<<endl;
            i++;
        }

        i = 0;
        for  (it = fluxos.begin(); it != fluxos.end(); ++it)
        {
            (*it)->getOrigem()->setValor((*it)->getOrigem()->getValor() - valores[i]);

            (*it)->getDestino()->setValor((*it)->getDestino()->getValor() + valores[i]);

            i++;
        }
    }
}



Estoque* ModeloImpl::criarEstoque ()
{
    Estoque *estoque = new EstoqueImpl();
    add(estoque);
    return estoque;
}

Estoque* ModeloImpl::criarEstoque (double valorEstoque, string nomeEstoque)
{
    Estoque *estoque = new EstoqueImpl(valorEstoque, nomeEstoque);
    add(estoque);
    return estoque;
}

Estoque* ModeloImpl::criarEstoque(Estoque* estoque)
{
    Estoque *estq = new EstoqueImpl(estoque->getValor(), estoque->getNome());
    add(estq);
    return estq;

}

//DELEGANDO FUNÇÔES
Modelo* Modelo::criarModelo()
{
    return ModeloImpl::criarModelo();
}

Modelo* Modelo::criarModelo(vector <Fluxo*> fluxo, vector <Estoque *> estoque, string id)
{
    return ModeloImpl::criarModelo(fluxo, estoque, id);
}

//IMPLEMENTANDO AS FUNÇÔES PROPRIAMENTE DITAS
Modelo* ModeloImpl::criarModelo()
{
    Modelo *mod = new ModeloImpl();
    modelos.push_back(mod);
    return mod;

}

Modelo* ModeloImpl::criarModelo(vector <Fluxo *> fluxo, vector <Estoque *> estoque, string id)
{
    Modelo *mod = new ModeloImpl(fluxo, estoque, id);
    modelos.push_back(mod);
    return mod;
}

ModeloImpl::~ModeloImpl()
{
    estoques.clear();
    fluxos.clear();
    modelos.clear();
}
