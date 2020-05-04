#include "Administrador.h"

void Administrador::verPerfil(Cadastro* cad)
{
    Perfil p;
    Data d;
    p = cad->getPerfil();
    d = p.getDataNasc();
    cout<<"\n-----Perfil-----"<<endl;
    cout<<"\nNome: "<<p.getNome()<<endl;
    cout<<"\nE-mail: "<<p.getEmail()<<endl;
    cout<<"\nSexo(M ou F): "<<p.getSexo()<<endl;
    cout<<"\nData de nascimento: "<<d.getDia()<<"/"<<d.getMes()<<"/"<<d.getAno()<<endl;
    cout<<"Permissao de administrador: ";
    if(p.getAdm()){
        cout<<"Sim"<<endl;
    }
    else {
        cout<<"Nao"<<endl;
    }
}