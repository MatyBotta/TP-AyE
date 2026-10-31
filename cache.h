#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

#include "lista.h"

typedef struct{
    tLista pri;
    unsigned cap;
    unsigned ce;
    comparar cmp;
} tLRU;

void crear_lrucache(tLRU *pl, unsigned cap, comparar cmp);
int agregar_lrucache(tLRU *pl, void *pd, size_t tamDato);
void *obtener_lrucache(tLRU *pl, void *pd);
int borrar_lrucache(tLRU *pl, void *pd);
void vaciar_lrucache(tLRU *pl);

#endif // CACHE_H_INCLUDED
