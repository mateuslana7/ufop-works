#include <iostream>
#include <cstdlib>
using namespace std;

int selection (int *a, int ini, int fim, int k)
{
	int pivotIndex, pivotValue,auxIndex;
	int i;
	pivotIndex = (ini+fim)/2;//não-randômico
	pivotValue = a[pivotIndex];
	swap(a[pivotIndex], a[fim]);
	auxIndex = ini;
	for(i = ini; i< fim;i++)
	{
		if(a[i] < pivotValue)
		{
			swap(a[auxIndex], a[i]);
			auxIndex = auxIndex+1;
		}
	}
	swap(a[auxIndex], a[fim]); 
	if(k == auxIndex) return a[k];
	else if (k < auxIndex ) return selection(a, ini, auxIndex-1,k);
	else return selection(a,auxIndex+1, fim, k);
}

int main()
{
	int mediana, p=0, r=12;
	int vetor[] = {33,44,55,77,95,99,22,25,41,66,88,89,23};
	mediana = selection(vetor,p,0,r);
	cout<<"Mediana:"<<mediana<<endl;
	return 0;
}
