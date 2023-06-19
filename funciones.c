#include "funciones.h"

int generarArchivo(const char *path)
{
    t_Alumno tAlumnos[] =
    {
        {34567890, "Pedro Rodriguez", {5, 2, 2002}, 'M', {1, 1, 2019},{0, 0, 0}, "ADM", 5, 'A'},
        {12345678, "Juan Perez", {15, 5, 2000}, 'M', {1, 1, 2021},{0, 0, 0}, "IT", 6, 'A'},
        {23456789, "Maria Gomez", {20, 10, 2001}, 'F', {1, 1, 2020},{0, 0, 0}, "ECO", 8, 'A'},
    };
    int cantElemento;
    FILE *pf;

    pf= fopen(path,"wb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return -1;
    }

    fwrite(&tAlumnos,sizeof(tAlumnos),1,pf);

    fclose(pf);

    cantElemento = sizeof(tAlumnos)/sizeof(t_Alumno);
    return cantElemento;
}

t_Indice *generarIndice(const char *path,int cantElem,int(*cmp)(void*,void*))
{
    FILE *pf;
    t_Alumno alumno;

    t_Indice *indice;
    int i = 0;

    pf = fopen(path, "rb");

    if (!pf)
    {
        printf("Error de lectura de Archivo de Alumnos\n");
        system("PAUSE");
        return 0;
    }

    indice = (t_Indice *)malloc(sizeof(t_Indice) * cantElem);

    if (!indice)
    {
        printf("Error de reserva de memoria\n");
        system("PAUSE");
        exit (1);
    }

    fread(&alumno, sizeof(t_Alumno), 1, pf);
    while(!feof(pf))
    {
        indice[i].DNI = alumno.DNI;
        indice[i].pos = i;
        i++;
        fread(&alumno, sizeof(t_Alumno), 1, pf);
    }

    bubble_sort(indice, cantElem, sizeof(t_Indice), cmp);

    fclose(pf);

    return indice;
}

int compara_alumnos(void*a,void*b)
{
    t_Alumno *alu1=(t_Alumno*)a,
              *alu2=(t_Alumno*)b;

    return alu1->DNI - alu2->DNI;
}

int altaAlumno(t_Indice *indice, int cantElem)
{
    int DiaNac,
        MesNac,
        AnioNac,
        DiaIng,
        MesIng,
        AnioIng,
        CantMaterias,
        i;
    long DNI;
    char ApyNom[50],
         Sexo,
         Carrera[4];

    t_Alumno alumno;

    FILE *pf;

    pf = fopen("alumno.dat","ab");

    if(!pf)
    {
        printf("No se pudo abrir el archivo \n");
        return 0;
    }

    printf("Ingrese DNI del alumno: ");
    scanf("%ld",&DNI);
    fflush(stdin);

    printf("\nIngrese apellido y nombre del alumno: ");
    gets(ApyNom);
    fflush(stdin);

    printf("\nIngrese sexo del alumno: ");
    scanf("%c",&Sexo);
    fflush(stdin);

    printf("\nIngrese carrera del alumno: ");
    gets(Carrera);
    fflush(stdin);

    printf("\nIngrese dia de nacimiento del alumno: ");
    scanf("%d",&DiaNac);

    printf("\nIngrese mes de nacimiento del alumno: ");
    scanf("%d",&MesNac);

    printf("\nIngrese anio de nacimiento del alumno: ");
    scanf("%d",&AnioNac);

    printf("\nIngrese dia de ingreso del alumno: ");
    scanf("%d",&DiaIng);

    printf("\nIngrese mes de ingreso del alumno: ");
    scanf("%d",&MesIng);

    printf("\nIngrese anio de ingreso del alumno: ");
    scanf("%d",&AnioIng);

    printf("\nIngrese cantidad materias aprobadas del alumno: ");
    scanf("%d",&CantMaterias);

    for(i = 0 ; i < cantElem ; i++)
    {
        if(indice[i].DNI == DNI)
        {
            printf("\nDni existente en el archivo.");
            return 0;
        }
    }

    if(10000000 < DNI && DNI < 99999999)
    {
        if(validarDia(DiaNac) && validarMes(MesNac) && validarAnio(AnioNac))
        {
            if(validarDia(DiaIng) && validarMes(MesIng) && validarAnio(AnioIng))
            {
                if(ES_MINISCULA(Sexo)== 'F' || ES_MINISCULA(Sexo)== 'M')
                    if(CantMaterias >= 0)
                    {
                        alumno.DNI= DNI;
                        strcpy(alumno.ApyNom,ApyNom);
                        alumno.Sexo = ES_MINISCULA(Sexo);
                        strcpy(alumno.Carrera,Carrera);
                        alumno.FNacimiento.Dia = DiaNac;
                        alumno.FNacimiento.Mes = MesNac;
                        alumno.FNacimiento.Anio = AnioNac;
                        alumno.FIngreso.Dia = DiaIng;
                        alumno.FIngreso.Mes = MesIng;
                        alumno.FIngreso.Anio = AnioIng;
                        alumno.CantMaterias = CantMaterias;
                        alumno.Estado = 'A';

                        fwrite(&alumno,sizeof(t_Alumno),1,pf);

                        printf("\nSe dio de alta exitosamente.\n");
                    }
            }
            else
            {
                printf("\nFecha de ingreso invalidas.");
                return 0;
            }
        }
        else
        {
            printf("\nFecha de nacimiento invalidas.");
            return 0;
        }
    }
    else
    {
        printf("\nDni erroneo.");
        return 0;
    }

    fclose(pf);

    return cantElem + 1;
}

void buscarAlumno(const char *path,t_Indice *indice, int cantElem)
{
    int i;
    long DNI;
    FILE *pf;
    t_Alumno alumno;

    pf=fopen(path,"rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo \n");
        return;
    }

    printf("Ingrese el dni que esta buscando: ");
    scanf("%ld",&DNI);
    fflush(stdin);

    for(i=0; i< cantElem ; i++)
    {
        if(indice[i].DNI == DNI)
        {
            fseek(pf, indice[i].pos * sizeof(t_Alumno), SEEK_SET);
            fread(&alumno, sizeof(t_Alumno), 1, pf);
            if(alumno.Estado!= 'B')
            {
                printf("\nDNI ENCONTRADO\n");
                printf("%08ld %-50s %c %-4s %02d/%02d/%d %02d/%02d/%d %d %c \n",
                       alumno.DNI,
                       alumno.ApyNom,
                       alumno.Sexo,
                       alumno.Carrera,
                       alumno.FNacimiento.Dia,
                       alumno.FNacimiento.Mes,
                       alumno.FNacimiento.Anio,
                       alumno.FIngreso.Dia,
                       alumno.FIngreso.Mes,
                       alumno.FIngreso.Anio,
                       alumno.CantMaterias,
                       alumno.Estado
                      );
            }
        }
    }

    fclose(pf);
}

void bajaDeAlumno(const char *path,t_Indice *indice, int cantElem,int dia,int mes,int anio)
{
    int i;
    long DNI;
    FILE *pf;
    t_Alumno alumno;

    pf=fopen(path,"r+b");

    if(!pf)
    {
        printf("No se pudo abrir el archivo \n");
        return;
    }

    printf("Ingrese el dni del alumno: ");
    scanf("%ld",&DNI);
    fflush(stdin);

    for(i=0; i< cantElem ; i++)
    {
        if(indice[i].DNI == DNI)
        {
            printf("\nAlumno dado de baja\n");
            fseek(pf, indice[i].pos * sizeof(t_Alumno), SEEK_SET);
            fread(&alumno, sizeof(t_Alumno), 1, pf);
            alumno.Estado = 'B';
            alumno.FBaja.Dia = dia;
            alumno.FBaja.Mes = mes;
            alumno.FBaja.Anio = anio;
            fseek(pf, indice[i].pos * sizeof(t_Alumno), SEEK_SET);
            fwrite(&alumno, sizeof(t_Alumno), 1, pf);
            fseek(pf,0,SEEK_END);
        }
    }

    fclose(pf);
}

void listarDadosDeBaja(const char *path)
{
    FILE *pf;
    t_Alumno alumno;

    pf=fopen(path,"rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo \n");
        return;
    }
    printf("\nDNI ApellidoyNombre Sexo Carrera FechaNacimiento FechaIngreso FechaBaja CantMaterias Estado\n");

    while(!feof(pf))
    {
        fread(&alumno,sizeof(t_Alumno),1,pf);
        if(alumno.Estado== 'B')
            printf("%08ld %-50s %c %-4s %02d/%02d/%d %02d/%02d/%d %02d/%02d/%d %d %c \n",
                   alumno.DNI,
                   alumno.ApyNom,
                   alumno.Sexo,
                   alumno.Carrera,
                   alumno.FNacimiento.Dia,
                   alumno.FNacimiento.Mes,
                   alumno.FNacimiento.Anio,
                   alumno.FIngreso.Dia,
                   alumno.FIngreso.Mes,
                   alumno.FIngreso.Anio,
                   alumno.FBaja.Dia,
                   alumno.FBaja.Mes,
                   alumno.FBaja.Anio,
                   alumno.CantMaterias,
                   alumno.Estado
                  );
    }

    fclose(pf);
}

void listarEnOrden(const char *path,t_Indice *indice, int cantElem)
{
    int i;
    FILE *pf;
    t_Alumno alumno;

    pf=fopen(path,"rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo \n");
        return;
    }
    printf("\nDNI ApellidoyNombre Sexo Carrera Dia Mes Anio Dia Mes Anio CantMaterias Estado\n");
    for(i=0; i< cantElem ; i++)
    {
        fseek(pf, indice[i].pos * sizeof(t_Alumno), SEEK_SET);
        fread(&alumno, sizeof(t_Alumno), 1, pf);
        if(alumno.Estado!= 'B')
            printf("%08ld %-50s %c %-4s %02d/%02d/%d %02d/%02d/%d %d %c \n",
                   alumno.DNI,
                   alumno.ApyNom,
                   alumno.Sexo,
                   alumno.Carrera,
                   alumno.FNacimiento.Dia,
                   alumno.FNacimiento.Mes,
                   alumno.FNacimiento.Anio,
                   alumno.FIngreso.Dia,
                   alumno.FIngreso.Mes,
                   alumno.FIngreso.Anio,
                   alumno.CantMaterias,
                   alumno.Estado
                  );
    }

    fclose(pf);
}

void mostrarArchivo()
{
    t_Alumno alumno;
    FILE *pf;

    pf = fopen("alumno.dat","rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo \n");
        return;
    }

    fread(&alumno,sizeof(t_Alumno),1,pf);

    printf("DNI ApellidoyNombre Sexo Carrera Dia Mes Anio Dia Mes Anio CantMaterias Estado\n");

    while(!feof(pf))
    {
        printf("%ld %s %c %s %d %d %d %d %d %d %d %c \n",
               alumno.DNI,
               alumno.ApyNom,
               alumno.Sexo,
               alumno.Carrera,
               alumno.FNacimiento.Dia,
               alumno.FNacimiento.Mes,
               alumno.FNacimiento.Anio,
               alumno.FIngreso.Dia,
               alumno.FIngreso.Mes,
               alumno.FIngreso.Anio,
               alumno.CantMaterias,
               alumno.Estado
              );
        fread(&alumno,sizeof(t_Alumno),1,pf);
    }
}
