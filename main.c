#include <stdio.h>
#include <stdlib.h>
#include "tweener.h"

#define USUARIOS 5000

int main(int argc, char *argv[])
{
    unsigned int semilla = argc > 1 ? (unsigned int)atoi(argv[1]) : 1;
    int tams[] = {10, 50, 100, 500, 1000, 2000, 5000};
    const char *lotes[] = {"lote_concentrado.bin", "lote_disperso.bin", "lote_ordenado.bin"};
    tTipoLote tipos[] = {LOTE_CONCENTRADO, LOTE_DISPERSO, LOTE_ORDENADO};
    int i, j;

    srand(semilla);
    if (generarPosteos("posteos.bin") != TODO_BIEN)
        return 1;

    for (i = 0; i < 3; i++)
    {
        if (generarUsuarios(lotes[i], tipos[i], semilla, USUARIOS) != TODO_BIEN)
            return 1;

        printf("\n##### %s #####\n", lotes[i]);
        simular("posteos.bin", lotes[i], 0, VARIANTE_SIN_CACHE);
        for (j = 0; j < 7; j++)
        {
            simular("posteos.bin", lotes[i], tams[j], VARIANTE_P1);
            simular("posteos.bin", lotes[i], tams[j], VARIANTE_P2);
        }
    }
    return 0;
}
