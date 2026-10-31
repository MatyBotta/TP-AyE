#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdlib.h>
#include "comun.h"
#include "listaD.h"

/*
 * Arbol binario de busqueda usado como INDICE de la LRU cache.
 * Cada nodo del arbol referencia al nodo de la lista (tNodoD) que contiene el
 * dato con esa clave. El arbol NO es dueño de los datos ni de los nodos de la
 * lista: solo libera sus propios nodos.
 *
 * 'cmp' es la funcion de comparacion del usuario: compara DATOS (no nodos).
 * El arbol baja al dato de cada nodo de la lista antes de llamarla.
 */
typedef struct sNodoArb
{
    tNodoD * nodo;              // nodo de la lista que contiene el dato con esta clave
    struct sNodoArb * izq;
    struct sNodoArb * der;
} tNodoArb;

typedef tNodoArb* tArbolBin;

void crearArbol (tArbolBin * pa);

// Inserta en el indice el nodo de la lista (ordenado por la clave de su dato).
// Devuelve TODO_BIEN, SIN_MEM o DUPLICADO (ya hay un nodo con esa clave).
int insertarOrdArbol (tArbolBin * pa, tNodoD * nodo, comparar cmp);

size_t alturaArbol (const tArbolBin * pa);

// Elimina la entrada del indice que esta en *p (no toca la lista ni el dato). 1 si pudo, 0 si estaba vacio.
int eliminarRaizArbol(tArbolBin * p);

// Elimina del indice la entrada con esa clave ('clave' es un dato con la clave cargada). 1 si existia, 0 si no.
int eliminarElemArbol(tArbolBin * p, const void * clave, comparar cmp);

tNodoArb ** menorNodoArbol(const tArbolBin * p);
tNodoArb ** mayorNodoArbol(const tArbolBin * p);

// Busca por clave. Devuelve el enlace que apunta al nodo del arbol (para poder eliminarlo), o NULL.
tNodoArb ** buscarNodoArbol(const tArbolBin * p, const void * clave, comparar cmp);

// Libera todos los nodos del arbol (no los datos ni los nodos de la lista). Devuelve cuantos libero.
int vaciarArbol(tArbolBin * pa);

#endif // ARBOL_H_INCLUDED
