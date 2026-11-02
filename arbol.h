#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdlib.h>
#include "comun.h"
#include "listaD.h"


typedef struct sNodoArb
{
    tNodoD * nodo;
    struct sNodoArb * izq;
    struct sNodoArb * der;
} tNodoArb;

typedef tNodoArb* tArbolBin;

void crearArbol (tArbolBin * pa);


int insertarOrdArbol (tArbolBin * pa, tNodoD * nodo, comparar cmp);

size_t alturaArbol (const tArbolBin * pa);

int eliminarRaizArbol(tArbolBin * p);

int eliminarElemArbol(tArbolBin * p, const void * clave, comparar cmp);

tNodoArb ** menorNodoArbol(const tArbolBin * p);
tNodoArb ** mayorNodoArbol(const tArbolBin * p);

tNodoArb ** buscarNodoArbol(const tArbolBin * p, const void * clave, comparar cmp);

int vaciarArbol(tArbolBin * pa);

#endif // ARBOL_H_INCLUDED
