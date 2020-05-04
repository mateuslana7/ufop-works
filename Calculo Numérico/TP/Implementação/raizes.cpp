#include <bits/stdc++.h>
#include "raizes.h"
using namespace std;

double funcao(double x)
{
	return (pow(x,4) - 2*pow(x,3) + 4*x - 1.4331);	// Funcao que deseja encontrar a raiz!
}

double derivada(double x)
{
	return (4*pow(x,3) - 6*pow(x,2) + 4);	// Funcao para usuario informar a derivada!
}

double bissecao(double a , double b, double *precisao)
{
	double f_a, f_b, f_x, x, erro;
	f_a = funcao(a);
	f_b = funcao(b);
	if(f_a * f_b < 0)	// Verificacao do teorema de Cauchy!
	{
		do{
			x = (a+b)/2;	// Funcao de iteracao!
			f_x = funcao(x);
			erro = abs(f_x);
			if(f_a * f_x > 0)
				a = x;
			else
				b = x;
		}while(erro > *precisao);
	}
	else
	{
		cout << "\nNao existem raizes no intervalo [" << a << " " << b << "]" << endl;
	}
	*precisao = erro;
	return x;
}

double falsaPosicao(double a, double b, double *precisao)
{
	int i = 0;
	double f_a, f_b, f_x, x, erro = DBL_MAX;
	f_a = funcao(a);
	f_b = funcao(b);

	if(f_a * f_b < 0)	// Verificacao do teorema de Cauchy!
	{
		do{
			x = (a*f_b - b*f_a)/(f_b - f_a);	// Funcao de iteracao!
			i++;
			f_x = funcao(x);
			erro = abs(f_x);
			if(f_a * f_x > 0)
				a = x;
			else
				b = x;
		}while(erro > *precisao);
	}
	else
	{
		cout << "\nNao existem raizes no intervalo [" << a << " " << b << "]" << endl;
	}
	*precisao = erro;
	return x;
}

double newtonRaphson(double xi, double *precisao)
{
	double x, erro;

	do{
		x = xi - (funcao(xi) / derivada(xi));

		erro = abs(funcao(xi));
		xi = x;
	}while(erro > *precisao);

	*precisao = erro;
	
	return x;
}