#include "cache.h"

void crear_lrucache(tLRU *pl, unsigned cap, comparar cmp)
{
    pl->pri = NULL;
    pl->ce = 0;
    pl->cap = cap;
    pl->cmp = cmp;

}

int agregar_lrucache(tLRU *pl, void *pd, size_t tamDato)
{
    borrar_lrucache(pl, pd);

    if(pl->cap == pl->ce)
    {
        eliminarUltimoLista(&(pl->pri));
        pl->ce--;
    }

    if(!ponerAlComienzo(&(pl->pri), pd, tamDato))
        return 0;
    else
        pl->ce++;
    return 1;

}

int borrar_lrucache(tLRU *pl, void *pd)
{
    tLista *aux = &(pl->pri);
    tNodo *elim;

    while (*aux && pl->cmp(pd, (*aux)->info) != 0)
        aux = &(*aux)->sig;

    if (*aux == NULL)
        return 0;

    elim = *aux;
    *aux = elim->sig;
    free(elim->info);
    free(elim);
    pl->ce--;
    return 1;
}

void *obtener_lrucache(tLRU *pl, void *pd)
{
    tLista *aux = &(pl->pri);
    tNodo *nodo;

    while (*aux && pl->cmp(pd, (*aux)->info) != 0)
        aux = &(*aux)->sig;

    if (*aux == NULL)
        return NULL;

    nodo = *aux;
    *aux = nodo->sig;
    nodo->sig = pl->pri;
    pl->pri = nodo;

    return nodo->info;
}

void vaciar_lrucache(tLRU *pl)
{
    vaciarLista(&(pl->pri));
    pl->ce = 0;
}
