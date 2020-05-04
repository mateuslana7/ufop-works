#include "Menu.h"
#include "Cadastro.h"
#include "Perfil.h"
#include "Login.h"
#include "PortalDeInformacoes.h"

int main()
{
    Menu* menuDeOpcoes = new Menu();
    Cadastro* cadastro = new Cadastro();
    Login* login = new Login();
	PortalDeInformacoes* portal = new PortalDeInformacoes();
	
	
	vector <Perfil> vetor_perfil;
	Perfil p;
	int quant, id=0, i, cont=0;
    int op;
    string email, senha;
	vector<Perfil>::const_iterator it;  
	bool flag = true;

    do{
        cout<<"\n\n ------Pagina Inicial-------"<<endl;
        cout<<" |                         |"<<endl;
        cout<<" | 1-Login                 |"<<endl;
        cout<<" | 2-Cadastrar-se          |"<<endl;
        cout<<" | 3-Sair                  |"<<endl;
        cout<<" |                         |"<<endl;
        cout<<" ---------------------------"<<endl;
        cin>>op;

        switch(op)
        {
            case 1:
                cout<<"\n-----Login-----"<<endl;
                fflush(stdin);
                cout<<"\nEmail: ";
                getline(cin,email);
                login->setEmail(email);
                cout<<"\nSenha: ";
                getline(cin,senha);
                login->setSenha(senha);
                fflush(stdin);
				
				quant = vetor_perfil.size();
				for(i=0; i<quant; i++)
				{
					if(email == vetor_perfil[i].getEmail() && senha == vetor_perfil[i].getSenha())
					{
						cadastro->setPerfil(vetor_perfil[i]);
						login->fazerLogin(cadastro,menuDeOpcoes,portal);
						id++;
					}
				}
				if(id==0)
				{
					cout<<"\nEmail ou senha inavalido(s)"<<endl;
				}
                id=0;
                break;
            case 2:
                cadastro->efetuarCadastro(menuDeOpcoes);
				p = cadastro->getPerfil();
				if(cont == 0)
				{
					p.setAdm(flag);
					cont++;
				}
				vetor_perfil.push_back(p);	
                break;
            case 3:
                break;
            default:
                cout<<"Opcao Invalida! Tente novamente."<<endl;
                break;
        }
    }while(op != 3);

    delete menuDeOpcoes;
    delete cadastro;
    delete login;

    return 0;
}
