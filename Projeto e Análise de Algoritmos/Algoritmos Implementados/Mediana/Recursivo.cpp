#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int separeAleatorizado(int* A, int p, int r)
{
	int num;
	srand((unsigned)time(NULL));
	i = rand()%r+p;
	aux = A[p];
	A[p] = A[i];
	A[i] = aux;
	
	return;
}

int selecionaAleat(int* A, int p, int t, int r)
{
	int q;
	if(p==r)
	{
		return A[p];
	}
	else
	{
		q = separeAleatorizado(A,p,r);
		if(q>=t)
			return selecionaAleat(A,p,t,q);
		else
			return selecionaAleat(A,q+1,t,r);	
	}
}

int main()
{
	int mediana, p=0, r=11;
	int vetor[] = {33,44,55,77,95,99,22,25,41,66,88,89};
	mediana = selecionaAleat(vetor,p,0,r);
	cout<<"Mediana:"<<mediana<<endl;
	return 0;
}
