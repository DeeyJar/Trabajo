#include "generico.h"

void bubble_sort(void *vec, size_t nmemb, size_t tamanio, int (*cmp)(void *, void *))
{
    int i, j;

    for(i = 0; i < nmemb; i++)
        for(j = 0; j < nmemb - 1; j++)
            if(cmp(vec + j * tamanio,  vec + (j + 1) * tamanio)>0)
                intercambia(vec + j * tamanio,  vec + (j + 1) * tamanio, tamanio);
}

void show(void *vec,int cantE,void (*sh)(void*, int))
{
    sh(vec,cantE);
}

void intercambia(void*a,void*b,size_t tamanio)
{
    char *aux = malloc(tamanio);

    memcpy(aux,a,tamanio);
    memcpy(a,b,tamanio);
    memcpy(b,aux,tamanio);
    free(aux);
}
