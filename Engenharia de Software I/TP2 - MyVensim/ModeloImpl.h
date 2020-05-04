#ifndef MODELOIMPL_H
#define MODELOIMPL_H

using namespace std;

#include "Modelo.h"
#include "FluxoImpl.h"

class ModeloImpl : public Modelo
{
    public:

        ModeloImpl();
        ModeloImpl(vector <Fluxo*>, vector <Estoque*>, string);

        virtual void setNome(string);
        virtual string getNome();

        virtual FluxoIterator getFluxosInicio();
        virtual FluxoIterator getFluxosFim();

        virtual EstoqueIterator getEstoquesInicio();
        virtual EstoqueIterator getEstoquesFim();


        virtual void add(Estoque*);
        virtual void add(Fluxo*);

        virtual void executa(const int, const int, const int);

        virtual Estoque* criarEstoque();
        virtual Estoque* criarEstoque (double, string);
        virtual Estoque* criarEstoque(Estoque*);

        static Modelo* criarModelo();
        static Modelo* criarModelo(vector <Fluxo*>, vector <Estoque*>, string);
        static Modelo* criarModelo(Modelo*);

        virtual ~ModeloImpl();//forma canonica
		
    protected:

        string nome;
        vector<Fluxo*> fluxos;//fabrica de fluxos
        vector<Estoque*> estoques;//fabrica de estoques
        static vector<Modelo*> modelos;//fabrica de modelos
	
	private:
		ModeloImpl(Modelo *mod);//forma canonica
		ModeloImpl& operator = (const ModeloImpl&);//forma canonica

};


#endif 
