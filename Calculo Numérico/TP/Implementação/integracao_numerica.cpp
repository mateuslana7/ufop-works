#include"integracao_numerica.h"
#include <bits/stdc++.h>
using namespace std;

double funcaoIntegracao(double x)
{
	return (pow(x,3)*log(x));
}

double metodoTrapezio(double a, double b, int m)
{
	int i;
	double x, y[m],h,I,soma=0.0;
	//Calculando o tamanho do intervalo
	h = (b-a)/m;
	//Calculando o valor de Ci
	for(i=0;i<=m;i++)
	{
		x=a+i*h;
		y[i]=funcaoIntegracao(x);
	}
	//Calculando o valor de Ci*Yi e somando seus devidos valores
	soma = soma + y[0];
	for(i=1;i<m;i++)
	{
		soma = soma +(2*y[i]);
	}
	soma = soma + y[m];
	//Calculando o valor aproximado da integral
	I=(h/2)*soma;
	return I;
}

double primeiraRegraSimpson(double a, double b, int m)
{
	int i;
	double x, y[m],h,I,soma=0.0;
	//Calculando o tamanho do intervalo
	h = (b-a)/m;
	//Calculando o valor de Ci
	for(i=0;i<=m;i++)
	{
		x=a+i*h;
		y[i]=funcaoIntegracao(x);
	}
	//Calculando o valor de Ci*Yi e somando seus devidos valores
	soma = soma + y[0];
	for(i=1;i<m;i++)
	{
		if(i%2 == 0)
		{
			soma = soma +(2*y[i]);
		}
		else
		{
			soma = soma +(4*y[i]);
		}
		
	}
	soma = soma + y[m];
	//Calculando o valor aproximado da integral
	I=(h/3)*soma;
	return I;
}

double segundaRegraSimpson(double a, double b, int m)
{
	int i;
	double x, y[m],h,I,soma=0.0;
	//Calculando o tamanho do intervalo
	h = (b-a)/m;
	//Calculando o valor de Ci
	for(i=0;i<=m;i++)
	{
		x=a+i*h;
		y[i]=funcaoIntegracao(x);
	}
	//Calculando o valor de Ci*Yi e somando seus devidos valores
	soma = soma + y[0];
	for(i=1;i<m;i++)
	{
		soma = soma +(3*y[i]);
	}
	soma = soma + y[m];
	//Calculando o valor aproximado da integral
	I=((3*h)/8)*soma;
	return I;
}