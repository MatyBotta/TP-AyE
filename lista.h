#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

#define SIN_MEM     1
#define CLA_DUP     2
#define TODO_BIEN   0

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;
typedef int (*comparar)(const void* a, const void* b);

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
int verUltimoLista(tLista *pl, void *pd, size_t tamDato);

// Sacar
int sacarPrimeroLista(tLista *pl, void *pd, size_t tamDato);
int sacarUltimoLista(tLista *pl);
void vaciarLista(tLista *pl);

// Mostrar
int mostrarLista(const tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp);
int mostrarListaAlReves(const tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp);
int mostrarListaAlRevesYVaciar(tLista *pl, void(*mostrar)(const void*, FILE*), FILE *fp);


#endif // LISTA_H_INCLUDED
