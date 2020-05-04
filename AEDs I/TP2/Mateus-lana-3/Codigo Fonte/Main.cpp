#include "Exercicio03.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "ShellSort.h"

int main()
{
	cout<<endl<<endl;
	cout<<"----------------------------- EXERCICIO 3 -----------------------------"<<endl<<endl;
	cout<<"------------------- UTILIZANDO METODOS DE ORDENACAO -------------------"<<endl<<endl;
	TItem *vet1,*aux1,*vet2,*aux2,*vet3,*aux3;
	Inicializar_Item(&vet1);
	Inicializar_Item(&aux1);
	Inicializar_Item(&vet2);
	Inicializar_Item(&aux2);
	Inicializar_Item(&vet3);
	Inicializar_Item(&aux3);
	clock_t inicio[18],fim[18],total[18];
	double tempo[18];
	long int j;
	unsigned long int numComp[18],numMov[18];
	
	//INICIALIZANDO OS VETORES DE COMPARAÇOES, MOVIMENTAÇOES E TEMPO COM 0
	for(j=0;j<18;j++)
	{
		numComp[j]=0;
		numMov[j]=0;
		tempo[j]=0;
	}
	ofstream arqIn1,arqIn2,arqIn3,arqOut1,arqOut2,arqOut3;
	
	//ENTRADA DE NUMEROS ALEATORIOS
	arqIn1.open("entrada_aleatoria.txt");
	arqIn1<<"Entrada de dados com numeros gerados aleatorios:"<<endl<<endl;
	cout<<"I - Carregando entrada de dados aleatorios."<<endl<<endl;
	cout<<"AGUARDE...";
	long int i,k,aux;
	srand((unsigned)time(NULL));
	for(i=0;i<n;i++)
	{
		aux=(rand()%1001)*(rand()%1001);
		vet1[i].chave=aux;
		arqIn1<<aux<<" ";
	}
	arqIn1.close();
	
	//ENTRADA DE NUMEROS CRESCENTES
	arqIn2.open("entrada_crescente.txt");
	arqIn2<<"Entrada de dados com numeros em ordem crescente:"<<endl<<endl;
	cout<<"\n\nII - Carregando entrada de dados em ordem crescente."<<endl<<endl;
	cout<<"AGUARDE...";
	for(i=0,k=1;i<n;i++,k++)
	{
		vet2[i].chave=k;
		arqIn2<<k<<" ";
	}
	arqIn2.close();
	
	//ENTRADA DE NUMEROS DECRESCENTES
	arqIn3.open("entrada_decrescente.txt");
	arqIn3<<"Entrada de dados com numeros em ordem decrescente:"<<endl<<endl;
	cout<<"\n\nIII - Carregando entrada de dados em ordem decrescente."<<endl<<endl;
	cout<<"AGUARDE...";
	for(i=0,k=n;i<n;i++,k--)
	{
		vet3[i].chave=k;
		arqIn3<<k<<" ";
	}
	arqIn3.close();
	
	//ORDENAÇAO DOS NUMEROS ALEATORIOS
	inicio[0]=clock();
	Copiar_Vetores(vet1,aux1);
	arqOut1.open("Ordenacao_dados_aleatorios.txt");
	arqOut1<<"Dados ordenados com numeros gerados aleatorios:"<<endl<<endl;
	
	cout<<"\n\n\n--- ORDENACAO DOS NUMEROS GERADOS ALEATORIAMENTE ---"<<endl;
	arqOut1<<"Ordenacao BubbleSort:"<<endl;
	cout<<"\n\nIV - Carregando ordenacao de numeros aleatorios pelo metodo BUBBLESORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Bubble(aux1,numComp,numMov,0);
	for(i=0;i<n;i++)
	{
		arqOut1<<aux1[i].chave<<" ";
	}
	arqOut1<<endl<<endl;
	fim[0]=clock();
	total[0]=fim[0]-inicio[0];
	tempo[0]=((double)total[0])/CLOCKS_PER_SEC;
	
	inicio[1]=clock();
	Copiar_Vetores(vet1,aux1);
	arqOut1<<"Ordenacao SelectionSort:"<<endl;
	cout<<"\n\nV - Carregando ordenacao de numeros aleatorios pelo metodo SELECTIONSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Selection(aux1,numComp,numMov,1);
	for(i=0;i<n;i++)
	{
		arqOut1<<aux1[i].chave<<" ";
	}
	arqOut1<<endl<<endl;
	fim[1]=clock();
	total[1]=fim[1]-inicio[1];
	tempo[1]=((double)total[1])/CLOCKS_PER_SEC;
	
	inicio[2]=clock();
	Copiar_Vetores(vet1,aux1);
	arqOut1<<"Ordenacao InsertionSort:"<<endl;
	cout<<"\n\nVI - Carregando ordenacao de numeros aleatorios pelo metodo SELECTIONSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Insertion(aux1,numComp,numMov,2);
	for(i=0;i<n;i++)
	{
		arqOut1<<aux1[i].chave<<" ";
	}
	arqOut1<<endl<<endl;
	fim[2]=clock();
	total[2]=fim[2]-inicio[2];
	tempo[2]=((double)total[2])/CLOCKS_PER_SEC;
	
	inicio[3]=clock();
	Copiar_Vetores(vet1,aux1);
	arqOut1<<"Ordenacao MergeSort:"<<endl;
	cout<<"\n\nVII - Carregando ordenacao de numeros aleatorios pelo metodo MERGESORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Merge(aux1,numComp,numMov,3);
	for(i=0;i<n;i++)
	{
		arqOut1<<aux1[i].chave<<" ";
	}
	arqOut1<<endl<<endl;
	fim[3]=clock();
	total[3]=fim[3]-inicio[3];
	tempo[3]=((double)total[3])/CLOCKS_PER_SEC;
	
	inicio[4]=clock();
	Copiar_Vetores(vet1,aux1);
	arqOut1<<"Ordencao QuickSort:"<<endl;
	cout<<"\n\nVIII - Carregando ordenacao de numeros aleatorios pelo metodo QUICKSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Quick(aux1,numComp,numMov,4);
	for(i=0;i<n;i++)
	{
		arqOut1<<aux1[i].chave<<" ";
	}
	arqOut1<<endl<<endl;
	fim[4]=clock();
	total[4]=fim[4]-inicio[4];
	tempo[4]=((double)total[4])/CLOCKS_PER_SEC;
	
	inicio[5]=clock();
	Copiar_Vetores(vet1,aux1);
	arqOut1<<"Ordenacao ShellSort:"<<endl;
	cout<<"\n\nIX - Carregando ordenacao de numeros aleatorios pelo metodo SHELLSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Shell(aux1,numComp,numMov,5);
	for(i=0;i<n;i++)
	{
		arqOut1<<aux1[i].chave<<" ";
	}
	arqOut1<<endl<<endl;
	fim[5]=clock();
	total[5]=fim[5]-inicio[5];
	tempo[5]=((double)total[5])/CLOCKS_PER_SEC;
	arqOut1.close();
	Liberar_Memoria(vet1);
	Liberar_Memoria(aux1);
	
	//ORDENAÇAO DOS NUMEROS CRESCENTES
	inicio[6]=clock();
	Copiar_Vetores(vet2,aux2);
	arqOut2.open("Ordenacao_dados_crescente.txt");
	arqOut2<<"Dados ordenados com numeros gerados em ordem crescente:"<<endl<<endl;
	
	cout<<"\n\n\n--- ORDENACAO DOS NUMEROS GERADOS EM ORDEM CRESCENTE ---"<<endl;
	arqOut2<<"Ordenacao BubbleSort:"<<endl;
	cout<<"\n\nX - Carregando ordenacao de numeros gerados em ordem crescente pelo metodo BUBBLESORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Bubble(aux2,numComp,numMov,6);
	for(i=0;i<n;i++)
	{
		arqOut2<<aux2[i].chave<<" ";
	}
	arqOut2<<endl<<endl;
	fim[6]=clock();
	total[6]=fim[6]-inicio[6];
	tempo[6]=((double)total[6])/CLOCKS_PER_SEC;
	
	inicio[7]=clock();
	Copiar_Vetores(vet2,aux2);
	arqOut2<<"Ordenacao SelectionSort:"<<endl;
	cout<<"\n\nXI - Carregando ordenacao de numeros gerados em ordem crescente pelo metodo SELECTIONSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Selection(aux2,numComp,numMov,7);
	for(i=0;i<n;i++)
	{
		arqOut2<<aux2[i].chave<<" ";
	}
	arqOut2<<endl<<endl;
	fim[7]=clock();
	total[7]=fim[7]-inicio[7];
	tempo[7]=((double)total[7])/CLOCKS_PER_SEC;
	
	inicio[8]=clock();
	Copiar_Vetores(vet2,aux2);
	arqOut2<<"Ordenacao InsertionSort:"<<endl;
	cout<<"\n\nXII - Carregando ordenacao de numeros gerados em ordem crescente pelo metodo INSERTIONSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Insertion(aux2,numComp,numMov,8);
	for(i=0;i<n;i++)
	{
		arqOut2<<aux2[i].chave<<" ";
	}
	arqOut2<<endl<<endl;
	fim[8]=clock();
	total[8]=fim[8]-inicio[8];
	tempo[8]=((double)total[8])/CLOCKS_PER_SEC;
	
	inicio[9]=clock();
	Copiar_Vetores(vet2,aux2);
	arqOut2<<"Ordenacao MergeSort:"<<endl;
	cout<<"\n\nXIII - Carregando ordenacao de numeros gerados em ordem crescente pelo metodo MERGESORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Merge(aux2,numComp,numMov,9);
	for(i=0;i<n;i++)
	{
		arqOut2<<aux2[i].chave<<" ";
	}
	arqOut2<<endl<<endl;
	fim[9]=clock();
	total[9]=fim[9]-inicio[9];
	tempo[9]=((double)total[9])/CLOCKS_PER_SEC;
	
	inicio[10]=clock();
	Copiar_Vetores(vet2,aux2);
	arqOut2<<"Ordencao QuickSort:"<<endl;
	cout<<"\n\nXIV - Carregando ordenacao de numeros gerados em ordem crescente pelo metodo QUICKSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Quick(aux2,numComp,numMov,10);
	for(i=0;i<n;i++)
	{
		arqOut2<<aux2[i].chave<<" ";
	}
	arqOut2<<endl<<endl;
	fim[10]=clock();
	total[10]=fim[10]-inicio[10];
	tempo[10]=((double)total[10])/CLOCKS_PER_SEC;
	
	inicio[11]=clock();
	Copiar_Vetores(vet2,aux2);
	arqOut2<<"Ordencao ShellSort:"<<endl;
	cout<<"\n\nXV - Carregando ordenacao de numeros gerados em ordem crescente pelo metodo SHELLSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Shell(aux2,numComp,numMov,11);
	for(i=0;i<n;i++)
	{
		arqOut2<<aux2[i].chave<<" ";
	}
	arqOut2<<endl<<endl;
	fim[11]=clock();
	total[11]=fim[11]-inicio[11];
	tempo[11]=((double)total[11])/CLOCKS_PER_SEC;
	arqOut2.close();
	Liberar_Memoria(vet2);
	Liberar_Memoria(aux2);
	
	//ORDENAÇAO DOS NUMEROS EM ORDEM DECRESCENTE
	inicio[12]=clock();
	Copiar_Vetores(vet3,aux3);
	arqOut3.open("Ordenacao_dados_decrescente.txt");
	arqOut3<<"Dados ordenados com numeros gerados em ordem decrescente:"<<endl<<endl;
	
	cout<<"\n\n\n--- ORDENACAO DOS NUMEROS GERADOS EM ORDEM DECRESCENTE ---"<<endl;
	arqOut3<<"Ordenacao BubbleSort:"<<endl;
	cout<<"\n\nXVI - Carregando ordenacao de numeros gerados em ordem decrescente pelo metodo BUBBLESORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Bubble(aux3,numComp,numMov,12);
	for(i=0;i<n;i++)
	{
		arqOut3<<aux3[i].chave<<" ";
	}
	arqOut3<<endl<<endl;
	fim[12]=clock();
	total[12]=fim[12]-inicio[12];
	tempo[12]=((double)total[12])/CLOCKS_PER_SEC;
	
	inicio[13]=clock();
	Copiar_Vetores(vet3,aux3);
	arqOut3<<"Ordenacao SelectionSort:"<<endl;
	cout<<"\n\nXVII - Carregando ordenacao de numeros gerados em ordem decrescente pelo metodo SELECTIONSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Selection(aux3,numComp,numMov,13);
	for(i=0;i<n;i++)
	{
		arqOut3<<aux3[i].chave<<" ";
	}
	arqOut3<<endl<<endl;
	fim[13]=clock();
	total[13]=fim[13]-inicio[13];
	tempo[13]=((double)total[13])/CLOCKS_PER_SEC;
	
	inicio[14]=clock();
	Copiar_Vetores(vet3,aux3);
	arqOut3<<"Ordenacao InsertionSort:"<<endl;
	cout<<"\n\nXVIII - Carregando ordenacao de numeros gerados em ordem decrescente pelo metodo INSERTIONSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Insertion(aux3,numComp,numMov,14);
	for(i=0;i<n;i++)
	{
		arqOut3<<aux3[i].chave<<" ";
	}
	arqOut3<<endl<<endl;
	fim[14]=clock();
	total[14]=fim[14]-inicio[14];
	tempo[14]=((double)total[14])/CLOCKS_PER_SEC;
	
	inicio[15]=clock();
	Copiar_Vetores(vet3,aux3);
	arqOut3<<"Ordenacao MergeSort:"<<endl;
	cout<<"\n\nXIX - Carregando ordenacao de numeros gerados em ordem decrescente pelo metodo MERGESORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Merge(aux3,numComp,numMov,15);
	for(i=0;i<n;i++)
	{
		arqOut3<<aux3[i].chave<<" ";
	}
	arqOut3<<endl<<endl;
	fim[15]=clock();
	total[15]=fim[15]-inicio[15];
	tempo[15]=((double)total[15])/CLOCKS_PER_SEC;
	
	inicio[16]=clock();
	Copiar_Vetores(vet3,aux3);
	arqOut3<<"Ordencao QuickSort:"<<endl;
	cout<<"\n\nXX - Carregando ordenacao de numeros gerados em ordem decrescente pelo metodo QUICKSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Quick(aux3,numComp,numMov,16);
	for(i=0;i<n;i++)
	{
		arqOut3<<aux3[i].chave<<" ";
	}
	arqOut3<<endl<<endl;
	fim[16]=clock();
	total[16]=fim[16]-inicio[16];
	tempo[16]=((double)total[16])/CLOCKS_PER_SEC;
	
	inicio[17]=clock();
	Copiar_Vetores(vet3,aux3);
	arqOut3<<"Ordenacao ShellSort:"<<endl;
	cout<<"\n\nXXI - Carregando ordenacao de numeros gerados em ordem decrescente pelo metodo SHELLSORT."<<endl<<endl;
	cout<<"AGUARDE...";
	Shell(aux3,numComp,numMov,17);
	for(i=0;i<n;i++)
	{
		arqOut3<<aux3[i].chave<<" ";
	}
	arqOut3<<endl<<endl;
	fim[17]=clock();
	total[17]=fim[17]-inicio[17];
	tempo[17]=((double)total[17])/CLOCKS_PER_SEC;
	arqOut3.close();
	Liberar_Memoria(vet3);
	Liberar_Memoria(aux3);
	
	//OBSERVAÇAO.: OS CARACTERES TRATAM-SE APENAS DA ESTETICA DO PROGRAMA
	char z=201, w=205, e=187, r=200, u=188;
	int m;
	cout<<endl<<endl;
	cout<<"\n  -- RESULTADOS --"<<endl;
	cout<<"  ";
	for(m=0;m<82;m++)//parte da estetica
	{
		if(m==0)
		cout<<z;
		if(m>=1 && m<=80)
		{
			cout<<w;
		}
		if(m==81)
		cout<<e;
	}
	cout<<endl<<endl;
	cout<<"   Informacoes com numeros gerados aleatoriamente"<<endl<<endl;
	cout<<"     Bubble....: Comparacoes: "<<numComp[0]<<" | Movimentacoes: "<<numMov[0]<<" | Tempo(seg): "<<tempo[0]<<endl;
	cout<<"     Selection.: Comparacoes: "<<numComp[1]<<" | Movimentacoes: "<<numMov[1]<<" | Tempo(seg): "<<tempo[1]<<endl;
	cout<<"     Insertion.: Comparacoes: "<<numComp[2]<<" | Movimentacoes: "<<numMov[2]<<" | Tempo(seg): "<<tempo[2]<<endl;
	cout<<"     Merge.....: Comparacoes: "<<numComp[3]<<" | Movimentacoes: "<<numMov[3]<<" | Tempo(seg): "<<tempo[3]<<endl;
	cout<<"     Quick.....: Comparacoes: "<<numComp[4]<<" | Movimentacoes: "<<numMov[4]<<" | Tempo(seg): "<<tempo[4]<<endl;
	cout<<"     Shell.....: Comparacoes: "<<numComp[5]<<" | Movimentacoes: "<<numMov[5]<<" | Tempo(seg): "<<tempo[5]<<endl<<endl;
	cout<<"   Informacoes com numeros gerados em ordem crescente"<<endl<<endl;
	cout<<"     Bubble....: Comparacoes: "<<numComp[6]<<" | Movimentacoes: "<<numMov[6]<<" | Tempo(seg): "<<tempo[6]<<endl;
	cout<<"     Selection.: Comparacoes: "<<numComp[7]<<" | Movimentacoes: "<<numMov[7]<<" | Tempo(seg): "<<tempo[7]<<endl;
	cout<<"     Insertion.: Comparacoes: "<<numComp[8]<<" | Movimentacoes: "<<numMov[8]<<" | Tempo(seg): "<<tempo[8]<<endl;
	cout<<"     Merge.....: Comparacoes: "<<numComp[9]<<" | Movimentacoes: "<<numMov[9]<<" | Tempo(seg): "<<tempo[9]<<endl;
	cout<<"     Quick.....: Comparacoes: "<<numComp[10]<<" | Movimentacoes: "<<numMov[10]<<" | Tempo(seg): "<<tempo[10]<<endl;
	cout<<"     Shell.....: Comparacoes: "<<numComp[11]<<" | Movimentacoes: "<<numMov[11]<<" | Tempo(seg): "<<tempo[11]<<endl<<endl;
	cout<<"   Informacoes com arquivos gerados em ordem decrescente"<<endl<<endl;
	cout<<"     Bubble....: Comparacoes: "<<numComp[12]<<" | Movimentacoes: "<<numMov[12]<<" | Tempo(seg): "<<tempo[12]<<endl;
	cout<<"     Selection.: Comparacoes: "<<numComp[13]<<" | Movimentacoes: "<<numMov[13]<<" | Tempo(seg): "<<tempo[13]<<endl;
	cout<<"     Insertion.: Comparacoes: "<<numComp[14]<<" | Movimentacoes: "<<numMov[14]<<" | Tempo(seg): "<<tempo[14]<<endl;
	cout<<"     Merge.....: Comparacoes: "<<numComp[15]<<" | Movimentacoes: "<<numMov[15]<<" | Tempo(seg): "<<tempo[15]<<endl;
	cout<<"     Quick.....: Comparacoes: "<<numComp[16]<<" | Movimentacoes: "<<numMov[16]<<" | Tempo(seg): "<<tempo[16]<<endl;
	cout<<"     Shell.....: Comparacoes: "<<numComp[17]<<" | Movimentacoes: "<<numMov[17]<<" | Tempo(seg): "<<tempo[17]<<endl<<endl;
	cout<<"  ";
	for(m=0;m<82;m++)//parte da estetica
	{
		if(m==0)
		cout<<r;
		if(m>=1 && m<=80)
		{
			cout<<w;
		}
		if(m==81)
		cout<<u;
	}
	cout<<endl<<endl<<endl;
	cout<<"Se julgarem necessario para a correcao, os dados ordenados foram salvos em um arquivo de texto."<<endl<<endl;
	cout<<"Fim da execucao!!"<<endl;
	return 0;
}