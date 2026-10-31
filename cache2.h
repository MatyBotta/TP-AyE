#ifndef CACHE2_H_INCLUDED
#define CACHE2_H_INCLUDED

#include <stddef.h>
#include "listaD.h"
#include "arbol.h"

typedef struct
{
    tListaD lista;
    tArbolBin indice;
    unsigned cap;
    unsigned ce;
    comparar cmp;
} tLRU2;

void crear_lrucache2(tLRU2 *pl, unsigned cap, comparar cmp);

int agregar_lrucache2(tLRU2 *pl, const void *pd, size_t tamDato);

void *obtener_lrucache2(tLRU2 *pl, const void *pd);

int borrar_lrucache2(tLRU2 *pl, const void *pd);

void vaciar_lrucache2(tLRU2 *pl);

size_t altura_lrucache2(const tLRU2 *pl);

#endif // CACHE2_H_INCLUDED
