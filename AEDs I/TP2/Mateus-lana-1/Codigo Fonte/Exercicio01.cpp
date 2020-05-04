#include "Exercicio01.h"

//Implementações

int Menu()
{
	int op, i;
	char a=205;//Parte da estetica
	cout<<"                  \nMENU"<<endl<<endl;
	for (i=0; i<40; i++)//Parte da estetica
	{
		cout<<a;
	}
    cout<<"\n\n1- INSERIR UM NUMERO NO TOPO DA PILHA\n\n2- RETIRAR UM NUMERO DO TOPO DA PILHA\n\n3- IMPRIMIR PILHA\n\n4- SAIR(X)"<<endl<<endl;
	for (i=0; i<40; i++)//Parte da estetica
	{
		cout<<a;
	}
	cout<<endl<<endl;
	cout<<" Insira a opcao que deseja: ";
	cin>>op;
    cin.ignore();
    return op;
}

void InicializarItem(TItem** num)
{
	(*num) = new TItem;
}

void InicializarPilha(TPilha** pilha)
{
	(*pilha) = new TPilha;
}

void Inicia (TPilha* pilha)
{
	pilha->Topo = new TCelula;
	pilha->Fundo = pilha->Topo;
	pilha->Topo->prox = NULL;
	pilha->tam = 0;
}

bool EhVazia (TPilha* pilha)
{
	if (pilha->Fundo == pilha->Topo || pilha->tam==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Push (TPilha* f1, TPilha* f2, TItem* num)
{
	if (!EhVazia(f1))
	{
		//Passagem de dados da fila 1 pra fila 2
		TCelula *auxiliar;
		auxiliar = f1->Fundo->prox;
		while (auxiliar != NULL)
		{
			f2->Topo->prox = new TCelula;
			f2->Topo=f2->Topo->prox;
			f2->Topo->item.n=auxiliar->item.n;
			f2->Topo->prox=NULL;
			f2->tam++;
			f1->tam--;
			auxiliar = auxiliar->prox;
		}
		//Fila 1 sem dados
		Inicia(f1);
	}
	//Insere o dado digitado na fila 1
	f1->Topo->prox = new TCelula;
	f1->Topo = f1->Topo->prox;
	f1->Topo->item.n = num->n;
	f1->Topo->prox = NULL;
	f1->tam++;
	//Retorna os dados da fila 2 pra a fila 1
	TCelula *auxiliar2;
	auxiliar2 = f2->Fundo->prox;
	while (auxiliar2!=NULL)
	{
		f1->Topo->prox=new TCelula;
		f1->Topo=f1->Topo->prox;
		f1->Topo->item.n=auxiliar2->item.n;
		f1->Topo->prox=NULL;
		f1->tam++;
		f2->tam--;
		auxiliar2=auxiliar2->prox;
	}
	//Fila 2 fica vazia nesse momento
	Inicia(f2);
}

bool Pop (TPilha* f1, TItem* num)
{
	if (EhVazia(f1))
	{
		return false;
	}
	else
	{
		TCelula* auxiliar;	
		auxiliar = f1->Fundo->prox;
		f1->Fundo->prox = f1->Fundo->prox->prox;
		f1->tam--;
		*num = auxiliar->item;
		if (f1->tam==0)
		{
			Inicia(f1);
		}
		delete auxiliar;
		return true;
	}
}

int Tamanho (TPilha* pilha)
{
	return pilha->tam;
}

void Imprime (TPilha* pilha)
{
	TCelula *auxiliar;
	auxiliar = pilha->Fundo->prox;
	if (EhVazia(pilha))
	{
		cout<<"\nPilha vazia!!"<<endl;
	}
	else
	{
		cout<<"\nDados da pilha:"<<endl<<endl;
		while (auxiliar != NULL)
		{
			cout<<"  "<<auxiliar->item.n<<endl;
			auxiliar = auxiliar->prox;
		}
	}
	cout<<endl;
}

void Liberar_Mem_Item(TItem* num)
{
	delete num;
}

void Liberar_Mem_Pilha(TPilha* pilha)
{
	delete pilha;
}