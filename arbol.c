#include <string.h>
#include "arbol.h"

void crearArbol (tArbolBin * pa)
{
    *pa = NULL;
}

int insertarOrdArbol (tArbolBin * pa, const void * info, size_t tamInfo, comparar cmp)
{
    int comparacion;
    tNodoArb * nue = (tNodoArb*)malloc(sizeof(tNodoArb));
    if(!nue || !(nue->info = malloc(tamInfo)))
    {
        free(nue);
        return SIN_MEM;
    }

    while(*pa)
    {
        if((comparacion = cmp((*pa)->info, info)) < 0)
            pa = &(*pa)->der;
        else if(comparacion > 0)
            pa = &(*pa)->izq;
        else
            return DUPLICADO;
    }

    memcpy(nue->info, info, tamInfo);
    nue->tamInfo = tamInfo;
    nue->der = nue->izq = NULL;
    *pa = nue;

    return TODO_BIEN;
}

size_t alturaArbol (const tArbolBin * pa)
{
    int hi, hd;

    if(!pa)
        return 0;

    hi = alturaArbol(&(*pa)->izq);
    hd = alturaArbol(&(*pa)->izq);

    return ((hi > hd) ? (hi) : (hd)) + 1;
}
