#include <bits/stdc++.h>

#include "Estoque.h"
#include "Fluxo.h"
#include "FluxoImpl.h"
#include "Modelo.h"

using namespace std;

void Testes_Unitarios();
void Testes_Estoque();
void Testes_Fluxo();
void Testes_Modelo();
void Testes_Funcionais();

int main()
{
	cout << "\n----------- TESTES UNITARIOS -----------" << endl;
    Testes_Unitarios();

	cout << "\n----------- TESTES FUNCIONAIS ----------" << endl; 	
    Testes_Funcionais();

    return 0;
}

void Testes_Unitarios()
{
	cout << "\nTESTES ESTOQUE" << endl;
    Testes_Estoque();
	
	cout << "\nTESTES FLUXO" << endl;
    Testes_Fluxo();
	
	cout << "\nTESTES MODELO" << endl;
    Testes_Modelo();
}

void Testes_Estoque()
{
    cout << endl;

    Modelo *modelo = Modelo::criarModelo();

    cout << "CRIACAO DE ESTOQUE SEM PARAMETRO... ";
    Estoque *estoque = modelo->criarEstoque();
    assert(estoque->getValor() == 0);
    assert(estoque->getNome() == "");
    cout << "Ok!" << endl;

    cout << "CRIACAO DE ESTOQUE COM PARAMETRO... ";
    Estoque *estoque1 = modelo->criarEstoque(100, "testeEstoque");
    assert(estoque1->getValor() == 100);
    assert(estoque1->getNome() == "testeEstoque");
    cout << "Ok!" << endl;

    cout << "CONSTRUTOR COPIA DE ESTOQUE........ ";
    Estoque *estoque2 = modelo->criarEstoque(estoque1);
    assert(estoque2->getValor() == 100);
    assert(estoque2->getNome() == "testeEstoque");
    cout << "Ok!" << endl;

    cout << "OPERADOR = PARA ESTOQUES........... ";
    Estoque *estoque3 = modelo->criarEstoque(1, "nomeCopia");
    Estoque *estoque4 = estoque3;
    assert (estoque4->getNome() == "nomeCopia");
    cout << "Ok!" << endl;

}

void Testes_Fluxo()
{
    cout << endl;

    Modelo *modelo = Modelo::criarModelo();

    cout << "CRIACAO DE FLUXO EXPONENCIAL....... ";
    Estoque* estoque1 = modelo->criarEstoque(100, "testeFluxo1");
    Estoque* estoque2 = modelo->criarEstoque(10, "testeFluxo2");
    Fluxo* fluxo = modelo->criarFluxo<FluxoExponencial>(estoque1, estoque2);
    assert(fluxo->getOrigem()->getNome() == "testeFluxo1");
    assert(fluxo->getDestino()->getNome() == "testeFluxo2");
    cout << "Ok!" << endl;

    cout << "CRIACAO DE FLUXO LOGISTICO......... ";
    Fluxo* fluxo1 = modelo->criarFluxo<FluxoLogistico>(estoque1, estoque2);
    assert(fluxo1->getOrigem()->getNome() == "testeFluxo1");
    assert(fluxo1->getDestino()->getNome() == "testeFluxo2");
    cout << "Ok!" << endl;

    cout << "OPERADOR = PARA FLUXOS............. ";
    Fluxo* fluxo2 = modelo->criarFluxo<FluxoExponencial>();
    fluxo2 = fluxo1;
    assert(fluxo2->getOrigem()->getNome() == "testeFluxo1");
    assert(fluxo2->getDestino()->getNome() == "testeFluxo2");
    cout << "Ok!" << endl;
}

void Testes_Modelo()
{
    cout << endl;

    cout << "CRIACAO DE MODELO SEM PARAMETRO.... ";
    Modelo *modelo = Modelo::criarModelo();
    assert(modelo->getNome() == "");
    cout << "Ok!" << endl;

    cout << "CRIACAO DE MODELO COM PARAMETROS... ";
    Estoque* estoque1 = modelo->criarEstoque(100, "testeModelo1");
    Estoque* estoque2 = modelo->criarEstoque(10, "testeModelo2");
    Fluxo* f1 = modelo->criarFluxo<FluxoExponencial>(estoque1, estoque2);
    vector<Estoque*> estoques;
    vector<Fluxo*> fluxos;
    estoques.push_back(estoque1);
    estoques.push_back(estoque2);
    fluxos.push_back(f1);
    Modelo *modelo1 = Modelo::criarModelo(fluxos, estoques, "testenamemodel");
    assert(modelo1->getNome() == "testenamemodel");
    cout << "Ok!" << endl;

    cout << "ADICAO DE ESTOQUE AO MODELO........ ";
    Estoque* estoque3 = modelo1->criarEstoque(200, "testeModelo3");
    int i = 0;
    vector<Estoque*>::iterator itEstoque = modelo1->getEstoquesInicio();
    vector<Estoque*>::iterator itEstoque1 = modelo1->getEstoquesFim();
    while (itEstoque != itEstoque1)
    {
        i++;
        ++itEstoque;
    }
    assert(i == 3);
    cout << "Ok!" << endl;

    cout << "ADICAO DE FLUXO AO MODELO.......... ";
    Fluxo* f2 = modelo1->criarFluxo<FluxoExponencial>(estoque1, estoque2);
    i = 0;
    vector<Fluxo *>::iterator itFluxo = modelo1->getFluxosInicio();
    vector<Fluxo *>::iterator itFluxo1 = modelo1->getFluxosFim();
    while (itFluxo != itFluxo1)
    {
        i++;
        ++itFluxo;
    }
    assert (i == 2);
    cout << "Ok!" << endl;

    cout << "OPERADOR = PARA MODELO............. ";
    Modelo *modelo3 = Modelo::criarModelo();
    modelo3 = modelo1;
    assert(modelo3->getNome() == modelo1->getNome());

    itEstoque = modelo3->getEstoquesInicio();
    itEstoque1 = modelo3->getEstoquesFim();
    i = 0;
    while (itEstoque != itEstoque1)
    {
        i++;
        ++itEstoque;
    }
    assert(i == 3);

    itFluxo = modelo3->getFluxosInicio();
    itFluxo1 = modelo3->getFluxosFim();
    i = 0;
    while (itFluxo != itFluxo1)
    {
        i++;
        ++itFluxo;
    }
    assert (i == 2);
    cout << "Ok!" << endl;
}

void Testes_Funcionais()
{
    cout << endl << "TESTE PARA FLUXO EXPONENCIAL....... ";
    Modelo* m1 = Modelo::criarModelo();

    Estoque* s1 = m1->criarEstoque(100, "pop1");
    Estoque* s2 = m1->criarEstoque(0, "pop2");

    Fluxo* f1 = m1->criarFluxo<FluxoExponencial>(s1, s2);


    m1->executa(0, 100, 1);
    assert(abs(s1->getValor() - 36.6032 < 0.001));
    //assert(abs(s1->getValor() - 34 < 0.001));
    assert(abs(s2->getValor() - 63.3968 < 0.001));
    cout << "Ok!" << endl;

    cout << endl << "TESTE PARA FLUXO LOGISTICO......... ";
    Modelo* m2 = Modelo::criarModelo();

    Estoque* s3 = m2->criarEstoque(100, "p1");
    Estoque* s4 = m2->criarEstoque(10, "p2");

    Fluxo* f2 = m2->criarFluxo<FluxoLogistico>(s3, s4);

    m2->executa(0, 100, 1);
    assert(abs(s3->getValor() - 88.2167 < 0.001));
    assert(abs(s4->getValor() - 21.7834 < 0.001));
    cout << "Ok!" << endl;

    cout << endl << "TESTE PARA MODELO ROBUSTO.......... ";
    Modelo* m3 = Modelo::criarModelo();

    Estoque* q1 = m3->criarEstoque(100, "q1");
    Estoque* q2 = m3->criarEstoque(0, "q2");
    Estoque* q3 = m3->criarEstoque(100, "q3");
    Estoque* q4 = m3->criarEstoque(0, "q4");
    Estoque* q5 = m3->criarEstoque(0, "q5");

    Fluxo* f = m3->criarFluxo<FluxoExponencial>(q1, q2);
    Fluxo* r = m3->criarFluxo<FluxoExponencial>(q2, q5);
    Fluxo* t = m3->criarFluxo<FluxoExponencial>(q2, q3);
    Fluxo* g = m3->criarFluxo<FluxoExponencial>(q1, q3);
    Fluxo* u = m3->criarFluxo<FluxoExponencial>(q3, q4);
    Fluxo* v = m3->criarFluxo<FluxoExponencial>(q4, q1);

    m3->executa(0, 100, 1);
    assert(abs(q1->getValor() - 31.8513 < 0.0001));
    assert(abs(q2->getValor() - 18.4003 < 0.0001));
    assert(abs(q3->getValor() - 77.1143 < 0.0001));
    assert(abs(q4->getValor() - 56.1728 < 0.0001));
    assert(abs(q5->getValor() - 16.4612 < 0.0001));
    cout << "Ok!" << endl;
}
