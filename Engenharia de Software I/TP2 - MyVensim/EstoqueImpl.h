#ifndef ESTOQUEIMPL_H
#define ESTOQUEIMPL_H

#include <string>

#include "Estoque.h"


class EstoqueImpl : public Estoque
{
	public:

		EstoqueImpl();
		EstoqueImpl(double const &, string);//forma canonica
		
		virtual void setValor(double const);
		virtual double getValor();
		virtual void setNome(string);
		virtual string getNome();
		
		EstoqueImpl operator = (const EstoqueImpl&);//forma canonica
		virtual ~EstoqueImpl();
	
	protected:

		string nome;
		double valor;
};

#endif 
