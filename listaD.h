#ifndef LISTAD_H_INCLUDED
#define LISTAD_H_INCLUDED

#include <stdlib.h>
#include "comun.h"

typedef struct sNodoD
{
    void * info;
    size_t tamInfo;
    struct sNodoD * sig;
    struct sNodoD * ant;
} tNodoD;

typedef struct
{
    tNodoD * pri;
    tNodoD * ult;
} tListaD;

void crearListaD (tListaD * pl);
int insertarPrimeroListaD (tListaD * pl, const void * dato, size_t tamDato);
int eliminarUltimoListaD (tListaD * pl);

#endif // LISTAD_H_INCLUDED
