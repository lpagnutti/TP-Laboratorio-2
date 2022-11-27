#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANTGRUPOS 8
#include <time.h>
#include<windows.h>

typedef struct Equipo
{
    char nomEquipo[40];
    int mp; ///partidos jugados
    int gf;   ///goles a favor
    int ga;  ////goles en contra
    int win;  ///partidos ganados
    int loss;  ////partidos perdidos
    int pts;  ////puntos totales
} Equipo;

typedef struct nodoEquipo
{
    Equipo equipo;
    struct nodoEquipo* siguiente;
} nodoEquipo;

typedef struct Grupo
{
    char letra; ///'A','B'....
    struct nodoGrupoEquipo* equipos; ///siempre va a haber 4
} Grupo;

typedef struct nodoGrupoEquipo
{
    Equipo* equipo;
    struct nodoGrupoEquipo* siguiente;
} nodoGrupoEquipo;

typedef struct Partido
{
    char fecha[6]; ///eligen ustedes el criterio
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEq1;
    int golesEq2;
    int penales1; ///en la fase de grupos no hay penales
    int penales2;
} Partido;

typedef struct nodoPartido
{
   Partido partido;
   struct nodoPartido* siguiente;
}nodoPartido;


typedef struct GrupoPartido
{
   char letra;
   nodoPartido* partidos;
}GrupoPartido;

typedef struct archivoProbabilidad
{
    char nomEquipo[40];
    int posibilidades;
}archivoProbabilidad;


typedef struct fase
{
int idFase;
nodoPartido* partidos;
}fase;

nodoEquipo* crearNodoEquipo(Equipo aux)
{
    nodoEquipo* nuevo=(nodoEquipo*)malloc(sizeof(nodoEquipo));
    strcpy(nuevo->equipo.nomEquipo,aux.nomEquipo);
    nuevo->equipo.ga=aux.ga;
    nuevo->equipo.gf=aux.gf;
    nuevo->equipo.loss=aux.loss;
    nuevo->equipo.mp=aux.mp;
    nuevo->equipo.pts=aux.pts;
    nuevo->equipo.win=aux.win;
    nuevo->siguiente=NULL;
    return nuevo;
}

void insertarAlFinal(nodoEquipo** listaEquipos,Equipo aux)
{
    nodoEquipo* nuevo= crearNodoEquipo(aux);
    nodoEquipo* seg;
    seg=*listaEquipos;
    if(*listaEquipos==NULL)
    {
        *listaEquipos=nuevo;
    }
    else
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo;
    }
}

void generarArregloGrupos(Grupo grupos[],nodoEquipo* listaEquipos)
{
    int letraGrupo=65;///uso el codigo ascii
    nodoEquipo* seg=listaEquipos;
    for(int i=0; i<CANTGRUPOS; i++)
    {
        grupos[i].letra=letraGrupo;
        nodoGrupoEquipo* aux=NULL;
        for(int j=0; j<4; j++)
        {
            nodoGrupoEquipo* nuevo=(nodoGrupoEquipo*)malloc(sizeof(nodoGrupoEquipo));
            nuevo->equipo=&((seg)->equipo);
            nuevo->siguiente=aux;
            aux=nuevo;
            seg=seg->siguiente;
        }
        letraGrupo++;
        grupos[i].equipos=aux;
    }
}


int buscarPosibilidad(char equipo[])
{
    FILE* fp=fopen("probabilidad.bin","rb");
    archivoProbabilidad aux;

    if(fp!=NULL)
    {
        while(fread(&aux,sizeof(archivoProbabilidad),1,fp)>0)
        {
            if(strcmpi(aux.nomEquipo,equipo)==0)
            {
                fclose(fp);

            }
        }
    }
    return aux.posibilidades;
}

void generarFechas(char fechas[48][6])
{
    strcpy(fechas[0],"21/11");
    strcpy(fechas[1],"25/11");
    strcpy(fechas[2],"29/11");
    strcpy(fechas[3],"29/11");
    strcpy(fechas[4],"25/11");
    strcpy(fechas[5],"20/11");
    strcpy(fechas[6],"21/11");
    strcpy(fechas[7],"25/11");
    strcpy(fechas[8],"29/11");
    strcpy(fechas[9],"29/11");
    strcpy(fechas[10],"25/11");
    strcpy(fechas[11],"21/11");
    strcpy(fechas[12],"22/11");
    strcpy(fechas[13],"26/11");
    strcpy(fechas[14],"30/11");
    strcpy(fechas[15],"30/11");
    strcpy(fechas[16],"26/11");
    strcpy(fechas[17],"22/11");
    strcpy(fechas[18],"22/11");
    strcpy(fechas[19],"26/11");
    strcpy(fechas[20],"30/11");
    strcpy(fechas[21],"30/11");
    strcpy(fechas[22],"26/11");
    strcpy(fechas[23],"22/11");
    strcpy(fechas[24],"23/11");
    strcpy(fechas[25],"27/11");
    strcpy(fechas[26],"01/12");
    strcpy(fechas[27],"01/12");
    strcpy(fechas[28],"27/11");
    strcpy(fechas[29],"23/11");
    strcpy(fechas[30],"23/11");
    strcpy(fechas[31],"27/11");
    strcpy(fechas[32],"01/12");
    strcpy(fechas[33],"01/12");
    strcpy(fechas[34],"27/11");
    strcpy(fechas[35],"23/11");
    strcpy(fechas[36],"24/11");
    strcpy(fechas[37],"28/11");
    strcpy(fechas[38],"02/12");
    strcpy(fechas[39],"02/12");
    strcpy(fechas[40],"28/11");
    strcpy(fechas[41],"24/11");
    strcpy(fechas[42],"24/11");
    strcpy(fechas[43],"28/11");
    strcpy(fechas[44],"02/12");
    strcpy(fechas[45],"02/12");
    strcpy(fechas[46],"28/11");
    strcpy(fechas[47],"24/11");
}

void generarPartidoConPenales (nodoPartido** nuevo)
{
    int posiEq1=buscarPosibilidad((*nuevo)->partido.equipo1->nomEquipo);
    int posiEq2=buscarPosibilidad((*nuevo)->partido.equipo2->nomEquipo);
    (*nuevo)->partido.golesEq1=  rand() % posiEq1;
    Sleep(5);
    (*nuevo)->partido.golesEq2= rand() % posiEq2;
    if(posiEq1>=3 && (*nuevo)->partido.golesEq1<2)
    {
        (*nuevo)->partido.golesEq1++;
    }
    if(posiEq2>=3 && (*nuevo)->partido.golesEq2<2)
    {
        (*nuevo)->partido.golesEq2++;
    }
    if((*nuevo)->partido.golesEq1 == (*nuevo)->partido.golesEq2)/// empataron
    {
        do
        {
            (*nuevo)->partido.penales1= rand() % 6;
            Sleep(5);
            (*nuevo)->partido.penales2= rand() % 6;

        }
        while((*nuevo)->partido.penales1==(*nuevo)->partido.penales2);
    }
    else
    {
        (*nuevo)->partido.penales1= 0;
        (*nuevo)->partido.penales2= 0;
    }
    (*nuevo)->partido.equipo1->gf+=(*nuevo)->partido.golesEq1;///sumo goles a favor eq1
    (*nuevo)->partido.equipo1->ga+=(*nuevo)->partido.golesEq2;/// sumo encontra eq1
    (*nuevo)->partido.equipo2->gf+=(*nuevo)->partido.golesEq2;///sumo goles a favor eq2
    (*nuevo)->partido.equipo2->ga+=(*nuevo)->partido.golesEq1;/// sumo encontra eq2
    (*nuevo)->partido.equipo1->mp++;
    (*nuevo)->partido.equipo2->mp++;
    if((*nuevo)->partido.penales1==0 && (*nuevo)->partido.penales2==0)/// no hubo penales
    {
        if((*nuevo)->partido.golesEq1 > (*nuevo)->partido.golesEq2) ///gano el equipo 1
        {
            (*nuevo)->partido.equipo1->win++;
            (*nuevo)->partido.equipo1->pts+=3;
            (*nuevo)->partido.equipo2->loss++;
        }
        else /// gano el 2
        {
            (*nuevo)->partido.equipo2->win++;
            (*nuevo)->partido.equipo2->pts+=3;
            (*nuevo)->partido.equipo1->loss++;
        }
    }
    else
    {
        if((*nuevo)->partido.penales1 > (*nuevo)->partido.penales2)  ///gano el equipo 1
        {
            (*nuevo)->partido.equipo1->win++;
            (*nuevo)->partido.equipo1->pts+=3;
            (*nuevo)->partido.equipo2->loss++;
        }
        else
        {
            (*nuevo)->partido.equipo2->win++;
            (*nuevo)->partido.equipo2->pts+=3;
            (*nuevo)->partido.equipo1->loss++;
        }
    }
}

void generarPartidoSinPenales(nodoPartido** nuevo)
{
    int posiEq1=buscarPosibilidad((*nuevo)->partido.equipo1->nomEquipo);
    int posiEq2=buscarPosibilidad((*nuevo)->partido.equipo2->nomEquipo);
    (*nuevo)->partido.golesEq1=  rand() % posiEq1;
    Sleep(5);
    (*nuevo)->partido.golesEq2= rand() % posiEq2;
    (*nuevo)->partido.penales1=0;
    (*nuevo)->partido.penales2=0;
    if(posiEq1>=3 && (*nuevo)->partido.golesEq1<=2)
    {
        (*nuevo)->partido.golesEq1++;
    }
    if(posiEq2>=3 && (*nuevo)->partido.golesEq2<=2)
    {
        (*nuevo)->partido.golesEq2++;
    }
    (*nuevo)->partido.equipo1->gf+=(*nuevo)->partido.golesEq1;///sumo los goles a favor
    (*nuevo)->partido.equipo1->ga+=(*nuevo)->partido.golesEq2;/// sumo los goles en contra
    (*nuevo)->partido.equipo1->mp++;///sumo los partidos jugados
    (*nuevo)->partido.equipo2->gf+=(*nuevo)->partido.golesEq2;
    (*nuevo)->partido.equipo2->ga+=(*nuevo)->partido.golesEq1;
    (*nuevo)->partido.equipo2->mp++;
    if((*nuevo)->partido.golesEq1 > (*nuevo)->partido.golesEq2) ///gano el equipo 1
    {
        (*nuevo)->partido.equipo1->win++;
        (*nuevo)->partido.equipo1->pts+=3;
        (*nuevo)->partido.equipo2->loss++;
    }
    else
    {
        if((*nuevo)->partido.golesEq1 == (*nuevo)->partido.golesEq2)/// empataron
        {
            (*nuevo)->partido.equipo1->pts+=1;
            (*nuevo)->partido.equipo2->pts+=1;
        }
        else///gano el 2
        {
            (*nuevo)->partido.equipo1->loss++;
            (*nuevo)->partido.equipo2->win++;
            (*nuevo)->partido.equipo2->pts+=3;
        }
    }
}


void generarArregloPartidosFaseGrupos(GrupoPartido partidosFaseGrupos[],Grupo grupos[])
{
    int j=0;
    FILE* fp=fopen("fechas.bin","ab");
    char fechas[48][6];
    generarFechas(fechas);
    int y=0;
    for(int i=0; i<CANTGRUPOS; i++)
    {
        nodoPartido* listaPartidos=NULL;
        partidosFaseGrupos[j].letra=grupos[i].letra;
        nodoGrupoEquipo* seg=grupos[i].equipos;///seg es el 1 luego el 2 y luego el 3
        while(seg->siguiente!=NULL)
        {
            nodoGrupoEquipo* aux=seg->siguiente;///aux seria el equipo siguiente cuando este seg en el 1 aux va a tomar el 2-3-4,seg en 2 aux 3-4, seg en 3 aux en 4 asi formando toda la grilla de partidos
            while(aux!=NULL)
            {
                nodoPartido* nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
                nuevo->partido.equipo1=seg->equipo;
                nuevo->partido.equipo2=aux->equipo;
                strcpy(nuevo->partido.fecha,fechas[y]);
                y++;
                generarPartidoSinPenales(&(nuevo));
                aux=aux->siguiente;
                nuevo->siguiente=listaPartidos;
                listaPartidos=nuevo;
            }
            seg=seg->siguiente;


        }
        fclose(fp);
        partidosFaseGrupos[j].partidos=listaPartidos;
        j++;
    }
}


void cargarProbabilidad(nodoEquipo* listaEquipos)
{
    FILE* fp=fopen("probabilidad.bin","wb");
    nodoEquipo* seg=listaEquipos;
    archivoProbabilidad aux;
    if(fp!=NULL)
    {
        while(seg!=NULL)
        {
            printf("Probabilidad de %s ",seg->equipo.nomEquipo);
            scanf("%i",&(aux.posibilidades));
            strcpy(aux.nomEquipo,seg->equipo.nomEquipo);
            fwrite(&aux,sizeof(archivoProbabilidad),1,fp);
            seg=seg->siguiente;
        }
    }
    fclose(fp);
}

typedef struct
{
    int equipo1;// si es primero o segundo
    char grupo1;// el grupo al que pertence
    int equipo2;
    char grupo2;
    char fecha[6];
}octavos;

void generarArregloOctavos(octavos arreglooctavos[7])
{
    arreglooctavos[0].equipo1=1;
    arreglooctavos[0].grupo1='A';
    arreglooctavos[0].equipo2=2;
    arreglooctavos[0].grupo2='B';
    strcpy(arreglooctavos[0].fecha,"03/12");
    arreglooctavos[1].equipo1=1;
    arreglooctavos[1].grupo1='C';
    arreglooctavos[1].equipo2=2;
    arreglooctavos[1].grupo2='D';
    strcpy(arreglooctavos[1].fecha,"03/12");
    arreglooctavos[2].equipo1=1;
    arreglooctavos[2].grupo1='E';
    arreglooctavos[2].equipo2=2;
    arreglooctavos[2].grupo2='F';
    strcpy(arreglooctavos[2].fecha,"05/12");
    arreglooctavos[3].equipo1=1;
    arreglooctavos[3].grupo1='G';
    arreglooctavos[3].equipo2=2;
    arreglooctavos[3].grupo2='H';
    strcpy(arreglooctavos[3].fecha,"05/12");
    arreglooctavos[4].equipo1=1;
    arreglooctavos[4].grupo1='B';
    arreglooctavos[4].equipo2=2;
    arreglooctavos[4].grupo2='A';
    strcpy(arreglooctavos[4].fecha,"04/12");
    arreglooctavos[5].equipo1=1;
    arreglooctavos[5].grupo1='D';
    arreglooctavos[5].equipo2=2;
    arreglooctavos[5].grupo2='C';
    strcpy(arreglooctavos[5].fecha,"04/12");
    arreglooctavos[6].equipo1=1;
    arreglooctavos[6].grupo1='F';
    arreglooctavos[6].equipo2=2;
    arreglooctavos[6].grupo2='E';
    strcpy(arreglooctavos[6].fecha,"06/12");
    arreglooctavos[7].equipo1=1;
    arreglooctavos[7].grupo1='H';
    arreglooctavos[7].equipo2=2;
    arreglooctavos[7].grupo2='G';
    strcpy(arreglooctavos[7].fecha,"03/12");
}

Equipo* buscarPrimero(char letra,Grupo grupos[])
{
    int i=0;
    while(grupos[i].letra!=letra)
    {
        i++;
    }
    nodoGrupoEquipo* seg=grupos[i].equipos;
    int maxPuntaje=0;
    int maxDif=0;
    int maxGol=0;
    Equipo* retornar;
    while (seg!=NULL)
    {
        if(seg->equipo->pts > maxPuntaje)
        {
            maxPuntaje=seg->equipo->pts;
            maxDif=seg->equipo->gf - seg->equipo->ga;
            maxGol=seg->equipo->gf;
            retornar=seg->equipo;
        }
        else if(seg->equipo->pts == maxPuntaje)
        {
            if((seg->equipo->gf - seg->equipo->ga) >maxDif)
            {
                maxPuntaje=seg->equipo->pts;
                maxDif=seg->equipo->gf - seg->equipo->ga;
                maxGol=seg->equipo->gf;
                retornar=seg->equipo;
            }
            else if((seg->equipo->gf - seg->equipo->ga) ==maxDif)
            {
                if(seg->equipo->gf>maxGol)
                {
                    maxPuntaje=seg->equipo->pts;
                    maxDif=seg->equipo->gf - seg->equipo->ga;
                    maxGol=seg->equipo->gf;
                    retornar=seg->equipo;
                }
            }
        }
        seg=seg->siguiente;
    }
    return retornar;
}

Equipo* buscarSegundo(char letra,Grupo grupos[])
{
    int i=0;
    while(grupos[i].letra!=letra)
    {
        i++;
    }
    nodoGrupoEquipo* seg=grupos[i].equipos;
    Equipo* primero=buscarPrimero(letra,grupos);
    int maxPuntaje=0;
    int maxDif=0;
    int maxGol=0;
    Equipo* retornar;
    while (seg!=NULL)
    {
        if(strcmpi(primero->nomEquipo,seg->equipo->nomEquipo)==0)
            seg=seg->siguiente;
        else
        {

            if(seg->equipo->pts > maxPuntaje)
            {
                maxPuntaje=seg->equipo->pts;
                maxDif=seg->equipo->gf - seg->equipo->ga;
                maxGol=seg->equipo->gf;
                retornar=seg->equipo;
            }
            else if(seg->equipo->pts == maxPuntaje)
            {
                if((seg->equipo->gf - seg->equipo->ga) >maxDif)
                {
                    maxPuntaje=seg->equipo->pts;
                    maxDif=seg->equipo->gf - seg->equipo->ga;
                    maxGol=seg->equipo->gf;
                    retornar=seg->equipo;
                }
                else if((seg->equipo->gf - seg->equipo->ga) ==maxDif)
                {
                    if(seg->equipo->gf>maxGol)
                    {
                        maxPuntaje=seg->equipo->pts;
                        maxDif=seg->equipo->gf - seg->equipo->ga;
                        maxGol=seg->equipo->gf;
                        retornar=seg->equipo;
                    }
                }
            }
            seg=seg->siguiente;
        }
    }
    return retornar;
}

void insertarAlFinalPartido(nodoPartido** listaPartido,nodoPartido* nuevo)
{
    nodoPartido* seg;
    seg=*listaPartido;
    if(*listaPartido==NULL)
    {
        *listaPartido=nuevo;
    }
    else
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo;
    }
}


nodoPartido* crearNodoPartidoOctavos(octavos arregloOctavos[8],int i,Grupo grupos[CANTGRUPOS])
{
    nodoPartido* nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    nuevo->siguiente=NULL;
    nuevo->partido.equipo1=buscarPrimero(arregloOctavos[i].grupo1,grupos);
    nuevo->partido.equipo2=buscarSegundo(arregloOctavos[i].grupo2,grupos);
    generarPartidoConPenales(&nuevo);
    return nuevo;
}

Equipo* buscarGanadorPartido(Partido aux)
{
    Equipo* retornar;
    if(aux.penales1==0 && aux.penales2==0)///no hubo penales
    {
        if(aux.golesEq1 > aux.golesEq2)
        {
            retornar=aux.equipo1;
        }
        else
        {
            retornar=aux.equipo2;
        }
    }
    else
    {
        if(aux.penales1>aux.penales2)
        {
            retornar=aux.equipo1;
        }
        else
        {
            retornar=aux.equipo2;
        }
    }
    return retornar;
}

nodoPartido* crearNodoPartidoCuartosySemi(nodoPartido** seg)
{
    nodoPartido* nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    nuevo->siguiente=NULL;
    nuevo->partido.equipo1=buscarGanadorPartido((*seg)->partido);
    *seg=(*seg)->siguiente;
    nuevo->partido.equipo2=buscarGanadorPartido((*seg)->partido);
    *seg=(*seg)->siguiente;
    generarPartidoConPenales(&nuevo);
    return nuevo;
}

Equipo* buscarPerdedorPartido(Partido aux)
{
    Equipo* retornar;
    if(aux.penales1==0 && aux.penales2==0)///no hubo penales
    {
        if(aux.golesEq1 > aux.golesEq2)
        {
            retornar=aux.equipo2;
        }
        else
        {
            retornar=aux.equipo1;
        }
    }
    else
    {
        if(aux.penales1>aux.penales2)
        {
            retornar=aux.equipo2;
        }
        else
        {
            retornar=aux.equipo1;
        }
    }
    return retornar;
}



nodoPartido* crearNodoFinal3erPuesto(nodoPartido** seg,int i)
{
    nodoPartido* nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    nuevo->siguiente=NULL;
    if(i==3)///3er puesto
    {
        nuevo->partido.equipo1=buscarPerdedorPartido((*seg)->partido);
        *seg=(*seg)->siguiente;
        nuevo->partido.equipo2=buscarPerdedorPartido((*seg)->partido);

    }
    else///final
    {
        nuevo->partido.equipo1=buscarGanadorPartido((*seg)->partido);
        *seg=(*seg)->siguiente;
        nuevo->partido.equipo2=buscarGanadorPartido((*seg)->partido);
    }
    generarPartidoConPenales(&nuevo);
    return nuevo;
}


void generarArregloFases(fase Fases[5],Grupo grupos[CANTGRUPOS])
{
    for (int i =0; i<5; i++)
    {
        if(i==0)///octavos
        {
            octavos arregloOctavos[8];
            generarArregloOctavos(arregloOctavos);
            Fases[i].idFase=i;
            Fases[i].partidos=NULL;
            for(int j=0; j<CANTGRUPOS; j++)
            {
                nodoPartido* nuevo=crearNodoPartidoOctavos(arregloOctavos,j,grupos);
                strcpy(nuevo->partido.fecha,arregloOctavos[j].fecha);
                insertarAlFinalPartido(&(Fases[i].partidos),nuevo);
            }
        }
        else
        {
            if(i==1 || i==2)///cuartos y semis
            {
                Fases[i].idFase=i;
                Fases[i].partidos=NULL;
                nodoPartido* seg=Fases[i-1].partidos;///lo uso para buscar los ganadores de octavos
                while(seg!=NULL)
                {
                    nodoPartido* nuevo=crearNodoPartidoCuartosySemi(&seg);
                    insertarAlFinalPartido(&(Fases[i].partidos),nuevo);
                }
            }
            else
            {
                if(i==3)///3er puesto
                {
                    Fases[i].idFase=i;
                    Fases[i].partidos=NULL;
                    nodoPartido* seg=Fases[i-1].partidos;///lo uso para buscar los perdedores de semis
                    nodoPartido* nuevo=crearNodoFinal3erPuesto(&seg,i);
                    insertarAlFinalPartido(&(Fases[i].partidos),nuevo);

                }
                else
                {
                    Fases[i].idFase=i;
                    Fases[i].partidos=NULL;
                    nodoPartido* seg=Fases[i-2].partidos;///lo uso para buscar los ganadores de semis
                    nodoPartido* nuevo=crearNodoFinal3erPuesto(&seg,i);
                    insertarAlFinalPartido(&(Fases[i].partidos),nuevo);

                }
            }
        }
    }
}


void generarListaEquipos(nodoEquipo** listaEquipos)
{
    FILE* fp=fopen("equipos.bin","rb");
    Equipo aux;
    if(fp!=NULL)
    {
        while(fread(&aux,sizeof(Equipo),1,fp)>0)
        {
            insertarAlFinal(listaEquipos,aux);
        }
    }
}

void modificarPosibilidades()
{
    FILE* fp=fopen("probabilidad.bin","rb");
    archivoProbabilidad aux;
    char nombre[20];
    int i=0;
    archivoProbabilidad arreglo[65];
    if(fp!=NULL)
    {
        while(fread(&aux,sizeof(archivoProbabilidad),1,fp)>0)
        {
            arreglo[i]=aux;
            i++;
        }
    }
    fclose(fp);
    printf("Ingrese el equipo al cual desea modificar las probabilidades:\n");
    fflush(stdin);
    scanf("%s",nombre);
    for(int j=0;j<=i;j++)
    {
        if(strcmpi(arreglo[j].nomEquipo,nombre)==0)
        {
            printf("%s %i\n",arreglo[j].nomEquipo,arreglo[j].posibilidades);
            printf("Ingrese las nuevas posibilidades:\n");
            scanf("%i",&(arreglo[j].posibilidades));
        }
    }
    fp=fopen("probabilidad.bin","wb");
    if(fp!=NULL)
    {
        for(int j=0;j<=i;j++)
        {
            aux=arreglo[j];
            fwrite(&aux,sizeof(archivoProbabilidad),1,fp);
        }
    }
    fclose(fp);
}

void mostrarTodosLosGrupos(Grupo grupos[])
{
    system("cls");
    for(int i=0; i<CANTGRUPOS; i++)
    {
        printf("\t\t\tGRUPO %c\n",grupos[i].letra);
        nodoGrupoEquipo* seg1=grupos[i].equipos;
        printf("\tEquipo\t | GF | GA | MP | WIN | LOSS | PTS|\n---------------------------------------------------\n");
        while(seg1!=NULL)
        {
            printf("%16s | %2i | %2i | %2i | %2i  |  %2i  | %2i |\n",seg1->equipo->nomEquipo,seg1->equipo->gf,seg1->equipo->ga,seg1->equipo->mp,seg1->equipo->win,seg1->equipo->loss,seg1->equipo->pts);
            seg1=seg1->siguiente;
        }
        Equipo* primero=buscarPrimero(grupos[i].letra,grupos);
        Equipo* segundo=buscarSegundo(grupos[i].letra,grupos);
        printf("---------------------------------------------------\n");
        printf("1ro de grupo: %s\n",primero->nomEquipo);
        printf("2ro de grupo: %s\n",segundo->nomEquipo);
        printf("\n");
    }
    system("pause");
}

void mostrarPartidosGrupos(nodoPartido* PartidosGrupos)
{
    nodoPartido* nuevo=PartidosGrupos;
    while (nuevo!=NULL)
    {
        printf("\t%s\n",nuevo->partido.fecha);
        printf("%14s: %i\n",nuevo->partido.equipo1->nomEquipo,nuevo->partido.golesEq1);
        printf("%14s: %i\n",nuevo->partido.equipo2->nomEquipo,nuevo->partido.golesEq2);
        nuevo=nuevo->siguiente;
        printf("----------------------\n");
    }
}

void mostrarUnGrupo(Grupo grupos[],int i,nodoPartido* PartidosGrupos)
{
    system("cls");
    printf("\t\t\tGRUPO %c\n",grupos[i].letra);
    nodoGrupoEquipo* seg1=grupos[i].equipos;
    printf("\tEquipo\t | GF | GA | MP | WIN | LOSS | PTS|\n---------------------------------------------------\n");
    while(seg1!=NULL)
    {
        printf("%16s | %2i | %2i | %2i | %2i  |  %2i  | %2i |\n",seg1->equipo->nomEquipo,seg1->equipo->gf,seg1->equipo->ga,seg1->equipo->mp,seg1->equipo->win,seg1->equipo->loss,seg1->equipo->pts);
        seg1=seg1->siguiente;
    }
    printf("\n");
    char rta;
    Equipo* primero=buscarPrimero(grupos[i].letra,grupos);
    Equipo* segundo=buscarSegundo(grupos[i].letra,grupos);
    printf("---------------------------------------------------\n");
    printf("1ro de grupo: %s\n",primero->nomEquipo);
    printf("2ro de grupo: %s\n\n",segundo->nomEquipo);
    printf("Desea ver los partidos del grupo s/n");
    fflush(stdin);
    scanf("%c",&rta);
    if(rta=='s' || rta=='S')
    {
        mostrarPartidosGrupos(PartidosGrupos);
    }
    system("pause");
}
void mostrarGrupos(Grupo grupos[],GrupoPartido partidosFaseGrupos[])
{
    int rta=0;
    do
    {
        do
        {
            system("cls");
            printf("1. GRUPO A\n");
            printf("2. GRUPO B\n");
            printf("3. GRUPO C\n");
            printf("4. GRUPO D\n");
            printf("5. GRUPO E\n");
            printf("6. GRUPO F\n");
            printf("7. GRUPO G\n");
            printf("8. GRUPO H\n");
            printf("9. Todos los grupos\n");
            printf("0. Salir\n");
            scanf("%i",&rta);
        }
        while (rta<0 || rta>9);
        if (rta>0 && rta<9)
        {
            mostrarUnGrupo(grupos,rta-1,partidosFaseGrupos[rta-1].partidos);
        }
        else
        {
            if(rta==9)
            {
                mostrarTodosLosGrupos(grupos);
            }
        }

    }while(rta!=0);
}

void mostrarFases(fase Fases[],int i)
{
    nodoPartido*nuevo=Fases[i].partidos;
    Equipo* ganador;
    switch(i)
    {
    case 0:
        printf("\tOCTAVOS\n");
        break;
    case 1:
        printf("\tCUARTOS\n");
        break;
    case 2:
        printf("\tSEMIS\n");
        break;
    case 3:
        printf("\t3er PUESTO\n");
        break;
    case 4:
        printf("\tFINAL\n");
        break;
    }
    while (nuevo!=NULL)
    {
        ganador=buscarGanadorPartido(nuevo->partido);
        printf("%14s: %i(%i)\n",nuevo->partido.equipo1->nomEquipo,nuevo->partido.golesEq1,nuevo->partido.penales1);
        printf("%14s: %i(%i)\n",nuevo->partido.equipo2->nomEquipo,nuevo->partido.golesEq2,nuevo->partido.penales2);
        printf("GANADOR: %s\n",ganador->nomEquipo);
        nuevo=nuevo->siguiente;
        printf("----------------------\n");
    }
}

void  mostrarEstadisticas(nodoEquipo* listaEquipos)
{
    nodoEquipo*seg1=listaEquipos;
    printf("\tEquipo\t | GF | GA | MP | WIN | LOSS | PTS|\n---------------------------------------------------\n");
    while(seg1!=NULL)
        {
            printf("%16s | %2i | %2i | %2i | %2i  |  %2i  | %2i |\n",seg1->equipo.nomEquipo,seg1->equipo.gf,seg1->equipo.ga,seg1->equipo.mp,seg1->equipo.win,seg1->equipo.loss,seg1->equipo.pts);
            seg1=seg1->siguiente;
        }
        printf("\n");

}



void mostrarArbol(fase Fases[])
{
    nodoPartido* octa=Fases[0].partidos;
    nodoPartido* cuartos=Fases[1].partidos;
    nodoPartido* semi=Fases[2].partidos;
    nodoPartido* fin=Fases[4].partidos;

    printf("\tOctavos\t\t\tCuartos\t\t\t\tSemis\t\t  Final\t\t       Campeon\n");
    printf("%14s: %i(%i) _\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i)  |\n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);
    octa=octa->siguiente;
    printf("\t\t      |_ %14s: %i(%i) _\n",cuartos->partido.equipo1->nomEquipo,cuartos->partido.golesEq1,cuartos->partido.penales1);
    printf("\t\t      |  %14s: %i(%i)  |\n",cuartos->partido.equipo2->nomEquipo,cuartos->partido.golesEq2,cuartos->partido.penales2);
    cuartos=cuartos->siguiente;
    printf("%14s: %i(%i) _|\t\t\t       |\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i) \t\t\t       |\n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);
    octa=octa->siguiente;
    printf("\t\t\t\t\t       |_ %14s: %i(%i) _\n",semi->partido.equipo1->nomEquipo,semi->partido.golesEq1,semi->partido.penales1);
    printf("\t\t\t\t\t       |  %14s: %i(%i)  |\n",semi->partido.equipo2->nomEquipo,semi->partido.golesEq2,semi->partido.penales2);
    semi=semi->siguiente;
    printf("%14s: %i(%i) _\t\t\t       |\t\t        |\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i)  |\t\t\t       |\t\t        |\n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);
    octa=octa->siguiente;
    printf("\t\t      |_ %14s: %i(%i) _|\t\t        |\n",cuartos->partido.equipo1->nomEquipo,cuartos->partido.golesEq1,cuartos->partido.penales1);
    printf("\t\t      |  %14s: %i(%i)  \t\t\t\t|\n",cuartos->partido.equipo2->nomEquipo,cuartos->partido.golesEq2,cuartos->partido.penales2);
    cuartos=cuartos->siguiente;
    printf("%14s: %i(%i) _|\t\t\t  \t\t\t\t|\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i)  \t\t\t  \t\t\t\t|\n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);
    octa=octa->siguiente;
    printf("\t\t\t\t\t\t\t\t\t|_ %14s: %i(%i)",fin->partido.equipo1->nomEquipo,fin->partido.golesEq1,fin->partido.penales1);
    printf("   %14s\n",buscarGanadorPartido(fin->partido)->nomEquipo);
    printf("\t\t\t\t\t\t\t\t\t|  %14s: %i(%i)\n",fin->partido.equipo2->nomEquipo,fin->partido.golesEq2,fin->partido.penales2);
    printf("%14s: %i(%i) _\t\t\t\t\t\t\t|\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i)  |\t\t\t\t\t\t\t|\n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);
    octa=octa->siguiente;
    printf("\t\t      |_ %14s: %i(%i) _\t\t\t\t|\n",cuartos->partido.equipo1->nomEquipo,cuartos->partido.golesEq1,cuartos->partido.penales1);
    printf("\t\t      |  %14s: %i(%i)  |\t\t\t|\n",cuartos->partido.equipo2->nomEquipo,cuartos->partido.golesEq2,cuartos->partido.penales2);
    cuartos=cuartos->siguiente;
    printf("%14s: %i(%i) _|\t\t\t       |\t\t\t|\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i)   \t\t\t       |\t\t\t|\n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);
    octa=octa->siguiente;
    printf("\t\t\t\t\t       |_ %14s: %i(%i) _|\n",semi->partido.equipo1->nomEquipo,semi->partido.golesEq1,semi->partido.penales1);
    printf("\t\t\t\t\t       |  %14s: %i(%i)  \n",semi->partido.equipo2->nomEquipo,semi->partido.golesEq2,semi->partido.penales2);
    printf("%14s: %i(%i) _\t\t\t       |\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i)  |\t\t\t       |\n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);
    octa=octa->siguiente;
    printf("\t\t      |_ %14s: %i(%i) _|\n",cuartos->partido.equipo1->nomEquipo,cuartos->partido.golesEq1,cuartos->partido.penales1);
    printf("\t\t      |  %14s: %i(%i)   \n",cuartos->partido.equipo2->nomEquipo,cuartos->partido.golesEq2,cuartos->partido.penales2);
    cuartos=cuartos->siguiente;
    printf("%14s: %i(%i) _|\n",octa->partido.equipo1->nomEquipo,octa->partido.golesEq1,octa->partido.penales1);
    printf("%14s: %i(%i) \n",octa->partido.equipo2->nomEquipo,octa->partido.golesEq2,octa->partido.penales2);

}
int main()
{
    srand(time(NULL));
    nodoEquipo* listaEquipos=NULL;
    generarListaEquipos(&listaEquipos);
    int rta;
    Grupo grupos[CANTGRUPOS];
    generarArregloGrupos(grupos,listaEquipos);
    GrupoPartido partidosFaseGrupos[CANTGRUPOS];
    generarArregloPartidosFaseGrupos(partidosFaseGrupos,grupos);
    fase Fases[5];
    do
    {
        do
        {
            system("cls");
            printf("1. Modificar posibilidades\n");
            printf("2. Visualizar grupos\n");
            printf("3. Visualizar octavos\n");
            printf("4. Visualizar cuartos\n");
            printf("5. Visualizar semis\n");
            printf("6. Visualizar final\n");
            printf("7. Visualizar 3er puesto\n");
            printf("8. Visualizar arbol\n");
            printf("9. Visualizar estadisticas\n");
            printf("0. Salir\n");
            scanf("%i",&rta);
        }
        while (rta<0 || rta>9);
        switch (rta)
        {
        case 1:
            system("cls");
            modificarPosibilidades();
            system("pause");
            break;
        case 2:
            system("cls");

            mostrarGrupos(grupos,partidosFaseGrupos);
            system("pause");
            break;
        case 3:
            system("cls");
            generarArregloFases(Fases,grupos);
            mostrarFases(Fases,0);
            system("pause");
            break;
        case 4:
            system("cls");
            mostrarFases(Fases,1);
            system("pause");
            break;
        case 5:
            system("cls");
            mostrarFases(Fases,2);
            system("pause");
            break;
        case 6:
            system("cls");
            mostrarFases(Fases,4);
            system("pause");
            break;
        case 7:
            system("cls");
            mostrarFases(Fases,3);
            system("pause");
            break;
        case 8:
            system("cls");
            mostrarArbol(Fases);
            system("pause");
            break;
        case 9:
            system("cls");
            mostrarEstadisticas(listaEquipos);
            system("pause");
            break;
        }

    }
    while(rta!=0);
}
