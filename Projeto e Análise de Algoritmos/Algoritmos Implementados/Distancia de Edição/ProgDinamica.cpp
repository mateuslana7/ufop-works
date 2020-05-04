#include <iostream>
#include <cmath>
using namespace std;

string a = "EXPONENTIAL";
string b = "POLYNOMIAL";

int DistEdicaoDinamica(int** M, int m, int n)
{
	int i,j,c, R1, R2, R3, Raux;
	for(i=0; i<m; i++)
		M[i][0] = i;
	for(j=0; j<n; j++)
		M[0][j] = j;
	for(i=1; i<m; i++)
	{
		for(j=1; j<n; j++)
		{
			if(a[i] == b[j])
				c = 0;
			else
				c = 1;
			
			R1 = M[i-1][j-1] + c;
			R2 = M[i-1][j] + 1;
			R3 = M[i][j-1] + 1;
			
			Raux = min(R1,R2);
			M[i][j] = min(Raux, R3);
		}
	}
	return M[m-1][n-1];
}

void exibeOperacao(int** M, int m, int n)
{
	int aux1, aux2;
	int i=m-1, j=n-1;
	while(i>0 || j>0)
	{
		//cout<<"M["<<i<<","<<j-1<<"] = "<<M[i][j-1]<<" "<<"M["<<i-1<<","<<j-1<<"] = "<<M[i-1][j-1]<<" "<<"M["<<i-1<<","<<j<<"]"<<" "<<M[i-1][j]<<endl;
		if(M[i-1][j-1] <= M[i][j-1] && M[i-1][j-1] <= M[i-1][j])
		{
			aux1 = i-1;
			aux2 = j-1;
		}
		else if(M[i][j-1] <= M[i-1][j-1] && M[i][j-1] <= M[i-1][j])
		{
			aux1 = i;
			aux2 = j-1;
		}
		else if(M[i-1][j] <= M[i][j-1] && M[i-1][j] <= M[i-1][j-1])
		{
			aux1 = i-1;
			aux2 = j;
		}	
		
		if(aux1 == i && aux2 == j-1)
		{
			cout<<"Insercao!"<<endl;
			j--;
		}
		else if(aux1 == i-1 && aux2 == j)
		{
			cout<<"Remocao!"<<endl;
			i--;
		}
		else if(aux1 == i-1 && aux2 == j-1)
		{
			if(M[i][j] == M[aux1][aux2])
				cout<<"Casamento!"<<endl;
			else
				cout<<"Troca!"<<endl;
			
			j--;
			i--;
		}
	}
}

int main()
{
	int m = a.size();
	int n = b.size();
	
	int** M = new int*[m];
	for(int i=0; i<m; i++)
	{
		M[i] = new int[n];
	}
	
	int custo = DistEdicaoDinamica(M,m,n);
	
	cout<<"  ";
	for(int i=0; i<n; i++)
	{
		cout<<b[i]<<" ";
	}
	cout<<endl;
	for(int i=0; i<m; i++)
	{
		cout<<a[i]<<" "; 
		for(int j=0; j<n; j++)
		{
			cout<<M[i][j]<<" ";
		}
		cout<<endl;
	}
	exibeOperacao(M, m, n);
	
	for(int i = 0;i < m; i++)
	{
		delete []M[i];
	}
	
	cout<<custo<<endl;
}