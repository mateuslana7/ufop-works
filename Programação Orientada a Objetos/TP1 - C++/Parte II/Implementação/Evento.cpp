#include "Evento.h"

void Evento::criarEvento()
{
    int dia, mes, ano, hora, minuto, numero=0;
    string nomeEv, nomeLocal, cidade, bairro, rua;

    cout<<"\n-----Sugerindo Evento-----"<<endl;
    fflush(stdin);
    cout<<"\nNome: ";
    getline(cin,nomeEv);
    setNome(nomeEv);
	
	//CONTROLE DA ENTRADA
	int i=0;
	do
	{
		if(i>0)
		{
			cout<<"\nERRO! Algum dos parametros esta invalido."<<endl;
		}
		cout<<"\n--Data--"<<endl;
		cout<<"\nDia: ";
		cin>>dia;
		cout<<"\nMes: ";
		cin>>mes;
		cout<<"\nAno: ";
		cin>>ano;
		i++;
	}while((mes<2 || mes>12) || (dia<0 || dia>31) || (ano<2017));
	
	data.setDia(dia);
	data.setMes(mes);
	data.setAno(ano);
	
	i=0;
	do
	{
		if(i>0)
		{
			cout<<"\nERRO! Algum dos parametros esta invalido."<<endl;
		}
		cout<<"\n--Hora--"<<endl;
		cout<<"\nHora(s): ";
		cin>>hora;
		cout<<"\nMinuto(s): ";
		cin>>minuto;
		i++;
	}while((hora<0 || hora>23) || (minuto<0 || minuto>59));
    
    horario.setHora(hora);
    horario.setMinuto(minuto);
	setEndereco(nomeLocal,cidade,bairro,rua,numero);
    cout<<"\nEvento sugerido."<<endl;
}

void Evento::setEndereco(string nomeLocal, string cidade, string bairro, string rua, int numero)
{
	fflush(stdin);
    cout<<"\nNome do lugar: ";
    getline(cin,nomeLocal);
	endereco.setNomeLugar(nomeLocal);
	cout<<"\nCidade: ";
	getline(cin,cidade);
	endereco.setCidade(cidade);
	cout<<"\nBairro: ";
	getline(cin,bairro);
	endereco.setBairro(bairro);
	cout<<"\nRua: ";
	getline(cin,rua);
	endereco.setRua(rua);
	cout<<"\nNumero: ";
	cin>>numero;
	endereco.setNumero(numero);
	fflush(stdin);
}
