#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdlib.h>
#include "comun.h"

typedef struct sNodoArb
{
    void * info;
    size_t tamInfo;
    struct sNodoArb * izq;
    struct sNodoArb * der;
} tNodoArb;

typedef tNodoArb* tArbolBin;

void crearArbol (tArbolBin * pa);
int insertarOrdArbol (tArbolBin * pa, const void * info, size_t tamInfo, comparar cmp);
size_t alturaArbol (const tArbolBin * pa);

#endif // ARBOL_H_INCLUDED
