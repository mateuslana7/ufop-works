#include <bits/stdc++.h>
#include "sistemas_lineares.h"
#include "interpolacao_polinomial.h"
#include "integracao_numerica.h"
#include "raizes.h"
using namespace std;

int menuPrincipal();
int menuSistemasLineares();
int menuInterpolacao();
int menuIntegracao();
int menuRaizes();

int main()
{
	int op, opcao;

	do{
		op = menuPrincipal();

		switch(op)
		{
			case 1:
			{
				int n, iteracoes, k = 0;
				opcao = menuSistemasLineares();
				if(opcao == 5)
					break;
				cout<<"Insira a ordem da matriz do sistema de equacoes a ser resolvido."<<endl;
				cout<<"Ordem: ";
				cin>>n;
				float termosInd[n], termosCopia[n], x[n], y[n], precisao, erro, det;
				int pos[n];
				
				//Alocar a matriz de coeficientes dinamicamente
				float **coef = new float*[n];
				for(int i = 0;i < n; ++i)
				{
					coef[i] = new float[n];
				}
				cout<<"Preencha os valores da matriz de coeficientes"<<endl;
				for(int i=0; i<n; i++)
				{
					for(int j=0; j<n; j++)
					{
						cin>>coef[i][j];
					}
				}
				cout<<"Insira o vetor de termos independentes"<<endl;
				for(int i=0; i<n; i++)
				{
					cin>>termosInd[i];
				}
				for(int i=0; i<n; i++)
				{
					termosCopia[i] = termosInd[i];
					y[i] = 0;
				}
				
				switch(opcao)
				{
					case 1:	// Gauss Pivotacao Parcial
						GaussPivParcial(coef, n, termosInd);
						(*x) = Substituicao_Retroativa(coef, n, termosInd, x);
						imprimeSolucao(x,n);
						break;
					case 2:	// Decomposicao LU Pivotacao Parcial
					{
						det = LUPivParcial(coef, pos, n);
						cout << "Matriz LU resultante:\n";
						for(int i = 0; i < n; i++)
						{
							for(int j = 0; j < n; j++)
							{
								cout << coef[i][j] << "\t";
							}
							cout << endl;
						}
						cout << "Determinante = " << det << endl;
						for (int i=0; i < n; i++) printf("pos[%2d]=%d \n",i,pos[i]);
            	 		for (int i=0; i < n; i++) termosInd[i] = termosCopia[pos[i]];


            	 		for (int i=0; i < n; i++) printf("b[%2d]=%g \n",i,termosInd[i]);
			            SubstituicaoProgressiva(coef,y,termosInd,n);
			            printf("Solucao y resultante:\n");
			            for (int i=0; i<n; i++){
			               printf("%g \n",y[i]);
         				}

         				(*x) = Substituicao_Retroativa(coef, n, y, x);
						imprimeSolucao(x,n);
						break;
					}
					case 3:	// Jacobi
					{
						for(int i=0; i<n; i++)
						{
							x[i] = 0;
						}
						cout<<"Insira a precisao que deseja: ";
						cin>>precisao;
						cout<<"Insira a quantidade maxima de iteracoes: ";
						cin>>iteracoes;
						erro = (float)INT_MAX;
						do
						{
							erro = Jacobi(coef, n, termosInd, x);
							k++;
						}while(erro > precisao && k < iteracoes);
						imprimeSolucao(x,n);
						cout<<"Erro = "<<erro<<endl;
						break;
					}
					case 4:	// Gauss-Seidel
					{
						for(int i=0; i<n; i++)
						{
							x[i] = 0;
						}
						cout<<"Insira a precisao que deseja: ";
						cin>>precisao;
						cout<<"Insira a quantidade maxima de iteracoes: ";
						cin>>iteracoes;
						erro = (float)INT_MAX;
						do
						{
							erro = GaussSeidel(coef, n, termosInd, x);
							k++;
						}while(erro > precisao && k < iteracoes);
						imprimeSolucao(x,n);
						cout<<"Erro = "<<erro<<endl;
						break;
					}
					case 5:
						break;
					default:
						cout << "\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE...\n\n";
						break;
				}
				
				//Liberar memória da matriz de coeficientes
				for(int i=0; i<n; ++i)
				{
					delete []coef[i];
				}
				delete []coef;
				break;
			}

			case 2:
			{
				opcao = menuInterpolacao();
				if(opcao == 4)
					break;
				int tam;
				cout << "\nInforme o grau do polinomio: ";	// Quantidade de pontos para preencher!
				cin >> tam;
				double x[tam+1], fx[tam+1], xUser, result;
				for(int i = 0; i <= tam; i++)	// Preenchendo os pontos!
				{
					cout << "\nDigite x(" << i << ") = ";
				    cin >> x[i];
				    cout << "\nDigite f(" << x[i] << ") = ";
				    cin >> fx[i];
				}
				cout << "\nInforme o valor de x que deseja obter o valor de fx: ";
				cin >> xUser;
				switch(opcao)
				{
					case 1:
						result = metodoLagrange(x,fx,xUser,tam+1);
						cout << "\n=================== Resultado Lagrange =====================\n\n";
    					cout << "O valor final de L(" << xUser << ") = " << setprecision(4) << result << endl << endl;
    					break;

    				case 2:
    					result = metodoDiferencasDivididas(x,fx,xUser,tam);
    					cout << "\n=================== Resultado Diferencas Divididas =====================\n\n";
    					cout << "O valor final de p(" << xUser << ") = " << setprecision(4) << result << endl << endl;
    					break;

    				case 3:
    					result = metodoDiferencasFinitasAsc(x,fx,xUser,tam);
    					cout << "\n================= Resultado Diferencas Finitas Ascendentes ===================\n\n";
    					cout << "O valor final de p(" << xUser << ") = " << setprecision(4) << result << endl << endl;
    					break;
				}
				
				break;
			}

			case 3:
			{
				opcao = menuIntegracao();
				if(opcao == 4)
					break;
				int m;
				double a, b, aux,result=0.0;
				cout<<"\nInsira o valor de a: ";
				cin>>a;
				cout<<"Insira o valor de b: ";
				cin>>b;
				cout<<"Insira a quantidade(m) de intervalos: ";
				cin>>m;
				if(a>b)
				{ //condição para que o valor de b seja sempre o maior valor
					aux=a, a=b, b=aux;
				}
				switch(opcao)
				{
					case 1:
						result = metodoTrapezio(a,b,m);
						cout<<"\n==================== Resultado Regra dos Trapezios =====================\n\n";
						cout<<"Valor da integral = "<<fixed<<setprecision(4)<<result<<endl;
						break;

					case 2:
						while(m%2!=0)
						{
							cout<<"Quantidade de intervalos(m) devem ser pares"<<endl;
							cout<<"\nInsira novamente o numero de intervalos(m):\n";
							cin>>m;
						}
						result = primeiraRegraSimpson(a,b,m);
						cout<<"\n=================== Resultado 1 Regra de Simpson =====================\n\n";
						cout<<"\nValor da integral = "<<fixed<<setprecision(4)<<result<<endl;
						break;

					case 3:
						while(m%3!=0)
						{
							cout<<"Quantidade de intervalos(m) devem ser multiplo de 3"<<endl;
							cout<<"\nInsira novamente o numero de intervalos(m):\n";
							cin>>m;
						}
							
						result = segundaRegraSimpson(a,b,m);
						cout<<"\n=================== Resultado 2 Regra de Simpson =====================\n\n";
						cout<<"\nValor da integral = "<<fixed<<setprecision(4)<<result<<endl;
						break;
				}

				break;
			}

			case 4:
			{
				opcao = menuRaizes();
				if(opcao == 4)
					break;
				double a, b, precisao, result, aux;
				cout << "\nInforme o intervalo [a b] para calculo das raizes:\n";
				cout << "a = ";
				cin >> a;
				cout << "b = ";
				cin >> b;
				cout << "Informe a precisao desejada: ";
				cin >> precisao;
				if(a > b)
				{
					aux = a, a = b, b = aux;
				}

				switch(opcao)
				{
					case 1:
						result = bissecao(a,b,&precisao);
						cout << "\nRaiz Bissecao = " << fixed << setprecision(4) << result << endl;
						cout << "Precisao = " << fixed << setprecision(5) << precisao << endl;
						break;

					case 2:
						result = falsaPosicao(a,b,&precisao);
						cout << "\nRaiz Falsa Posicao = " << fixed << setprecision(4) << result << endl;
						cout << "Precisao = " << fixed << setprecision(5) << precisao << endl;
						break;

					case 3:
						result = newtonRaphson(a,&precisao);
						cout << "\nRaiz Newton-Raphson = " << fixed << setprecision(4) << result << endl;
						cout << "Precisao = " << fixed << setprecision(5) << precisao << endl;
						break;
				} 
				break;
			}
			case 5:
				cout << "\nPROGRAMA FINALIZADO COM SUCESSO..." << endl << endl;
				break;

			default:
				cout << "\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE...\n\n";
				break;			
		}

	}while(op != 5);


	return 0;
}

/* Menu principal */
int menuPrincipal()
{
    int op;
    do{
        cout<<"\n\n  =============== MENU PRINCIPAL ================"<<endl;
        cout<<" ||                                              ||"<<endl;
        cout<<" || 1 - Sistemas Lineares.                       ||"<<endl;
        cout<<" || 2 - Interpolacao Polinomial.                 ||"<<endl;
        cout<<" || 3 - Integracao Numerica.                     ||"<<endl;
        cout<<" || 4 - Raizes.                                  ||"<<endl;
        cout<<" || 5 - Sair.                                    ||"<<endl;
        cout<<" ||                                              ||"<<endl;
        cout<<"  =============== MENU PRINCIPAL ================"<<endl;
        cout<<endl;
        cout<<"  Escolha: ";
        cin>>op;
        if(op < 1 || op > 5)
            cout << "\n\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE...\n";
    } while (op < 1 || op > 5);
    return op;
}

/* Menu Sistemas Lineares */
int menuSistemasLineares()
{
    int escolha;
    do{
        cout<<"\n   ========= MENU SISTEMAS LINEARES ========="<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<" || 1 - Eliminacao de Gauss(com pivotacao).  ||"<<endl;
        cout<<" || 2 - Decomposicao LU(com pivotacao).      ||"<<endl;
        cout<<" || 3 - Jacobi.                              ||"<<endl;
        cout<<" || 4 - Gauss - Seidel.                      ||"<<endl;
        cout<<" || 5 - Voltar.                              ||"<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<"   ========= MENU SISTEMAS LINEARES ========="<<endl;
        cout<<endl;
        cout<<"  Escolha: ";
        cin>>escolha;
        if(escolha < 1 || escolha > 5)
            cout << "\n\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE...\n";
    } while (escolha < 1 || escolha > 5);
    return escolha;
}

/* Menu Interpolacao */
int menuInterpolacao()
{
    int escolha;
    do{
        cout<<"\n   =========== MENU INTERPOLACAO ============"<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<" || 1 - Lagrange.                            ||"<<endl;
        cout<<" || 2 - Diferencas divididas.                ||"<<endl;
        cout<<" || 3 - Diferencas finitas ascendentes.      ||"<<endl;
        cout<<" || 4 - Voltar.                              ||"<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<"   =========== MENU INTERPOLACAO ============"<<endl;
        cout<<endl;
        cout<<"  Escolha: ";
        cin>>escolha;
        if(escolha < 1 || escolha > 4)
            cout << "\n\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE...\n";
    } while (escolha < 1 || escolha > 4);
    return escolha;
}

/* Menu Integracao */
int menuIntegracao()
{
    int escolha;
    do{
        cout<<"\n   ============ MENU INTEGRACAO ============="<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<" || 1 - Regra dos Trapezios.                 ||"<<endl;
        cout<<" || 2 - Primeira Regra de Simpson.           ||"<<endl;
        cout<<" || 3 - Segunda Regra de Simpson.            ||"<<endl;
        cout<<" || 4 - Voltar.                              ||"<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<"   ============ MENU INTEGRACAO ============="<<endl;
        cout<<endl;
        cout<<"  Escolha: ";
        cin>>escolha;
        if(escolha < 1 || escolha > 4)
            cout << "\n\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE...\n";
    } while (escolha < 1 || escolha > 4);
    return escolha;
}

/* Menu Raizes */
int menuRaizes()
{
    int escolha;
    do{
        cout<<"\n   ============== MENU RAIZES ==============="<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<" || 1 - Metodo Bissecao.                     ||"<<endl;
        cout<<" || 2 - Metodo Falsa Posicao.                ||"<<endl;
        cout<<" || 3 - Metodo Newton-Raphson.               ||"<<endl;
        cout<<" || 4 - Voltar.                              ||"<<endl;
        cout<<" ||                                          ||"<<endl;
        cout<<"   ============== MENU RAIZES ==============="<<endl;
        cout<<endl;
        cout<<"  Escolha: ";
        cin>>escolha;
        if(escolha < 1 || escolha > 4)
            cout << "\n\nOPCAO INVALIDA. FAVOR TENTAR NOVAMENTE...\n";
    } while (escolha < 1 || escolha > 4);
    return escolha;
}