#include <cstdio>
#include "Recurso.h"
#include "Processo.h"
#include "Computador.h"
#include "Tarefa.h"
using namespace std;
int main()
{
	int qtdPC, qtdRec, qtdProc, tipoRec, numProc, qtdTar, tipoTar, i, j;
	double cpcd, vel, demanda;
	cout<<"\nInsira o numero de computadores:\n";
	cin>>qtdPC;
	fflush(stdin);
	TComputador **PC = new TComputador*[qtdPC];
	
	//Entra o numero de computadores e dados sobre o recurso
	for (int i=0; i<qtdPC; i++)
	{
		cout<<"\nInsira a quantidade de recursos e processos: \n\n";
		cout<<"\nCOMPUTADOR "<<i+1<<endl;
		cout<<"\nRecursos: ";
		cin>>qtdRec;
		cout<<"\nProcessos: ";
		cin>>qtdProc;
		fflush(stdin);
		Inicializar_PC(&PC[i], qtdRec, qtdProc);
		
		//Laço que tem como criterio de parada o numero de recursos
		for (int j=0; j<qtdRec; j++)
		{
			TRecurso *Recurso = new TRecurso;
			Inicializar_Rec(&Recurso);
			cout<<"\nQual eh o tipo de recurso? (1-CPU, 2-Memoria, 3-Disco)\n";
			cin>>tipoRec;
			fflush(stdin);
			while(tipoRec < 1 || tipoRec > 3)
			{
				cout<<"\nTipo invalido! Insira novamente: "<<endl;
				cin>>tipoRec;
				fflush(stdin);
			}
			cout<<"\nInsira a capacidade do recurso:\n";
			cin>>cpcd;
			fflush(stdin);
			cout<<"\nInsira a velocidade do recurso:\n";
			cin>>vel;
			fflush(stdin);
			setTipo(Recurso,tipoRec);
			setCapacidade(Recurso,cpcd);
			setVelocidade(Recurso,vel);
			AddRecurso(PC[i], Recurso);
		}
	}
	cout<<"\nInsira o numero de processos:\n";
	cin>>numProc;
	fflush(stdin);
	TProcesso **Processo = new TProcesso*[numProc];
	TTarefa* Tarefa;
	Inicializar_Tar(&Tarefa);
	
	//Entram os dados sobre as tarefas e processos
	for (i=0; i<numProc; i++)
	{
		cout<<"\nQual eh a quantidade de tarefas do processo?\n";
		cin>>qtdTar;
		fflush(stdin);
		Inicializar_Proc(&Processo[i], qtdTar);
		
		for (j=0; j<qtdTar; j++)
		{
			cout<<"\nQual eh o tipo de tarefa? (1-CPU, 2-Memoria, 3-Disco).\n";
			cin>>tipoTar;
			fflush(stdin);
			while (tipoTar < 1 || tipoTar > 3)
			{
				cout<<"\nTipo invalido! Insira novamente: "<<endl;
				cin>>tipoTar;
				fflush(stdin);
			}
			cout<<"\nInsira a demanda:\n";
			cin>>demanda;
			fflush(stdin);
			setRecurso(Tarefa, tipoTar);
			setDemanda(Tarefa, demanda);
			AddTarefa(Processo[i], Tarefa);
		}
	}
	delete Tarefa;
	
	//Verificador do sistema
	for(int i=0; i<numProc; i++)
	{
		for(int j=0; j<qtdPC; j++)
		{
			//Verificando se o computador consegue adicionar o processo.
			int acc = 1;
			for(int k=1 ; k<4; k++)
			{
				int dem_tot = Resultado_Dem(Processo[i], k);
				if (Verificar_Disp(PC[j], k, dem_tot) == 0)
				{
					acc = 0;
					break;
				}
			}
			if (acc == 1)
			{
				Processo[i]->comp = j+1;
				AddProcesso(PC[j], Processo[i]);
				break;
			}
		}
	}
	 
	//Executando o computador e exibindo resultados
	
    for (i=0; i<qtdPC; i++)
    {
		Executar_PC(PC[i], i);
        cout<<"\n---COMPUTADOR "<<i+1<<"---"<<endl;
		cout<<"\nProcessos: "<<PC[i]->cont_PROC<<endl;
		cout<<"Tempo total: "<<PC[i]->tempoTotal<<endl<<endl;
    }
    for (j=0; j<qtdProc; j++)
    {
        cout<<"\n---PROCESSO "<<j+1<<"---"<<endl;
		cout<<"\nComputador: "<<Processo[j]->comp<<endl;
		cout<<"Tempo de execucao: "<<Processo[j]->tempo_PROC<<endl;	
    }
	for (i=0; i<qtdPC; i++)
	{
		liberarMemoria_PC(PC[i], qtdRec);
	}
	
	return 0;
}