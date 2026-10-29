#include <string.h>
#include "listaD.h"

void crearListaD (tListaD * pl)
{
    pl->pri = NULL;
    pl->ult = NULL;
}

int insertarPrimeroListaD (tListaD * pl, const void * dato, size_t tamDato)
{
    tNodoD * nue = (tNodoD*)malloc(sizeof(tNodoD));
    if(!nue || !(nue->info = malloc(tamDato)))
    {
        free(nue);
        return SIN_MEM;
    }

    nue->ant = NULL;
    nue->sig = pl->pri;

    if(pl->pri)
    {
        pl->pri->ant = nue;
    }

    pl->pri = nue;

    return TODO_BIEN;
}

int eliminarUltimoListaD (tListaD * pl)
{
    tNodoD * elim = pl->ult;

    if(!elim)
        return LISTA_VACIA;

    elim->ant->sig = NULL;

    free(elim->info);
    free(elim);

    return TODO_BIEN;
}

int moverAlComienzo (tListaD * pl, void * elem)
{
    if(!elem)
        return ERR_ARG;

    tNodoD * nodo = (tNodoD*)elem;

    nodo->ant->sig = nodo->sig;
    nodo->sig->ant = nodo->ant;

    nodo->ant = NULL;
    nodo->sig = pl->pri;

    pl->pri = nodo;

    return TODO_BIEN;
}
