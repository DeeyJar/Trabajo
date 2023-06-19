#ifndef GENERICO_H_INCLUDED
#define GENERICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(void *vec, size_t nmemb, size_t tamanio, int (*cmp)(void *, void *));

void show(
    void *vec,
    int cantE,
    void (*sh)(void*,int)
);

void intercambia(
    void*a,
    void*b,
    size_t tamanio
);

#endif // GENERICO_H_INCLUDED
