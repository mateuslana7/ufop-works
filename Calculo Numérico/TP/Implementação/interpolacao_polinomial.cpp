#include "interpolacao_polinomial.h"
#include <bits/stdc++.h>
using namespace std;

double metodoLagrange(double *x,double *fx, double valor, int tam)
{
	double L = 0, Lx[tam], somaNumerador = 1, somaDenominador = 1;
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            if (j != i){
                somaNumerador = somaNumerador * (valor - x[j]);
                somaDenominador = somaDenominador * (x[i] - x[j]);
            }
        }
        Lx[i] = somaNumerador / somaDenominador;
        somaNumerador = 1;
        somaDenominador = 1;
        cout << "O valor de L" << i <<"(x) = " << Lx[i] << endl;
    }
    for(int i=0; i<tam; i++){
        L += fx[i]*Lx[i];
    }

	return L;
}

double metodoDiferencasDivididas(double *x,double *fx,double valor,int tam)
{
	double Dyi[tam][tam], somaNumerador, somaDenominador;
    
    for(int j=0; j<tam; j++){
        somaNumerador = fx[j+1]-fx[j];
        somaDenominador = x[j+1]-x[j];
        Dyi[j][1] = somaNumerador/somaDenominador;
    }
    cout << endl;
 
    for(int k=2; k<tam+1; k++){
        for(int j=0; j<tam-k+1; j++){
            somaNumerador = Dyi[j+1][k-1]-Dyi[j][k-1];
            somaDenominador = x[j+k]-x[j];
            Dyi[j][k] = somaNumerador/somaDenominador;
        }
    }
 
    for (int j=0; j<tam; j++){
        for (int k=1; k<tam+1; k++){
            cout << fixed << setprecision(4) << Dyi[j][k] << " ";
        }
        cout << endl;
    }
 
    double p = fx[0];
 
    for(int j=1; j<tam+1; j++){
        double mult = 1;
        for(int k=0; k<j; k++){
            mult = mult * (valor - x[k]);
        }
        mult = mult * Dyi[0][j];
        p += mult;
    }

	return p;
}

double metodoDiferencasFinitasAsc(double *x,double *fx,double valor,int tam)
{
	double Dyi[tam][tam], somaNumerador;
    
    for(int j=0; j<tam; j++){
        somaNumerador = fx[j+1]-fx[j];
        Dyi[j][1] = somaNumerador;
    }
    cout << endl;
 
    for(int k=2; k<tam+1; k++){
        for(int j=0; j<tam-k+1; j++){
            somaNumerador = Dyi[j+1][k-1]-Dyi[j][k-1];
            Dyi[j][k] = somaNumerador;
        }
    }
 
    for (int j=0; j<tam; j++){
        for (int k=1; k<tam+1; k++){
            cout << fixed << setprecision(4) << Dyi[j][k] << " ";
        }
        cout << endl;
    }
 
    double p = fx[0], z = (valor - x[0])/(x[1] - x[0]), fat[] = {1,1,2,6,24,120,720,5040};
 
    for(int j=1; j<tam+1; j++){
        double mult = 1;
        for(int k=0; k<j; k++){
            mult = mult * (z - k);
        }
        mult = mult * (Dyi[0][j] / fat[j]);
        p += mult;
    }


	return p;
}