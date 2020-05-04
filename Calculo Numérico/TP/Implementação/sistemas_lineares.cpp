#include <bits/stdc++.h>
#include "raizes.h"
using namespace std;

void GaussPivParcial(float **a, int n, float *b)
{
	int i, j, k, r;
	float w, m, aux;

	for(k = 0; k < n; k++)
	{
		w = fabs(a[k][k]);
		r = k;
		for (i=k; i<n; i++)
		{
			if (fabs(a[i][k]) > w)
			{
				w = fabs(a[i][k]);
				r = i;
			}
		}
		for (j=k; j<n; j++)
		{
			aux = a[k][j];
			a[k][j] = a[r][j];
			a[r][j] = aux;
		}
		aux = b[k];
		b[k] = b[r];
		b[r] = aux;
		for (i = k+1; i < n; i++)
		{
			m = -a[i][k] / a[k][k];
			for (j=k+1; j<n; j++)
			{
				a[i][j] = a[i][j] + m * a[k][j];    
			}
			b[i] = b[i] + m * b[k];    
		}    
	}    
}

float LUPivParcial(float **a, int *pos, int n)
{
	int i, j, k, r, trocas, auxint;
	float w, m, aux, det;

	for (i=0; i<n; i++) pos[i]=i;
	trocas = 0;
	for (k = 0; k < n-1; k++){
		w = fabs(a[k][k]);
		r = k;
		for (i=k; i<n; i++){
			if (fabs(a[i][k]) > w){
				w = fabs(a[i][k]);
				r = i;
			}
		}
		if (r != k){
			trocas++;
			/* Eh preciso trocar todas as colunas */
			for (j=0; j<n; j++){
				aux = a[k][j];
				a[k][j] = a[r][j];
				a[r][j] = aux;
			}
			auxint = pos[k];
			pos[k] = pos[r];
			pos[r] = auxint;      
		}
		for (i = k+1; i < n; i++){
			m = -a[i][k] / a[k][k];
			for (j=k; j<n; j++){
				a[i][j] = a[i][j] + m * a[k][j];    
			}
			a[i][k] = -m;     
		}    
	}
	det = 1;
	for (k=0; k<n; k++){
		det = det * a[k][k];    
	}
	if (trocas % 2 != 0)
		det = - det;
	return det;   
}

float Jacobi(float **a, int n, float *b, float *x)
{
	int i, j;
	float soma, erro;

	float xant[n];

	erro = 0;
	for (i=0; i<n; i++)
	{
		xant[i] = x[i];    
	}
	for (i=0; i<n; i++)
	{
		soma = 0;
		for (j=0; j<n; j++)
		{
			if (j != i)
			soma = soma + a[i][j]*xant[j];
		}
		x[i] = (b[i] - soma)/a[i][i];
		if (fabs(x[i] - xant[i]) > erro)
		erro = fabs(x[i] - xant[i]);    
	}
	return erro;
}

float GaussSeidel(float **a, int n, float *b, float *x)
{
	int i, j;
	float soma, erro, xant;
  
	erro = 0;
	for (i=0; i<n; i++)
	{
		xant = x[i];
		soma = 0;
		for (j=0; j<n; j++)
		{
			if (j != i)
			soma = soma + a[i][j]*x[j];
		}
		x[i] = (b[i] - soma)/a[i][i];
		if (fabs(x[i] - xant) > erro)
			erro = fabs(x[i] - xant);    
	}
	return erro;
}

float Substituicao_Retroativa(float** coef, int n, float* termosInd, float* x)
{
	double soma;
	x[n-1] = termosInd[n-1]/coef[n-1][n-1];
	for(int i=n-2; i>=0; i--)
	{
		soma = 0;
		for(int j=i+1; j<n; j++)
		{
			soma = soma + coef[i][j]*x[j];
		}
		x[i] = 	(termosInd[i] - soma)/coef[i][i];
	}
	return* x;
}

void SubstituicaoProgressiva(float **L, float *y, float *b, int n)
{
 	int i, j;
  	float soma;

  	for (i = 0; i < n; i++ ){
    	soma = 0;
    	for (j = 0; j < i; j++) {
      		soma = soma + L[i][j]*y[j];      
    	}
    	y[i] = (b[i] - soma);
  	}
}

void imprimeSolucao(float *x, int n)
{
	cout<<"\n==== SOLUCAO ===="<<endl;
	for(int i=0; i<n; i++)
	{
		cout<<" x"<<i+1<<" = "<<fixed<<setprecision(4)<<x[i]<<endl;
	}
	cout<<"================="<<endl;
}