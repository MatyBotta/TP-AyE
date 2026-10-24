#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comun.h"

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

/// Primitivas
// Administrativas
void crearLista(tLista *pl);
int listaVacia(tLista *pl);
int listaLlena(const tLista *pl, size_t tamDato);
void ordenar(tLista *pl, int (*comparar)(const void *, const void *));

// Insertar
int ponerAlComienzo(tLista *pl, const void *pd, size_t tamDato);
int ponerAlFinal(tLista *pl,const void *pd, size_t tamDato);
int ponerEnOrden(tLista *pl, const void *pd, size_t tamElem,int (*comparar)(const void*,const void*), int (*acomular)(void**, size_t *, const void *, size_t));

// Ver
int verPrimeroLista(const tLista *pl, void *pd, size_t tamDato);
int verUltimoLista(const tLista *pl, void *pd, size_t tamDato);

// Sacar
int sacarPrimeroLista(tLista *pl, void *pd, size_t tamDato);
int sacarUltimoLista(tLista *pl, void * dst, size_t tamDst);
int eliminarUltimoLista(tLista * pl);
void vaciarLista(tLista *pl);

// Mostrar
int mostrarLista(const tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp);
int mostrarListaAlReves(const tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp);
int mostrarListaAlRevesYVaciar(tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp);


#endif // LISTA_H_INCLUDED
