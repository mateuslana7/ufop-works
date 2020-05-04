#include "Exercicio01.h"

int main()
{
	
	TPilha* fila1,*fila2;
	TItem* num;
	int op;
	InicializarPilha(&fila1);
	InicializarPilha(&fila2);
	InicializarItem(&num);
	Inicia(fila1);
	Inicia(fila2);
	
	cout<<endl<<endl;
	cout<<"----------------------------- EXERCICIO 1 -----------------------------"<<endl<<endl;
	
	do{
		op = Menu();
		switch (op)
		{
			case 1:
			{
				cout<<endl;
				cout<<"Qual numero deseja inserir na pilha ? ";
				cin>>num->n;
				Push(fila1,fila2,num);
				Imprime(fila1);
				break;
			}
			case 2:
			{
				if (Pop(fila1,num))
				{
					if (Tamanho(fila1)==0)
					{
						cout<<"\nRemocao feita."<<endl;
						cout<<"\nPilha vazia!!"<<endl<<endl;
					}
					else
					{
						cout<<"\nRemocao feita."<<endl;
						Imprime(fila1);
					}
				}
				else
				{
					cout<<"\nPilha vazia, nao eh possivel retirar dados!!"<<endl<<endl;
				}
				break;
			}
			case 3:
			{
				Imprime(fila1);
				break;
			}
			case 4:
			{
				cout<<"\nFim da execucao!!"<<endl<<endl;
				break;
			}
			default:
			{
				cout<<"\nOpcao invalida. Escolha novamente!"<<endl<<endl;
				break;
			}
		}
		
	}while(op!=4);
	
	Liberar_Mem_Item(num);
	Liberar_Mem_Pilha(fila1);
	Liberar_Mem_Pilha(fila2);
	return 0;
}