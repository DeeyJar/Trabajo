#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ES_MINISCULA(x) ((x)>= 'a' && (x)<='z' ? (x)-32 : x)
#include "generico.h"
#include "fecha.h"

typedef struct
{
    int Dia,
        Mes,
        Anio;
} t_Fecha;

typedef struct
{
    long DNI;
    char ApyNom[50];
    t_Fecha FNacimiento;
    char Sexo;
    t_Fecha FIngreso;
    t_Fecha FBaja;
    char Carrera[4];
    int CantMaterias;
    char Estado;
}t_Alumno;

typedef struct
{
    long DNI;
    int pos;
} t_Indice;

int generarArchivo(const char *path);
int compara_alumnos(void*a,void*b);

t_Indice *generarIndice(const char *path,int cantElem,int(*cmp)(void*,void*));
void mostrarArchivo();


int altaAlumno(t_Indice *indice, int cantElem);
void buscarAlumno(const char *path,t_Indice *indice, int cantElem);
void bajaDeAlumno(const char *path,t_Indice *indice, int cantElem,int dia,int mes,int anio);
void listarDadosDeBaja(const char *path);
void listarEnOrden(const char *path,t_Indice *indice, int cantElem);

#endif // FUNCIONES_H_INCLUDED
