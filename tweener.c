#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tweener.h"

int generarPosteos(const char *nombre)
{
    FILE *pf = fopen(nombre, "wb");
    tPosteo p;
    int i, j, largo;

    if(!pf)
        return ERR_ARCHIVO;

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
    return TODO_BIEN;
}

int generarUsuarios(const char *nombre, tTipoLote tipo, unsigned int semilla, int cantUsuarios)
{
    FILE *pf;
    tUsuario u;
    int i, j;
    int idActual = 0, maxPaso = 1, repetir = 0;

    if (cantUsuarios < MIN_REG)
        return ERR_ARG;

    if (tipo == LOTE_ORDENADO)
    {
        /* todos los ids del archivo forman una unica secuencia creciente
           dentro de [0, CANT_POSTEOS). Si hay mas accesos que posteos
           los ids se repiten (no decrecientes) */
        if (cantUsuarios * MAX_FEED <= CANT_POSTEOS)
            maxPaso = (CANT_POSTEOS - 1) / (cantUsuarios * MAX_FEED - 1);
        else
            repetir = 1;
    }

    pf = fopen(nombre, "wb");
    if (!pf)
        return ERR_ARCHIVO;

    srand(semilla);

    for (i = 0; i < cantUsuarios; i++)
    {
        char buf[32];
        memset(&u, 0, sizeof(u));
        snprintf(buf, sizeof(buf), "user_%03d", i);
        strncpy(u.usuario, buf, TAM_USUARIO - 1);
        u.usuario[TAM_USUARIO - 1] = '\0';

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
                for (j = 0; j < MAX_FEED; j++)
                {
                    if (repetir)
                        u.feed[j] = (int)((double)(i * MAX_FEED + j) * (CANT_POSTEOS - 1)
                                          / (cantUsuarios * MAX_FEED - 1));
                    else
                    {
                        u.feed[j] = idActual;
                        idActual += 1 + rand() % maxPaso;
                    }
                }
                break;
        }

        fwrite(&u, sizeof(u), 1, pf);
    }

    fclose(pf);
    return TODO_BIEN;
}

int procesarUsuario (const char * posteos, const char * usuarios, int * cantUsuarios)
{
    tPosteo post;
    tUsuario usuario;

    FILE * pf_post;
    FILE * pf_usuarios = fopen(usuarios, "rb");
    if(!pf_usuarios)
        return ERR_ARCHIVO;


    pf_post = fopen(posteos, "rb");
    if(!pf_post)
    {
        fclose(pf_usuarios);
        return ERR_ARCHIVO;
    }

    *cantUsuarios = 0;

    while(fread(&usuario, sizeof(tUsuario), 1, pf_usuarios))
    {
        for(int i = 0; i < MAX_FEED; i++)
        {
            fseek(pf_post, usuario.feed[i] * sizeof(tPosteo), SEEK_SET);
            fread(&post, sizeof(tPosteo), 1, pf_post);
        }

        (*cantUsuarios)++;
    }

    fclose(pf_post);
    fclose(pf_usuarios);

    return TODO_BIEN;
}

int procesarUsuarioCache (const char * posteos, const char * usuarios, int tamCache,
                          int * cantUsuarios, int * hits, int * misses)
{
    tPosteo post;
    tUsuario usuario;
    tLRU cache;

    void * info = NULL;
    FILE * pf_post, * pf_usuarios;

    pf_usuarios = fopen(usuarios, "rb");
    if(!pf_usuarios)
        return ERR_ARCHIVO;

    pf_post = fopen(posteos, "rb");
    if(!pf_post)
    {
        fclose(pf_usuarios);
        return ERR_ARCHIVO;
    }

    crear_lrucache(&cache, tamCache, compararPosteo);

    *cantUsuarios = 0;
    *hits = 0;
    *misses = 0;

    while(fread(&usuario, sizeof(tUsuario), 1, pf_usuarios))
    {
        for(int i = 0; i < MAX_FEED; i++)
        {
            if((info = obtener_lrucache(&cache, &(usuario.feed[i]))))
            {
                (*hits)++;
            }
            else
            {
                fseek(pf_post, usuario.feed[i] * sizeof(tPosteo), SEEK_SET);
                fread(&post, sizeof(tPosteo), 1, pf_post);
                agregar_lrucache(&cache, &post, sizeof(tPosteo));

                (*misses)++;
            }
        }

        (*cantUsuarios)++;
    }

    fclose(pf_post);
    fclose(pf_usuarios);
    vaciar_lrucache(&cache);

    return TODO_BIEN;
}

int procesarUsuarioCache2 (const char * posteos, const char * usuarios, int tamCache,
                           int * cantUsuarios, int * hits, int * misses, size_t * altura)
{
    tPosteo post;
    tUsuario usuario;
    tLRU2 cache;

    void * info = NULL;
    FILE * pf_post, * pf_usuarios;

    pf_usuarios = fopen(usuarios, "rb");
    if(!pf_usuarios)
        return ERR_ARCHIVO;

    pf_post = fopen(posteos, "rb");
    if(!pf_post)
    {
        fclose(pf_usuarios);
        return ERR_ARCHIVO;
    }

    crear_lrucache2(&cache, tamCache, compararPosteo);

    *cantUsuarios = 0;
    *hits = 0;
    *misses = 0;

    while(fread(&usuario, sizeof(tUsuario), 1, pf_usuarios))
    {
        for(int i = 0; i < MAX_FEED; i++)
        {
            if((info = obtener_lrucache2(&cache, &(usuario.feed[i]))))
            {
                (*hits)++;
            }
            else
            {
                fseek(pf_post, usuario.feed[i] * sizeof(tPosteo), SEEK_SET);
                fread(&post, sizeof(tPosteo), 1, pf_post);
                agregar_lrucache2(&cache, &post, sizeof(tPosteo));

                (*misses)++;
            }
        }

        (*cantUsuarios)++;
    }

    fclose(pf_post);
    fclose(pf_usuarios);
    *altura = altura_lrucache2(&cache);
    vaciar_lrucache2(&cache);

    return TODO_BIEN;
}

int compararPosteo (const void * s1, const void * s2)
{
    tPosteo * post1 = (tPosteo*)s1;
    tPosteo * post2 = (tPosteo*)s2;

    return post1->id - post2->id;
}

static double ahora_seg(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int simular(const char *posteos, const char *usuarios, int tamCache, tVariante variante)
{
    int cantUsuarios = 0;
    int hits = 0, misses = 0;
    size_t altura = 0;
    int rc = 0;
    double t0, t1, seg;

    t0 = ahora_seg();

    switch (variante)
    {
        case VARIANTE_SIN_CACHE:
            rc = procesarUsuario(posteos, usuarios, &cantUsuarios);
            break;
        case VARIANTE_P1:
            rc = procesarUsuarioCache(posteos, usuarios, tamCache,
                                      &cantUsuarios, &hits, &misses);
            break;
        case VARIANTE_P2:
            rc = procesarUsuarioCache2(posteos, usuarios, tamCache,
                                       &cantUsuarios, &hits, &misses, &altura);
            break;
    }

    t1 = ahora_seg();
    seg = t1 - t0;

    if (rc != TODO_BIEN) {
        fprintf(stderr, "Error en simulacion (codigo %d)\n", rc);
        return rc;
    }

    long totalAccesos = (long)cantUsuarios * MAX_FEED;

    /* ---- salida ---- */
    const char *nombreVar =
        variante == VARIANTE_SIN_CACHE ? "SIN CACHE" :
        variante == VARIANTE_P1        ? "LRU P1"    : "LRU P2";

    printf("========================================\n");
    printf("Variante            : %s\n", nombreVar);
    printf("Cache size          : %d\n", tamCache);
    printf("Usuarios            : %d\n", cantUsuarios);
    printf("Accesos totales     : %ld\n", totalAccesos);
    printf("Tiempo total        : %.6f s\n", seg);
    printf("Prom. por posteo    : %.9f s\n", seg / totalAccesos);
    printf("Prom. por usuario   : %.9f s\n", seg / cantUsuarios);

    if (variante != VARIANTE_SIN_CACHE)
    {
        printf("Hits                : %d\n", hits);
        printf("Misses              : %d\n", misses);
        printf("Hit rate            : %.2f %%\n",
               100.0 * hits / totalAccesos);
        if (variante == VARIANTE_P2)
            printf("Altura del indice   : %lu\n", (unsigned long)altura);

        if (hits + misses != totalAccesos)
            fprintf(stderr, "WARN: hits+misses (%d) != accesos (%ld)\n",
                    hits + misses, totalAccesos);
    }

    return TODO_BIEN;
}
