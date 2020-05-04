#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Ponto
{
	double x;
	double y;
};

double distancia(double,double,double,double);
double randomico(double,double);
void gerar(int,double,double);
double forcaBruta(Ponto*,int,Ponto*,Ponto*);
int EhMenorCoordX(const void*, const void*);
int EhMenorCoordY(const void*, const void*);
double divisaoConquista(Ponto*, Ponto*, int, Ponto*, Ponto*);
double menorFaixa(Ponto*, int, double, Ponto*, Ponto*);
double min(double, double);

int main()
{
	int i=0, tam;
	string aux, linha;
	double maximo, minimo;
	cout<<"Informe o limite minimo do valor dos pontos a serem criados: ";
	cin>>minimo;
	cout<<"Informe o limite maximo do valor dos pontos a serem criados: ";
	cin>>maximo;
	cout<<"Informe a quantidade de pontos que deseja criar: ";
	cin>>tam;
	gerar(tam,minimo,maximo);
	ifstream arq;
	arq.open("entrada.txt");
	
	Ponto ponto1, ponto2;
	Ponto pontos[tam];
	
	while(!arq.eof())
    {
		arq>>ponto1.x>>ponto1.y;
		pontos[i] = ponto1;
		i++;
	}
	arq.close();
	
    // Forca Bruta
	duration<double> tempoForcaBruta;
	//Ordena os pontos pela coordenada x
	qsort(pontos, tam, sizeof(Ponto), EhMenorCoordX);
	/*for(int k=0; k < tam; k++)
	{
		cout << pontos[k].x << "    ->   " << pontos[k].y<< endl;
	
	}*/
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
	minimo = forcaBruta(pontos,tam,&ponto1,&ponto2);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
    tempoForcaBruta = duration_cast<duration<double> >(t2-t1);

    cout<<endl<<"Menor distancia Forca Bruta = "<<minimo<<endl;
	cout<<"Ponto 1: x = "<<ponto1.x<<" y = "<<ponto1.y<<endl;
	cout<<"Ponto 2: x = "<<ponto2.x<<" y = "<<ponto2.y<<endl;
	cout<<"Tempo(s) Forca Bruta: "<<tempoForcaBruta.count()<<endl;

	// Divisao e Conquista
    duration<double> tempoDivConquita;
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    Ponto pontoX[tam];
    Ponto pontoY[tam];
    for(i=0; i<tam; i++)
    {
    	pontoX[i] = pontos[i];
    	pontoY[i] = pontos[i];
    }
    qsort(pontoX, tam, sizeof(Ponto), EhMenorCoordX);
    qsort(pontoY, tam, sizeof(Ponto), EhMenorCoordY);
	minimo = divisaoConquista(pontoX,pontoY,tam,&ponto1,&ponto2);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
    tempoDivConquita = duration_cast<duration<double> >(t4-t3);
	
	cout<<endl<<"Menor distancia Divisao e Conquista = "<<minimo<<endl;
	cout<<"Ponto 1: x = "<<ponto1.x<<" y = "<<ponto1.y<<endl;
	cout<<"Ponto 2: x = "<<ponto2.x<<" y = "<<ponto2.y<<endl;
	cout<<"Tempo(s) Divisao e Conquista: "<<tempoDivConquita.count()<<endl;
	
	return 0;
}

/* Calcula a distancia entre dois pontos */
double distancia(double x1, double y1, double x2, double y2)
{
	double result;
	result = pow((x2 - x1),2) + pow((y2 - y1),2);
	return sqrt(result);
}

/* Gera numero aleatorio entre min e max */
double randomico(double min, double max)
{
    if (min == max) return min;
    int num = (min + rand() % (int)(max-min));
    int frac = rand() % 100;
    double total = num + (frac/100.0);
    return total;
}

/* Geracao do arquivo .txt com os pontos */
void gerar(int tam, double min, double max)
{
	Ponto ponto;
	ofstream arq;

	arq.open("entrada.txt");

	srand(time(NULL));
	for(int i = 0; i < tam; i++)
	{
		ponto.x = randomico(min, max);
		ponto.y = randomico(min, max);

		i == (tam - 1) ? arq << ponto.x << endl << ponto.y : arq << ponto.x << endl << ponto.y << endl;
	}
	arq.close();
}

int EhMenorCoordX(const void* a, const void* b)
{
	Ponto *p1 = (Ponto*)a, *p2 = (Ponto*)b;
	return (p1->x - p2->x);
}

int EhMenorCoordY(const void* a, const void* b)
{
	Ponto *p1 = (Ponto*)a, *p2 = (Ponto*)b;
	return (p1->y - p2->y);
}

double min(double x, double y)
{
    return (x < y)? x : y;
}

/* Encontrar a menor distancia entre os pontos por forca bruta */
double forcaBruta(Ponto *pontos, int tam, Ponto* ponto1, Ponto* ponto2)
{
	double menorDist, dist;
	double x1, y1, x2, y2;
	int i, j; 
	menorDist = DBL_MAX;
	for(i=0; i<tam-1; i++)
	{
		x1 = pontos[i].x;
		y1 = pontos[i].y;
		for(j=i+1; j<tam; j++)
		{
			x2 = pontos[j].x;
			y2 = pontos[j].y;
			if(x2 - x1 > menorDist)
			{
				break;
			}
			dist = distancia(x1,y1,x2,y2);
			//cout << dist << endl;
			if(dist < menorDist)
			{
				menorDist = dist;
				*ponto1 = pontos[i];
				*ponto2 = pontos[j];
			}
		}
	}
	return menorDist;
}

double menorFaixa(Ponto *faixa, int tam, double d, Ponto *ponto1, Ponto *ponto2)
{
	double menor = d;

	for(int i = 0; i < tam; ++i)
	{
		for(int j = i+1; j < tam && (faixa[j].y - faixa[i].y) < menor; ++j)
		{
			if(distancia(faixa[i].x,faixa[i].y,faixa[j].x,faixa[j].y) < menor)
			{
				menor = distancia(faixa[i].x,faixa[i].y,faixa[j].x,faixa[j].y);
				*ponto1 = faixa[i];
				*ponto2 = faixa[j];
			}
		}
	}
	return menor;
}

double divisaoConquista(Ponto *pontoX, Ponto *pontoY,int tam, Ponto* ponto1, Ponto* ponto2)
{
	if(tam <= 3)
	{
		return forcaBruta(pontoX, tam, ponto1, ponto2);
	}
	int meio = tam/2;
	Ponto pontoMeio = pontoX[meio];

	Ponto pontoYEsq[meio+1];
	Ponto pontoYDir[tam-meio-1];
	int li=0, ri=0;
	for(int i = 0; i < tam; i++)
	{
		if(pontoY[i].x <= pontoMeio.x)
			pontoYEsq[li++] = pontoY[i];
		else
			pontoYDir[ri++] = pontoY[i];
	}

	double distEsq = divisaoConquista(pontoX,pontoYEsq,meio,ponto1,ponto2);
	double distDir = divisaoConquista(pontoX+meio,pontoYDir,tam-meio,ponto1,ponto2);
	double d;

	if(distEsq < distDir)
	{
		d = distEsq;
		*ponto1 = pontoX[meio];
		*ponto2 = pontoY[meio];
	}
	else
	{
		d = distDir;
		*ponto1 = pontoX[tam-meio];
		*ponto2 = pontoY[tam-meio];
	}
	//double d = min(distEsq, distDir);

	Ponto faixa[tam];
	int j = 0;
	for(int i = 0; i < tam; i++)
	{
		if(abs(pontoY[i].x - pontoMeio.x) < d)
		{
			faixa[j] = pontoY[i];
			j++;
		}
	}
	return min(d, menorFaixa(faixa,j,d,ponto1,ponto2));
}
