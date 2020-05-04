#include <iostream>
#include <cmath>
using namespace std;

int RecDistEd(string a, int n, string b, int m)
{
	int c, R1, R2, R3, Raux;
	if(n == 0 && m == 0)
		return 0;
	if(n==0)
		return m;
	if(m==0)
		return n;
	else 
	{
		if(a[n] == b[m])
			c=0;
		else
			c=1;
		
		R1 = c + RecDistEd(a, n-1, b, m-1);
		R2 = 1 + RecDistEd(a, n-1, b, m);
		R3 = 1 + RecDistEd(a, n, b, m-1);
		
		Raux = min(R1,R2);
		return min(Raux,R3);
	}
}

int main()
{
	int n,m,custo;
	string a = "EXPONENCIAL";
	string b = "POLYNOMIAL";
	n = a.size();
	m = b.size();
	custo = RecDistEd(a,n,b,m);
	cout<<custo<<endl;
	return 0;
}