#include "fecha.h"

int validarDia(int dia)
{
    if(dia >= 1 && dia <=31)
        return 1;

    return 0;
}

int validarMes(int mes)
{
    if(mes >= 1 && mes <=12)
        return 1;

    return 0;
}

int validarAnio(int anio)
{
    if(anio > 0)
        return 1;

    return 0;
}
