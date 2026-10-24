#include "lista.h"

void crearLista(tLista *pl)
{
    *pl = NULL;
}

int sacarUltimoLista(tLista *pl)
{
    tLista *aux = pl;
    if(*aux == NULL)
        return 0;

    while((*aux)->sig)
        aux = &(*aux)->sig;
    free((*aux)->info);
    free(*aux);
    *aux = NULL;
    return 1;
}

int ponerAlComienzo(tLista *pl, const void *pd, size_t tamDato)
{
    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));

    if(nue == NULL || (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *pl;
    *pl = nue;
    return 1;
}

void vaciarLista(tLista *pl)
{
    while(*pl)
    {
        tNodo *aux = *pl;
        *pl = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int listaVacia(tLista *pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista *pl, size_t tamDato)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(tamDato);

    free(aux);
    free(info);

    return !aux || !info;
}

int sacarPrimeroLista(tLista *pl, void *pd, size_t tamDato)
{
    tNodo * aux = *pl;

    if(aux == NULL)
        return 0;
    *pl = aux->sig;
    memcpy(pd, aux->info, MINIMO(tamDato, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}

int verPrimeroLista(const tLista *pl, void *pd, size_t tamDato)
{
    if(*pl == NULL)
        return 0;

    memcpy(pd, (*pl)->info, MINIMO(tamDato, (*pl)->tamInfo));
    return 1;
}

int ponerAlFinal(tLista *pl,const void *pd, size_t tamDato)
{
    tNodo *nue;

    while(*pl)
        *pl = (*pl)->sig;

    if((nue = (tNodo*)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = NULL;
    *pl = nue;
    return 1;
}

int verUltimoLista(tLista *pl, void *pd, size_t tamDato)
{
    if(*pl == NULL)
        return 0;
    while((*pl)->sig)
        *pl = (*pl)->sig;
    memcpy(pd, (*pl)->info, MINIMO(tamDato, (*pl)->tamInfo));
    return 1;
}

int mostrarLista(const tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp)
{
    int cant = 0;
    while(*pl)
    {
        mostrar((*pl)->info, fp);
        pl = &(*pl)->sig;
        cant++;
    }
    return cant;
}

int mostrarListaAlReves(const tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp)
{
    if(*pl)
    {
        int n = mostrarListaAlReves(&(*pl)->sig, mostrar, fp);

        mostrar((*pl)->info, fp);
        return n + 1;
    }
    return 0;
}

int mostrarListaAlRevesYVaciar(tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp)
{
    if(*pl)
    {
        int n = mostrarListaAlReves(&(*pl)->sig, mostrar, fp);

        mostrar((*pl)->info, fp);
        free((*pl)->info);
        free(*pl);
        *pl = NULL;
        return n + 1;
    }
    return 0;
}

int ponerEnOrden(tLista *pl, const void *pd, size_t tamElem,int (*comparar)(const void*,const void*),
                 int (*acomular)(void**, size_t *, const void *, size_t))
{
    tNodo *nue;

    while(*pl && comparar((*pl)->info, pd) < 0)
        pl = &(*pl)->sig;
    if(*pl && comparar((*pl)->info, pd) == 0)
    {
        if(acomular)
        {
            if(!acomular(&(*pl)->info, &(*pl)->tamInfo, pd, tamElem))
                return SIN_MEM;
            return CLA_DUP;
        }
    }
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(tamElem)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, pd, tamElem);
    nue->tamInfo = tamElem;
    nue->sig = *pl;
    *pl = nue;
    return TODO_BIEN;
}

void ordenar(tLista *pl, int (*comparar)(const void *, const void *))
{
    tLista * pri = pl;

    if(*pl == NULL)
        return;
    while((*pl)->sig)
    {
        if(comparar((*pl)->info, (*pl)->sig->info) > 0)
        {
            tLista *q = pri;
            tNodo *aux = (*pl)->sig;

            (*pl)->sig = aux->sig;
            while(comparar((*q)->info, aux->info) <= 0)
                q = &(*q)->sig;
            aux->sig = *q;
            *q = aux;
        }
        else
        {
            pl = &(*pl)->sig;
        }
    }
}
