#include "Menu.h"
#include "PortalDeInformacoes.h"
#include "CalendarioDeEventos.h"
#include "Usuario.h"
#include "Cadastro.h"
#include "Perfil.h"

void Menu::exibirMenu(Cadastro* cad, PortalDeInformacoes* port)
{
    int op;
    Usuario *user = new Usuario();
    do{
        cout<<"\n\n -------------Menu--------------"<<endl;
        cout<<" |                             |"<<endl;
        cout<<" | 1-Portal de Informacoes     |"<<endl;
        cout<<" | 2-Calendario de Eventos     |"<<endl;
        cout<<" | 3-Visualizar Perfil         |"<<endl;
        cout<<" | 4-Voltar ao inicio(deslogar)|"<<endl;
        cout<<" |                             |"<<endl;
        cout<<" -------------------------------"<<endl;
        cin>>op;

        switch(op)
        {
            case 1:
                abrirPortal(port,cad);
                break;
            case 2:
                abrirCalendario(user);
                break;
            case 3:
                user->verPerfil(cad);
                break;
            case 4:
                break;
            default:
                cout<<"Opcao Invalida! Tente novamente."<<endl;
                break;
        }
    }while(op != 4);
}

void Menu::abrirPortal(PortalDeInformacoes* port, Cadastro* cad)
{
    PortalDeInformacoes portal;
	Perfil p;
    int op;
    string info;
    do{
        cout<<"\n\n ----------Portal-----------"<<endl;
        cout<<" |                         |"<<endl;
        cout<<" | 1-Divulgar Informacao   |"<<endl;
        cout<<" | 2-Excluir Post          |"<<endl;
        cout<<" | 3-Visualizar Informacoes|"<<endl;
        cout<<" | 4-Voltar                |"<<endl;
        cout<<" |                         |"<<endl;
        cout<<" ---------------------------"<<endl;
        cin>>op;

        switch(op)
        {
            case 1:
				fflush(stdin);
                cout<<"\nInsira o seu post: ";
                getline(cin,info);
				fflush(stdin);
                port->divulgarInfo(info);
                break;
            case 2:
				port->visualizarInfos();
				p = cad->getPerfil();
				if(p.getAdm())
				{
					fflush(stdin);
					cout<<"\nInsira exatamente o post que deseja remover: ";
					getline(cin,info);
					port->excluirPost(info);
					fflush(stdin);
				}
				else
				{
					cout<<"\nVoce nao eh administrador. Sendo assim nao possui permissao para remover um post"<<endl;
				}
                break;
            case 3:
                port->visualizarInfos();
                break;
            case 4:
                break;
            default:
                cout<<"Opcao Invalida! Tente novamente."<<endl;
        }
    }while(op != 4);
}

void Menu::abrirCalendario(Usuario* u)
{
    //CONDICIONAL QUE VERIFICA TIPO DE USUARIO
    CalendarioDeEventos calendario;
	vector <Evento> vetor_evento;
	Evento ev;
	Data dt;
	Hora hr;
	Endereco end;
	
    int op, quant, i;
    do{
        cout<<"\n\n --------Calendario---------"<<endl;
        cout<<" |                         |"<<endl;
        cout<<" | 1-Sugerir Evento        |"<<endl;
        cout<<" | 2-Visualizar Eventos    |"<<endl;
        cout<<" | 3-Voltar                |"<<endl;
        cout<<" |                         |"<<endl;
        cout<<" ---------------------------"<<endl;
        cin>>op;

        switch(op)
        {
            case 1:
                calendario.sugerirEvento();
				ev = calendario.getEvento();
				vetor_evento.push_back(ev);
                break;
            case 2:
				quant = vetor_evento.size();
				if (quant == 0)
				{
					cout<<"\nNao ha nenhum evento cadastrado ainda."<<endl;
				}
				for(i=0;i<quant;i++)
				{
					cout<<"\n----Evento "<<i+1<<"----"<<endl;
					cout<<"\nNome do Evento: "<<vetor_evento[i].getNome()<<endl;
					dt = vetor_evento[i].getData();
					hr = vetor_evento[i].getHorario();
					end = vetor_evento[i].getEndereco();
					cout<<"\nData: "<<dt.getDia()<<"/"<<dt.getMes()<<"/"<<dt.getAno()<<endl;
					cout<<"\nHora: "<<hr.getHora()<<":"<<fixed<<setprecision(2)<<hr.getMinuto()<<endl;
					cout<<"\nLocal: "<<end.getNomeLugar()<<endl;
					cout<<"\nEndereco: "<<end.getRua()<<" "<<end.getNumero()<<", "<<end.getBairro()<<", "<<end.getCidade()<<endl;
				}
                calendario.visualizarCalendario();
                break;
            case 3:
                break;
            default:
                cout<<"Opcao Invalida! Tente novamente."<<endl;
        }
    }while(op != 3);
    desalocaUser(u);
}

void Menu::desalocaUser(Usuario* u)
{
    delete u;
}
