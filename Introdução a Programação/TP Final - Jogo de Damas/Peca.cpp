#include "Peca.h"
#include "Jogadores.h"
#include <cstdlib>
#include <windows.h>
void Simbolos (tPeca *p)
{
    p->peca1 = 'o';
    p->peca2 = 'x';
    p->dama1 = 'O';
    p->dama2 = 'X';
}
void PreencheTab(tTab *t, tPeca *p, tJog *J)
{
    int i, j;
	//Coloca Peca1
	for (i=0; i<3; i++)
	{
		for (j=0; j<8; j++)
		{
			if (t->tabu[i][j]==' ')
			{
				t->tabu[i][j]=p->peca1;
			}
		}
	}
	//Coloca Peca2
	for (i=7; i>4; i--)
	{
		for (j=0; j<8; j++)
		{
			if (t->tabu[i][j]==' ')
			{
				t->tabu[i][j]=p->peca2;
			}
		}
	}
	system ("cls");
	cout<<endl<<"                                  DAMAS"<<endl;
	cout<<"Peca de "<<J->Jogador1<<": o."<<endl;
	cout<<"Peca de "<<J->Jogador2<<": x."<<endl;//VER AQUI
	cout<<J->Jogador1<<": 12        "<<J->Jogador2<<": 12"<<endl<<endl;//MEXER
	cout<<"________________________________________________________________________________"<<endl<<endl;
	cout<<"                                ";
	cout<<"01234567\n";
	for (i=0; i<8; i++)
	{
		cout<<"                              "<<i<<" ";
		for (j=0; j<8; j++)
		{
			cout<<t->tabu[i][j];
		}
		cout<<endl;
	}
}
void Movimenta(tTab *t, tJog *J, int *numpecas1, int *numpecas2)
{
	//MOVIMENTA AS PEÇAS
    char resp;
	int k=0, x, y, z, w;
    int n, m;
	do
    {
		if ((*numpecas1)==0)
			break;
		if ((*numpecas2)==0)
			break;
		if (k%2 == 0)//VEZ DO JOGADOR 1
		{
            cout<<"VEZ DE: "<<J->Jogador1<<endl<<endl;
			cout<<"Digite as coordenadas da peca que deseja movimentar, linha e coluna:\n";
			cin>>x>>y;
            if (t->tabu[x][y] == 'o' || t->tabu[x][y] == 'O') 
            {
				if (t->tabu[x][y]=='o')//SE FOR PECA NORMAL
				{
					cout<<"Digite as coordenadas do destino para o qual deseja movimenta-la, linha e coluna:\n";
					cin>>z>>w;
					if (t->tabu[z][w] != ' ' || z>7 || w>7 || z<0 || w<0)
					{
						cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
						Sleep(1800);
						MostraTab(t, J, numpecas1, numpecas2);
					}
					else 
					{
						if(z-x==1)
						{
							if (((z-x == 1) && (w-y == 1 || w-y == -1)) && (t->tabu[z][w] == ' '))//RESTRIÇAO DE MOVIMENTO
							{
								if (z==7 && t->tabu[x][y]=='o')//VIRA DAMA
								{
									t->tabu[x][y]='O';
								}
								t->tabu[z][w] = t->tabu[x][y];
								t->tabu[x][y] = ' ';
								MostraTab(t, J, numpecas1, numpecas2);
								k++;
							}
							else
							{
								cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
								Sleep(2500);
								MostraTab(t, J, numpecas1, numpecas2);
							}
						}
						if(z-x==2)
						{
							if (((z-x == 2) && (w-y == 2 || w-y == -2)) && ((t->tabu[x+1][y+1]=='x') ||(t->tabu[x+1][y+1]=='X') || (t->tabu[x+1][y-1]=='x') || (t->tabu[x+1][y-1]=='X')) && (t->tabu[z][w]==' '))//COMER PEÇAS
							{
								if (z==7 && t->tabu[x][y]=='o')//VIRA DAMA
								{
									t->tabu[x][y]='O';
								}
								t->tabu[z][w] = t->tabu[x][y];
								t->tabu[x][y] = ' ';
								if (w-y == 2)
								{
									t->tabu[x+1][y+1]=' ';
								}
								else if (w-y == -2)
								{
									t->tabu[x+1][y-1]=' ';
								}
								(*numpecas2)--;//DIMINUI NUMERO DE PECAS JOGADOR 2
								MostraTab(t, J, numpecas1, numpecas2);
								//SO COME 2 VEZES
								while (resp!='n' || resp!='N')
								{
									if (((t->tabu[z+1][w+1]=='x') || (t->tabu[z+1][w+1]=='X') || (t->tabu[z+1][w-1]=='x') || (t->tabu[z+1][w-1]=='X')) && ((t->tabu[z+2][w-2]==' ') || (t->tabu[z+2][w+2]==' ')))
									{
										cout<<J->Jogador1<<endl<<endl;
										cout<<"Deseja comer novamente? Se sim digite 's', se nao 'n'.\n";;
										cin>>resp;
										if (resp=='s' || resp=='S')
										{
											cout<<"Digite as coordenadas do destino para o qual deseja movimentar novamente, linha e coluna:\n";
											cin>>m>>n;
											if (t->tabu[m][n]!=' ')
											{
												cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
												Sleep(2000);
											}
											else
											{
												if (m==7 && t->tabu[z][w]=='o')//VIRA DAMA
												{
													t->tabu[z][w]='O';
												}
												t->tabu[m][n] = t->tabu[z][w];
												t->tabu[z][w] = ' ';
												if (w-n == 2)
												{
													t->tabu[m-1][n+1]=' ';
												}
												else if (w-n == -2)
												{
													t->tabu[m-1][n-1]=' ';
												}
												(*numpecas2)--;//DIMINUI NUMERO DE PECAS JOGADOR 2
												MostraTab(t, J, numpecas1, numpecas2);
												z=m;
												w=n;
											}
										}
										else if (resp=='n')
										{
											break;
										}
									}
									else
									{
										break;
									}
								}
								MostraTab(t, J, numpecas1, numpecas2);
								k++;
							}
						}
					}
				}
				if (t->tabu[x][y] == 'O')//SE FOR DAMA // TO AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
				{
					cout<<"Digite as coordenadas do destino para o qual deseja movimenta-la, linha e coluna:\n";
					cin>>z>>w;
					if (t->tabu[z][w] != ' ' || z>7 || w>7 || z<0 || w<0)
					{
						cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
						Sleep(1800);
						MostraTab(t, J, numpecas1, numpecas2);
					}
					else
					{
						if((((z-x == 1) && (w-y == 1 || w-y == -1)) || ((z-x == -1) && (w-y == 1 || w-y == -1))) && (t->tabu[z][w] == ' '))
						{
							t->tabu[z][w] = t->tabu[x][y];
							t->tabu[x][y] = ' ';
							MostraTab(t, J, numpecas1, numpecas2);
							k++;
						}
						else if (((z-x == 2 || (z-x == -2)) && (w-y == 2 || w-y == -2)) && (((t->tabu[x+1][y+1]=='x') || (t->tabu[x+1][y+1]=='X')) || ((t->tabu[x+1][y-1]=='x') || (t->tabu[x+1][y-1]=='X')) || ((t->tabu[x-1][y-1]=='x') || (t->tabu[x-1][y-1]=='X')) || ((t->tabu[x-1][y+1]=='x') || (t->tabu[x-1][y+1]=='X'))) && (t->tabu[z][w]==' '))
						{
							t->tabu[z][w] = t->tabu[x][y];
							t->tabu[x][y] = ' ';
							if(z-x==2)
							{
								if (w-y == 2)
								{
									t->tabu[x+1][y+1]=' ';
								}
								else if (w-y == -2)
								{
									t->tabu[x+1][y-1]=' ';
								}
							}
							else if (z-x==-2)
							{
								if (w-y == 2)
								{
									t->tabu[x-1][y+1]=' ';
								}
								else if (w-y == -2)
								{
									t->tabu[x-1][y-1]=' ';
								}
							}
							(*numpecas2)--;//DIMINUI NUMERO DE PECAS JOGADOR 2
							MostraTab(t, J, numpecas1, numpecas2);
							while (resp!='n' || resp!='N')
							{
								if (((t->tabu[z+1][w+1]=='x') || (t->tabu[z+1][w+1]=='X') || (t->tabu[z+1][w-1]=='x') || (t->tabu[z+1][w-1]=='X') || (t->tabu[z-1][w-1]=='x') || (t->tabu[z-1][w-1]=='X') || (t->tabu[z-1][w+1]=='x') || (t->tabu[z-1][w+1]=='X')) && ((t->tabu[z+2][w-2]==' ') || (t->tabu[z+2][w+2]==' ') || (t->tabu[z-2][w-2]==' ') || (t->tabu[z-2][w+2]==' ')) && ((z-x == 2 || (z-x == -2))))//TO AQUI
								{
									cout<<J->Jogador1<<endl<<endl;
									cout<<"Deseja comer novamente? Se sim digite 's', se nao 'n'.\n";;
									cin>>resp;
									if (resp=='s' || resp=='S')
									{
										cout<<"Digite as coordenadas do destino para o qual deseja movimentar novamente, linha e coluna:\n";
										cin>>m>>n;
										if (t->tabu[m][n]!=' ')
										{
											cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
											Sleep(2000);
										}
										else
										{
											t->tabu[m][n] = t->tabu[z][w];
											t->tabu[z][w] = ' ';
											if(m-z==2)//VER
											{
												if (w-n == 2)
												{
													t->tabu[m-1][n+1]=' ';
												}
												else if (w-n == -2)
												{
													t->tabu[m-1][n-1]=' ';
												}
											}												
											if(m-z==-2)//VER
											{
												if (w-n == 2)
												{
													t->tabu[m+1][n+1]=' ';
												}
												else if (w-n == -2)
												{
													t->tabu[m+1][n-1]=' ';
												}
											}
											(*numpecas2)--;//DIMINUI NUMERO DE PECAS JOGADOR 2
											MostraTab(t, J, numpecas1, numpecas2);
											z=m;
											w=n;
										}
									}
									else if (resp=='n')
									{
										break;
									}
								}
								else
								{
									break;
								}
							}
							MostraTab(t, J, numpecas1, numpecas2);
							k++;
						}
					}
				}
            }
			else
            {
                cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
                Sleep(2500);
                MostraTab(t, J, numpecas1, numpecas2);
            }
		}
		else //VEZ DO JOGADOR 2
		{
            cout<<"VEZ DE: "<<J->Jogador2<<endl<<endl;
            cout<<"Digite as coordenadas da peca que deseja movimentar, linha e coluna:\n";
            cin>>x>>y;
            if (t->tabu[x][y] == 'x' || t->tabu[x][y] == 'X')
            {
				if (t->tabu[x][y]=='x')//SE FOR PECA NORMAL
				{
					cout<<"Digite as coordenadas do destino para o qual deseja movimenta-la, linha e coluna:\n";
					cin>>z>>w;
					if (t->tabu[z][w] != ' ' || z>7 || w>7 || z<0 || w<0)
					{
						cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
						Sleep(1800);
						MostraTab(t, J, numpecas1, numpecas2);
					}
					else 
					{
						if (z-x==-1)
						{
							if (((z-x==-1) && (w-y == 1 || w-y == -1)) && (t->tabu[z][w]==' '))//RESTRIÇAO DE MOVIMENTO
							{
								if (z==0 && t->tabu[x][y]=='x')//VIRA DAMA
								{
									t->tabu[x][y]='X';
								}
								t->tabu[z][w] = t->tabu[x][y];
								t->tabu[x][y] = ' ';
								MostraTab(t, J, numpecas1, numpecas2);
								k++;
							}
							else 
							{
								cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
								Sleep(2500);
								MostraTab(t, J, numpecas1, numpecas2);
							}
						}
						if(z-x==-2)
						{
							if (((z-x == -2) && (w-y == 2 || w-y == -2)) && ((t->tabu[x-1][y-1]=='o') || (t->tabu[x-1][y-1]=='O') || (t->tabu[x-1][y+1]=='o') || (t->tabu[x-1][y+1]=='O')) && (t->tabu[z][w]==' '))//COMER PEÇAS,PROBLEMA
							{
								if (z==7 && t->tabu[x][y]=='x')//VIRA DAMA
								{
									t->tabu[x][y]='X';
								}
								t->tabu[z][w] = t->tabu[x][y];
								t->tabu[x][y] = ' ';
								if (w-y == 2)
								{
									t->tabu[x-1][y+1]=' ';
								}
								else if (w-y == -2)
								{
									t->tabu[x-1][y-1]=' ';
								}
								(*numpecas1)--;//DIMINUI NUMERO DE PECAS JOGADOR 1
								MostraTab(t, J, numpecas1, numpecas2);
								while (resp!='n' || resp!='N')
								{
									if(((t->tabu[z-1][w-1]=='o') || (t->tabu[z-1][w-1]=='O') || (t->tabu[z-1][w+1]=='o') || (t->tabu[z-1][w+1]=='O')) && ((t->tabu[z-2][w-2]==' ') || (t->tabu[z-2][w+2]==' ')))//TO AQUIIIIIIIIIIIIII
									{
										cout<<J->Jogador2<<endl<<endl;
										cout<<"Deseja comer novamente? Se sim digite 's', se nao 'n'.\n";
										cin>>resp;
										if (resp=='s' || resp=='S')
										{
											cout<<"Digite as coordenadas do destino para o qual deseja movimentar novamente, linha e coluna:\n";
											cin>>m>>n;
											if (t->tabu[m][n]!=' ')
											{
												cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
												Sleep(2000);
											}
											else 
											{
												if (m==0 && t->tabu[z][w]=='x')//VIRA DAMA
												{
													t->tabu[z][w]='X';
												}
												t->tabu[m][n] = t->tabu[z][w];
												t->tabu[z][w] = ' ';
												if (w-n == 2)
												{
													t->tabu[m+1][n+1]=' ';
												}
												else if (w-n == -2)
												{
													t->tabu[m+1][n-1]=' ';
												}
												(*numpecas1)--;//DIMINUI NUMERO DE PECAS JOGADOR 2
												MostraTab(t, J, numpecas1, numpecas2);
												z=m;
												w=n;
											}
										}
										else if (resp=='n')
										{
											break;
										}
									}
									else
									{
										break;
									}
								}
								MostraTab(t, J, numpecas1, numpecas2);
								k++;
							}
						}
					}
				}
				if (t->tabu[x][y] == 'X')//SE FOR DAMA
				{
					cout<<"Digite as coordenadas do destino para o qual deseja movimenta-la, linha e coluna:\n";
					cin>>z>>w;
					if (t->tabu[z][w] != ' ' || z>7 || w>7 || z<0 || w<0)
					{
						cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
						Sleep(1800);
						MostraTab(t, J, numpecas1, numpecas2);
					}
					else
					{
						if((((z-x == 1) && (w-y == 1 || w-y == -1)) || ((z-x == -1) && (w-y == 1 || w-y == -1))) && (t->tabu[z][w] == ' '))
						{
							t->tabu[z][w] = t->tabu[x][y];
							t->tabu[x][y] = ' ';
							MostraTab(t, J, numpecas1, numpecas2);
							k++;
						}
						else if (((z-x == 2 || (z-x == -2)) && (w-y == 2 || w-y == -2)) && (((t->tabu[x+1][y+1]=='o') || (t->tabu[x+1][y+1]=='O')) || ((t->tabu[x+1][y-1]=='o') || (t->tabu[x+1][y-1]=='O')) || ((t->tabu[x-1][y-1]=='o') || (t->tabu[x-1][y-1]=='O')) || ((t->tabu[x-1][y+1]=='o') || (t->tabu[x-1][y+1]=='O'))) && (t->tabu[z][w]==' ')) 
						{
							t->tabu[z][w] = t->tabu[x][y];
							t->tabu[x][y] = ' ';
							if(z-x==2)
							{
								if (w-y == 2)
								{
									t->tabu[x+1][y+1]=' ';
								}
								else if (w-y == -2)
								{
									t->tabu[x+1][y-1]=' ';
								}
							}
							else if (z-x==-2)
							{
								if (w-y == 2)
								{
									t->tabu[x-1][y+1]=' ';
								}
								else if (w-y == -2)
								{
									t->tabu[x-1][y-1]=' ';
								}
							}
							(*numpecas1)--;//DIMINUI NUMERO DE PECAS JOGADOR 1
							MostraTab(t, J, numpecas1, numpecas2);
							while (resp!='n' || resp!='N')
							{
								if (((t->tabu[z+1][w+1]=='o') || (t->tabu[z+1][w+1]=='O') || (t->tabu[z+1][w-1]=='o') || (t->tabu[z+1][w-1]=='O') || (t->tabu[z-1][w-1]=='o') || (t->tabu[z-1][w-1]=='O') || (t->tabu[z-1][w+1]=='o') || (t->tabu[z-1][w+1]=='O')) && ((t->tabu[z+2][w-2]==' ') || (t->tabu[z+2][w+2]==' ') || (t->tabu[z-2][w-2]==' ') || (t->tabu[z-2][w+2]==' ')) && ((z-x == 2 || (z-x == -2))))//TO AQUI
								{
									cout<<J->Jogador2<<endl<<endl;
									cout<<"Deseja comer novamente? Se sim digite 's', se nao 'n'.\n";;
									cin>>resp;
									if (resp=='s' || resp=='S')
									{
										cout<<"Digite as coordenadas do destino para o qual deseja movimentar novamente, linha e coluna:\n";
										cin>>m>>n;
										if (t->tabu[m][n]!=' ')
										{
											cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
											Sleep(2000);
										}
										else
										{
											t->tabu[m][n] = t->tabu[z][w];
											t->tabu[z][w] = ' ';
											if(m-z==2)//VER
											{
												if (w-n == 2)
												{
													t->tabu[m-1][n+1]=' ';
												}
												else if (w-n == -2)
												{
													t->tabu[m-1][n-1]=' ';
												}
											}												
											if(m-z==-2)//VER
											{
												if (w-n == 2)
												{
													t->tabu[m+1][n+1]=' ';
												}
												else if (w-n == -2)
												{
													t->tabu[m+1][n-1]=' ';
												}
											}
											(*numpecas1)--;//DIMINUI NUMERO DE PECAS JOGADOR 1
											MostraTab(t, J, numpecas1, numpecas2);
											z=m;
											w=n;
										}
									}
									else if (resp=='n')
									{
										break;
									}
								}
								else
								{
									break;
								}
							}
							MostraTab(t, J, numpecas1, numpecas2);
							k++;
						}
					}
				}
			}
			else
            {
                cout<<"JOGADA INVALIDA. Tente novamente."<<endl<<endl;
                Sleep(2500);
                MostraTab(t, J, numpecas1, numpecas2);
            }
        }
	}while ((*numpecas1)!=0 || (*numpecas2)!=0);
	if ((*numpecas2) == 0)
	{
		system("cls");
		cout<<endl<<endl<<"                                                         "<<J->Jogador1<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"                                                    VOCE FOI O"<<endl<<endl;
		cout<<"                    ##      ##  ########  ####   ##  ########  ########  ######     ########  #######   ##"<<endl;
		Sleep(50);
		cout<<"                     ##    ##   ##        ## ##  ##  ##        ##        ##    ##   ##    ##  ##    ##  ##"<<endl;
		Sleep(50);
		cout<<"                      ##  ##    ######    ##  ## ##  ##        ######    ##     ##  ##    ##  #######   ##"<<endl;
		Sleep(50);
		cout<<"                       ####     ##        ##   ####  ##        ##        ##    ##   ##    ##  ## ##       "<<endl;
		Sleep(50);
		cout<<"                        ##      ########  ##    ###  ########  ########  ######     ########  ##   ##   ##"<<endl;
		Sleep(5000);
	}
	else if ((*numpecas1) == 0)
	{
		system("cls");
		cout<<endl<<endl<<"                                                         "<<J->Jogador2<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"                                                    VOCE FOI O"<<endl<<endl;
		cout<<"                    ##      ##  ########  ####   ##  ########  ########  ######     ########  #######   ##"<<endl;
		Sleep(50);
		cout<<"                     ##    ##   ##        ## ##  ##  ##        ##        ##    ##   ##    ##  ##    ##  ##"<<endl;
		Sleep(50);		
		cout<<"                      ##  ##    ######    ##  ## ##  ##        ######    ##     ##  ##    ##  #######   ##"<<endl;
		Sleep(50);
		cout<<"                       ####     ##        ##   ####  ##        ##        ##    ##   ##    ##  ## ##       "<<endl;
		Sleep(50);
		cout<<"                        ##      ########  ##    ###  ########  ########  ######     ########  ##   ##   ##"<<endl;
		Sleep(5000);
	}
	system("cls");
}
