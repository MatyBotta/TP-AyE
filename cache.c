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
        sacarUltimoLista(&(pl->pri));
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

void *obtener_lrucache(tLRU *pl, void *pd, size_t tamDato)
{
    void *info = ElimCod(pl, pd, tamDato);

    if(!info)
        return NULL;

    if(!ponerAlComienzo(&(pl->pri), info, tamDato))
    {
        free(info);
        return NULL;
    }

    pl->ce++;
    return info;
}

void* ElimCod(tLRU *pl, void *pd, size_t tamDato)
{
    tLista *aux = &(pl->pri);
    tNodo *elim;
    void *info = malloc(tamDato);
    if(!info)
        return 0;

    while (*aux && pl->cmp(pd, (*aux)->info) != 0)
        aux = &(*aux)->sig;

    if (*aux == NULL)
    {
        free(info);
        return 0;
    }

    elim = *aux;
    *aux = elim->sig;
    memcpy(info, elim->info, MINIMO(tamDato, elim->tamInfo));
    free(elim->info);
    free(elim);
    pl->ce--;
    return info;
}

void vaciar_lrucache(tLRU *pl)
{
    vaciarLista(&(pl->pri));
    free(pl);
}
