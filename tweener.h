#ifndef TWEENER_H_INCLUDED
#define TWEENER_H_INCLUDED

#define MAX_CAR 140
#define CANT_POSTEOS 50000
#define MIN_REG 200
#define TAM_USUARIO 15
#define MAX_FEED 20
#define POOL_CONCENTRADO 100

#define TAM_CACHE 10

#include "comun.h"
#include "cache.h"
#include "cache2.h"

typedef enum
{
    LOTE_CONCENTRADO, LOTE_DISPERSO, LOTE_ORDENADO
} tTipoLote;

typedef enum { VARIANTE_SIN_CACHE, VARIANTE_P1, VARIANTE_P2 } tVariante;

typedef struct
{
    int id;
    char texto[MAX_CAR + 1];
} tPosteo;

typedef struct
{
    char usuario[TAM_USUARIO];
    int feed[MAX_FEED];
} tUsuario;

int generarPosteos (const char *nombre);
int generarUsuarios(const char *nombre, tTipoLote tipo, unsigned int semilla);
int procesarUsuario (const char * posteos, const char * usuarios, int * cantUsuarios);
int procesarUsuarioCache (const char * posteos, const char * usuarios, int tamCache,
                          int * cantUsuarios, int * hits, int * misses, int * lecturas);
int procesarUsuarioCache2 (const char * posteos, const char * usuarios, int tamCache,
                           int * cantUsuarios, int * hits, int * misses, int * lecturas);

int compararPosteo (const void * s1, const void * s2);

#endif // TWEENER_H_INCLUDED
