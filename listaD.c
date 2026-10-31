#include <string.h>
#include "listaD.h"

void crearListaD (tListaD * pl)
{
    pl->pri = NULL;
    pl->ult = NULL;
}

tNodoD * insertarPrimeroListaD (tListaD * pl, const void * dato, size_t tamDato)
{
    tNodoD * nue = (tNodoD*)malloc(sizeof(tNodoD));

    if(!nue || !(nue->info = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->info, dato, tamDato);
    nue->tamInfo = tamDato;
    nue->ant = NULL;
    nue->sig = pl->pri;

    if(pl->pri)
        pl->pri->ant = nue;
    else
        pl->ult = nue;

    pl->pri = nue;

    return nue;
}

int eliminarNodoListaD (tListaD * pl, tNodoD * nodo)
{
    if(!nodo)
        return ERR_ARG;

    if(nodo->ant)
        nodo->ant->sig = nodo->sig;
    else
        pl->pri = nodo->sig;    // era el primero

    if(nodo->sig)
        nodo->sig->ant = nodo->ant;
    else
        pl->ult = nodo->ant;    // era el ultimo

    free(nodo->info);
    free(nodo);

    return TODO_BIEN;
}

int eliminarUltimoListaD (tListaD * pl)
{
    if(!pl->ult)
        return LISTA_VACIA;

    return eliminarNodoListaD(pl, pl->ult);
}

int moverAlComienzo (tListaD * pl, void * elem)
{
    tNodoD * nodo = (tNodoD*)elem;

    if(!nodo)
        return ERR_ARG;

    if(nodo == pl->pri)
        return TODO_BIEN;


    nodo->ant->sig = nodo->sig;

    if(nodo->sig)
        nodo->sig->ant = nodo->ant;
    else
        pl->ult = nodo->ant;

    nodo->ant = NULL;
    nodo->sig = pl->pri;
    pl->pri->ant = nodo;
    pl->pri = nodo;

    return TODO_BIEN;
}

int vaciarListaD(tListaD *pl)
{
    int cant = 0;
    tNodoD *act = pl->pri;

    while(act)
    {
        tNodoD *aux = act->sig;

        free(act->info);
        free(act);
        act = aux;
        cant++;
    }

    pl->pri = NULL;
    pl->ult = NULL;

    return cant;
}
