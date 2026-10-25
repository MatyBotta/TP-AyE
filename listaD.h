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

typedef tNodoD* tListaD;

void crearListaD(tListaD * pl);

#endif // LISTAD_H_INCLUDED
