#ifndef PORTALDEINFORMACOES_H
#define PORTALDEINFORMACOES_H

#include "Menu.h"

class PortalDeInformacoes
{
    public:
        void divulgarInfo(string);
        void excluirPost(string);
        void visualizarInfos();
    private:
        stack<string> pilha_info;
};

#endif 
