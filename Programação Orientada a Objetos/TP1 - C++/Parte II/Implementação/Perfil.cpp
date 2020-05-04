#include "Perfil.h"

Perfil::Perfil()
{
    adm = false;
}

void Perfil::criarPerfil()
{
    string nome, email, senha;
    char sexo;
    int dia, mes, ano;

    cout<<"\n-----Cadastro-----"<<endl;
    fflush(stdin);
    cout<<"\nNome: ";
    getline(cin,nome);
    setNome(nome);
    cout<<"\nE-mail: ";
    getline(cin, email);
    setEmail(email);
    cout<<"\nSenha: ";
    getline(cin,senha);
    setSenha(senha);
    cout<<"\nSexo(M ou F): ";
    cin>>sexo;
    fflush(stdin);
    setSexo(sexo);

    //CONTROLE DA ENTRADA
	int i=0;
	do
	{
		if(i>0)
		{
			cout<<"\nERRO! Algum dos parametros esta invalido."<<endl;
		}
		cout<<"\nData de nascimento: "<<endl;
		cout<<"\nDia: ";
		cin>>dia;
		cout<<"\nMes: ";
		cin>>mes;
		cout<<"\nAno: ";
		cin>>ano;
		i++;
	}while((mes<1 || mes>12) || (dia<0 || dia>31) || (ano<1900));
	
	dataNasc.setMes(mes);
	dataNasc.setDia(dia);
	dataNasc.setAno(ano);
}
