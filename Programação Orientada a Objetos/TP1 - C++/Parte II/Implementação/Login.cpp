#include "Login.h"
#include "Perfil.h"

void Login::fazerLogin(Cadastro* cad, Menu* menu, PortalDeInformacoes* port)
{
    cout<<"\nLogin efetuado com sucesso!"<<endl;
    menu->exibirMenu(cad,port);
}
