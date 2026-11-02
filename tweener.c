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

int generarUsuarios(const char *nombre, tTipoLote tipo, unsigned int semilla)
{
    FILE *pf = fopen(nombre, "wb");
    tUsuario u;
    int i, j;
    int cantUsuarios;

    if (!pf)
        return ERR_ARCHIVO;

    srand(semilla);

    cantUsuarios = MIN_REG + rand();

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

/*
int procesarUsuarioCache (const char * posteos, const char * usuarios, int * cantUsuarios)
{
    tPosteo post;
    tUsuario usuario;
    tLRU cache;

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

*/
