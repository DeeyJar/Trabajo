#include "main.h"
/*
1)Validar carrera de tamanio 4 y que este en el listado que esta en el word y normalizar
2)Normalizar ApeyNombre
3)Dar de baja bug
*/


int main()
{
    char menu;
    int dia,mes,anio,cantElemento;
    t_Indice *indice;
    cantElemento = generarArchivo(ARCH_ALUMNO);

    if(cantElemento == -1)
    {
        printf("Finalizando programa\n");
        return 0;
    }

    indice = generarIndice(ARCH_ALUMNO,cantElemento,compara_alumnos);

    do
    {
        printf("Ingrese el dia del proceso : ");
        scanf("%d",&dia);
    }
    while(!validarDia(dia));

    do
    {
        printf("\nIngrese el mes del proceso : ");
        scanf("%d",&mes);
    }
    while(!validarMes(mes));

    do
    {
        printf("\nIngrese el anio del proceso : ");
        scanf("%d",&anio);
    }
    while(!validarAnio(anio));

    do
    {
        printf("==================================\n");
        printf("\nFecha del proceso: %d/%d/%d\n", dia,mes,anio);
        printf("Alta - A\n");
        printf("Baja - B\n");
        printf("Buscar - S\n");
        printf("Listar los dados de baja- L\n");
        printf("Listar en orden- O\n");
        printf("Salir - Q\n\n");
        printf("==================================\n");

        printf("Ingrese un caracter: ");
        scanf("%c",&menu);
        fflush(stdin);

        switch(ES_MINISCULA(menu))
        {
        case'A':
                printf("Dar de alta alumno\n");
            cantElemento = altaAlumno(indice,cantElemento);
            indice = generarIndice(ARCH_ALUMNO,cantElemento,compara_alumnos);
            system ("pause");
            break;
        case'B':
                printf("Dar de baja alumno\n");
            bajaDeAlumno(ARCH_ALUMNO,indice,cantElemento,dia,mes,anio);
            system ("pause");
            break;
        case'S':
            printf("Buscar alumno\n");
            buscarAlumno(ARCH_ALUMNO,indice,cantElemento);
            system ("pause");
            break;
        case'L':
            printf("Listar alumno dados baja\n");
            listarDadosDeBaja(ARCH_ALUMNO);
            system ("pause");
            break;
        case'O':
            printf("Listar alumno en orden\n");
            listarEnOrden(ARCH_ALUMNO,indice,cantElemento);
            system ("pause");
            break;
        }
        system("cls");
    }
    while(ES_MINISCULA(menu) != 'Q');
}
