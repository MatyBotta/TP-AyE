#include <string.h>
#include "cache2.h"


static void descartarUltimo(tLRU2 *pl)
{
    eliminarElemArbol(&pl->indice, pl->lista.ult->info, pl->cmp);
    eliminarUltimoListaD(&pl->lista);
    pl->ce--;
}

void crear_lrucache2(tLRU2 *pl, unsigned cap, comparar cmp)
{
    crearListaD(&pl->lista);
    crearArbol(&pl->indice);
    pl->cap = cap;
    pl->ce = 0;
    pl->cmp = cmp;
}

int agregar_lrucache2(tLRU2 *pl, const void *pd, size_t tamDato)
{
    tNodoArb **pn = buscarNodoArbol(&pl->indice, pd, pl->cmp);
    tNodoD *nodo;
    void *nuevo;

    if(pn)
    {
        nodo = (*pn)->nodo;

        if(!(nuevo = malloc(tamDato)))
            return 0;

        memcpy(nuevo, pd, tamDato);
        free(nodo->info);
        nodo->info = nuevo;
        nodo->tamInfo = tamDato;

        moverAlComienzo(&pl->lista, nodo);
        return 1;
    }

    if(pl->cap == 0)
        return 0;

    if(pl->ce == pl->cap)
        descartarUltimo(pl);

    if(!(nodo = insertarPrimeroListaD(&pl->lista, pd, tamDato)))
        return 0;

    if(insertarOrdArbol(&pl->indice, nodo, pl->cmp) != TODO_BIEN)
    {
        eliminarNodoListaD(&pl->lista, nodo);
        return 0;
    }

    pl->ce++;

    return 1;
}

void *obtener_lrucache2(tLRU2 *pl, const void *pd)
{
    tNodoArb **pn = buscarNodoArbol(&pl->indice, pd, pl->cmp);


    if(!pn)
        return NULL;

    moverAlComienzo(&pl->lista, (*pn)->nodo);

    return (*pn)->nodo->info;
}

int borrar_lrucache2(tLRU2 *pl, const void *pd)
{
    tNodoArb **pn = buscarNodoArbol(&pl->indice, pd, pl->cmp);
    tNodoD *nodo;

    if(!pn)
        return 0;

    nodo = (*pn)->nodo;

    eliminarRaizArbol(pn);
    eliminarNodoListaD(&pl->lista, nodo);
    pl->ce--;

    return 1;
}

void vaciar_lrucache2(tLRU2 *pl)
{
    vaciarArbol(&pl->indice);
    vaciarListaD(&pl->lista);
    pl->ce = 0;
}

size_t altura_lrucache2(const tLRU2 *pl)
{
    return alturaArbol(&pl->indice);
}
