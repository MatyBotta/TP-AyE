#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tweener.h"

int generarPosteos(const char *nombre)
{
    FILE *pf = fopen(nombre, "wb");
    tPosteo p;
    int i, j, largo;

    if(!pf)
        return 0;

    for(i = 0; i < CANT_POSTEOS; i++)
    {
        memset(&p, 0, sizeof(p));
        p.id = i;
        largo = 20 + rand() % 120;
        for(j = 0; j < largo; j++)
            p.texto[j] = (rand() % 6 == 0) ? ' ' : 'a' + rand() % 26;
        p.texto[largo] = '\0';
        fwrite(&p, sizeof(p), 1, pf);
    }
    fclose(pf);
    return 1;
}

int generarUsuarios(const char *nombre, tTipoLote tipo, unsigned int semilla)
{
    FILE *pf = fopen(nombre, "wb");
    tUsuario u;
    int i, j;
    int cantUsuarios;

    if (!pf)
        return 0;

    srand(semilla);

    cantUsuarios = MIN_REG + rand();

    for (i = 0; i < cantUsuarios; i++)
    {
        memset(&u, 0, sizeof(u));
        snprintf(u.usuario, TAM_USUARIO, "user_%03d", i);

        switch (tipo)
        {
            case LOTE_CONCENTRADO:
                for (j = 0; j < MAX_FEED; j++)
                    u.feed[j] = rand() % POOL_CONCENTRADO;
                break;

            case LOTE_DISPERSO:
                for (j = 0; j < MAX_FEED; j++)
                    u.feed[j] = rand() % CANT_POSTEOS;
                break;

            case LOTE_ORDENADO:
                {
                    int base = rand() % (CANT_POSTEOS - MAX_FEED * 2);
                    int paso  = 1 + rand() % 50;   // separación entre ids
                    for (j = 0; j < MAX_FEED; j++)
                        u.feed[j] = base + j * paso;
                }
                break;
        }

        fwrite(&u, sizeof(u), 1, pf);
    }

    fclose(pf);
    return 1;
}
