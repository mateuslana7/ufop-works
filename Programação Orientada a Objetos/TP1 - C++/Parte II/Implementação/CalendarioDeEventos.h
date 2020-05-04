#ifndef CALENDARIODEEVENTOS_H
#define CALENDARIODEEVENTOS_H

#include "Evento.h"

class CalendarioDeEventos
{
    public:
        Evento getEvento() { return evento; }
        void visualizarCalendario();
        void setEvento(Evento ev) { evento = ev; }
        void sugerirEvento();
    private:
        Evento evento;
};

#endif
