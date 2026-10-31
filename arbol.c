#include "arbol.h"

void crearArbol (tArbolBin * pa)
{
    *pa = NULL;
}

int insertarOrdArbol (tArbolBin * pa, tNodoD * nodo, comparar cmp)
{
    int comparacion;
    tNodoArb * nue;

    while(*pa)
    {
        if((comparacion = cmp((*pa)->nodo->info, nodo->info)) < 0)
            pa = &(*pa)->der;
        else if(comparacion > 0)
            pa = &(*pa)->izq;
        else
            return DUPLICADO;
    }

    if(!(nue = (tNodoArb*)malloc(sizeof(tNodoArb))))
        return SIN_MEM;

    nue->nodo = nodo;
    nue->der = nue->izq = NULL;
    *pa = nue;

    return TODO_BIEN;
}

size_t alturaArbol (const tArbolBin * pa)
{
    size_t hi, hd;

    if(!*pa)
        return 0;

    hi = alturaArbol(&(*pa)->izq);
    hd = alturaArbol(&(*pa)->der);

    return ((hi > hd) ? (hi) : (hd)) + 1;
}

int eliminarRaizArbol(tArbolBin * p)
{
    tNodoArb ** remp,
             * elim;

    if(!*p)
        return 0; ///ARBOL_VACIO

    if (!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p = NULL;
        return 1; ///OK
    }

    remp = alturaArbol(&(*p)->izq)>alturaArbol(&(*p)->der)?
        mayorNodoArbol(&(*p)->izq):
        menorNodoArbol(&(*p)->der);

    elim = *remp;
    (*p)->nodo = elim->nodo;

    *remp = elim->izq ? elim->izq : elim->der;

    free(elim);

    return 1; ///OK
}

int eliminarElemArbol(tArbolBin * p, const void * clave, comparar cmp)
{
    tNodoArb ** pn = buscarNodoArbol(p, clave, cmp);

    if(!pn)
        return 0; ///NO_EXISTE

    return eliminarRaizArbol(pn);
}

tNodoArb ** mayorNodoArbol(const tArbolBin * p)
{
    if(!*p)
        return NULL;
    while((*p)->der)
        p = &(*p)->der;
    return (tNodoArb **) p;
}

tNodoArb ** buscarNodoArbol(const tArbolBin * p, const void * clave, comparar cmp)
{
    int rc;

    while(*p && (rc = cmp(clave, (*p)->nodo->info)))
    {
        if(rc < 0)
            p = &(*p)->izq;
        else
            p = &(*p)->der;
    }

    if(!*p)
        return NULL;

    return (tNodoArb **)p;
}

tNodoArb ** menorNodoArbol(const tArbolBin * p)
{
    if(!*p)
        return NULL;
    while((*p)->izq)
        p = &(*p)->izq;
    return (tNodoArb **) p;
}

int vaciarArbol(tArbolBin * pa) // No terminé de entender
{
    int cant = 0;
    tNodoArb * act = *pa,
             * aux;

    while(act)
    {
        if(act->izq)
        {
            aux = act->izq;
            act->izq = aux->der;
            aux->der = act;
            act = aux;
        }
        else
        {
            aux = act->der;
            free(act);
            act = aux;
            cant++;
        }
    }

    *pa = NULL;

    return cant;
}
