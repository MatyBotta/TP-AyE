#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef enum
{
    TODO_BIEN,
    SIN_MEM,
    DUPLICADO,
    LISTA_VACIA

} cod_return;

typedef int (*comparar)(const void* a, const void* b);

#endif // COMUN_H_INCLUDED
