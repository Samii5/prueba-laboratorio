/*
 ============================================================================
 Name        : tp bici
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "tp bicicleta.h"
#define T 20
/* 1 vacio y 0 lleno */



typedef struct
{
	int identificadorDeServicio; /* arranca de 2 mil y se suma */
	char descripcion[30];
	float precio;
	int isEmpty;

}eServicio;
float preciosDeServicio[4] = {250, 300, 400, 350};
char nombresDelServicio[4][15] = {"limpieza", "parche", "centrado", "cadena"};

typedef struct
{
	int dia;
	int mes;
	int anio;

}eFecha;

typedef struct
{
	int identificadorDeTrabajoDeUno;
	char marcaBicicleta[30];
	int rodadoBicicleta;
	int identificadorDeServicio;
	eFecha eFecha;
	int isEmpty;

}eTrabajo;

int cargarTrabajo(eTrabajo listaDeTrabajo[], int tam, int *id);
int mostrarTrabajo(eTrabajo listaDeTrabajo[], int tam, int identificador);
int BuscarLibre(eTrabajo listaDeTrabajo[], int tam);
int bajaTrabajo(eTrabajo listaDeTrabajo[], int tam, int guardarId);
int buscarTrabajo(eTrabajo listaDeTrabajo[], int tam, int identificador);
int validarFecha(int dia, int mes, int anio);
int modificarEmpleado(eTrabajo listaDeTrabajo[], int tam, int identificadorDeTrabajoDeUno);
void OrdenarTrabajosPorAnio(eTrabajo listaDeTrabajo[], int tam);



int mostrarServicios(eServicio listaDeServicios[], int tam, int identificadorDeServicio);
int cargarServicios(eServicio listaDeServicios[], int tam, int identificadorDeServicio);
int buscarServicio(eServicio listaDeServicios[], int tam, int identificador);



int main(void)
{
	setbuf(stdout,NULL);
	fflush(stdin);

	char seguir = 's';
	int identificadorDeServicio = 2000;
	int identificadorDeTrabajoDeUno = 1;
	int devuelve;
	int opcion;
	int guardarId;
	eTrabajo listaDeTrabajo[T];
	eServicio listaDeServicios[T];
	int bandera1 = 0;

	for(int i=0;i < T;i++)
	{
		listaDeTrabajo[i].isEmpty=1;
	}

	while(seguir=='s')
	{
		printf(
	    "\n 1.ALTA trabajo"
	    "\n 2.BAJA trabajo"
	    "\n 3.MODIFICAR trabajo"
	    "\n 4.LISTAR trabajos en orden de años de < a > "
		"\n 5.Crear y LISTAR Servicios"
		"\n 6.TOTAL en pesos de servicios prestados"
	    "\n 7.SALIR");
		printf("\n Elija una opcion: ");
		scanf("%d", &opcion);

		switch(opcion)
		{
			case 1:
				devuelve = cargarTrabajo(listaDeTrabajo, T, &identificadorDeTrabajoDeUno);
				if (devuelve == 0)
				{
					printf("trabajo ingresado con exito!!!\n");
				}
				else
				{
					printf("No hay mas lugar en la lista para trabajos !!\n");
				}
				bandera1=1;
			break;

			case 2:
				if (bandera1==0)
				{
					printf("\n error,no ingresaste trabajos");
				} // fin del if
				else
				{
					mostrarTrabajo(listaDeTrabajo,T , identificadorDeTrabajoDeUno);
					printf("ingrese el id del trabajo que desee dar de baja");
					scanf("%d", &guardarId);
					devuelve = bajaTrabajo(listaDeTrabajo,T ,guardarId);
					if (devuelve == 1)
					{
						printf("trabajo dado de baja con exito!!!\n");
					}
					else
					{
						printf("No se dio de baja !!\n");
					}
				 } // fin del else
			break;

			case 3:
				if (bandera1==0)
				{
					printf("\n error,no ingresaste ningun trabajo");
				}
				else
				{
					mostrarTrabajo(listaDeTrabajo,T , identificadorDeTrabajoDeUno);
					printf("ingrese el id que desea modificar");
					scanf("%d", &guardarId);
					devuelve = modificarEmpleado(listaDeTrabajo, T, identificadorDeTrabajoDeUno);
					if(devuelve ==1)
					{
						printf("trabajo modificado con exito!!!\n");
					}
					else
					{
						printf("No se pudo modificar !!\n");
					}

				}// fin del else gordo

			break;

			case 4:
				if (bandera1==0)
				{
					printf("\n error,no ingresaste ningun trabajo");
				}
				else
				{
					mostrarTrabajo(listaDeTrabajo,T , identificadorDeTrabajoDeUno);
					printf("ahora se mostraran ordenados segun su año y marca de bicileta \n");
				    OrdenarTrabajosPorAnio(listaDeTrabajo, T);
					mostrarTrabajo(listaDeTrabajo,T , identificadorDeTrabajoDeUno);

				}

			break;

			case 5:
				//mostrarServicios(listaDeServicios, T, identificadorDeServicio);
				devuelve = cargarServicios(listaDeServicios, T, identificadorDeServicio);
				if (devuelve == 0)
				{
					printf("listado de servicios ingresado con exito!!!\n");

				}
				else
				{
					printf("No se hizo el listado!!\n");
				}

			break;

			case 6:

			break;

			case 7:
				printf("si desea seguir escribe s sino n");
				fflush(stdin);
				scanf("%c", &seguir);
			break;

		} // fin del switch

    } // fin del while

return 0;

} // fin del main

int BuscarLibre(eTrabajo listaDeTrabajo[], int tam)
{
	int lugarLibre =-1;

	if(listaDeTrabajo != NULL && tam > 0)
	{
		for(int i=0; i < tam; i++)
		{
			if(listaDeTrabajo[i].isEmpty == 1)
			{
				lugarLibre = i;
				break;
			} // fin del if

		} // fin del for

	} // fin del if

return lugarLibre;
}// fin de buscar libre

int cargarTrabajo(eTrabajo listaDeTrabajo[], int tam, int *id)
{
	int libre;
	libre = BuscarLibre(listaDeTrabajo, tam);
	eTrabajo miTrabajo;
	eFecha miFecha;
	int respuesta;

	if(listaDeTrabajo != NULL && tam > 0 && libre > -1)
	{
		printf("Ingrese la marca de la bicileta: ");
		fflush(stdin);
		scanf("%[^\n]", miTrabajo.marcaBicicleta);

		printf(" Ingrese el rodado bicicleta: ");
		scanf("%d", &miTrabajo.rodadoBicicleta);

		printf(" Ingrese id servicio : ");
		scanf("%d", &miTrabajo.identificadorDeServicio);

		printf("ingrese dia: ");
		scanf("%d", &miFecha.dia);
		printf("ingrese el mes: ");
		scanf("%d", &miFecha.mes);
		printf("ingrese anio");
		scanf("%d", &miFecha.anio);
        respuesta = validarFecha(miFecha.dia, miFecha.mes, miFecha.anio);

while(respuesta == 0)
{
	printf("error, ingreso un numero invalido en el dia o en el mes \n");
	printf("ingrese dia: ");
	scanf("%d", &miFecha.dia);
	printf("ingrese el mes: ");
	scanf("%d", &miFecha.mes);
	printf("ingrese anio");
	scanf("%d", &miFecha.anio);
	respuesta = validarFecha(miFecha.dia, miFecha.mes, miFecha.anio);

}// fin del while

	strcpy(listaDeTrabajo[libre].marcaBicicleta , miTrabajo.marcaBicicleta);
	listaDeTrabajo[libre].rodadoBicicleta = miTrabajo.rodadoBicicleta;
	listaDeTrabajo[libre].identificadorDeServicio =miTrabajo.identificadorDeServicio;
	listaDeTrabajo[libre].eFecha.dia = miFecha.dia;
	listaDeTrabajo[libre].eFecha.mes = miFecha.mes;
	listaDeTrabajo[libre].eFecha.anio = miFecha.anio;
	listaDeTrabajo[libre].identificadorDeTrabajoDeUno = *id;
	(*id) ++;
	listaDeTrabajo[libre].isEmpty = 0;

	} // fin del if

return 0;
} /*fin de cargar trabajo */

int mostrarTrabajo(eTrabajo listaDeTrabajo[], int tam, int identificador)
{

int i;
int retorno =0;

if(listaDeTrabajo != NULL && tam > 0)
{
	for(i=0; i<tam; i++)
	 {
		if(listaDeTrabajo[i].isEmpty == 0)
		{
			printf("%d %s %d %d %d %d %d \n ", listaDeTrabajo[i].identificadorDeTrabajoDeUno,
											   listaDeTrabajo[i].marcaBicicleta,
											   listaDeTrabajo[i].rodadoBicicleta,
											   listaDeTrabajo[i].identificadorDeServicio,
											   listaDeTrabajo[i].eFecha.dia,
											   listaDeTrabajo[i].eFecha.mes,
											   listaDeTrabajo[i].eFecha.anio);

			void OrdenarTrabajosPorAnio(eTrabajo listaDeTrabajo[], int tam);


			retorno = 1;
		} // fin del if

	 } // fin del for

} // fin del if

return retorno;
} // fin de mostrar trabajos

int buscarTrabajo(eTrabajo listaDeTrabajo[], int tam, int identificador)
{

int indice = -1;

  if (listaDeTrabajo != NULL && tam > 0)
  {
	   for (int i=0; i< tam; i++)
	   {
		   if (listaDeTrabajo[i].identificadorDeTrabajoDeUno && listaDeTrabajo[i].isEmpty == 0)
		   {
			   indice = i;
			   break;
		   }
	   }
  }
 return indice;
} // fin de buscar Trabajo

int bajaTrabajo(eTrabajo listaDeTrabajo[],int tam, int guardarId)
{
	int resultado = 0;

	for(int i = 0; i < tam; i++)
	{
		if(listaDeTrabajo[i].identificadorDeTrabajoDeUno == guardarId)
		{
			listaDeTrabajo[i].isEmpty = 1;
			resultado = 1;
			break;
		}
	}

return resultado;
} // fin de baja Trabajo


int modificarEmpleado(eTrabajo listaDeTrabajo[], int tam, int identificadorDeTrabajoDeUno)
{
	   int modificacion;
	   int indice = 1;
	   int NuevoeDia;
	   int NuevoeMes;
	   int NuevoAnio;
	   int NuevoIdentificadorDeServicio;
	   char nuevaMarcaBicicleta[30];
 	   int nuevoRodadoBicicleta;

	  mostrarTrabajo(listaDeTrabajo, T, identificadorDeTrabajoDeUno);
	  printf("repita el ID que quiere modificar por favor");
	  scanf("%d", &identificadorDeTrabajoDeUno);

	  printf("ingrese lo que quiere modificar de ese trabajo\n: "
			  	  	  	  	  	  	  	  	  	  	  	  	 "1.marcaBicicleta\n "
			  	  	  	  	  	  	  	  	  	  	  	  	 "2.rodadoBicicleta\n "
			  	  	  	  	  	  	  	  	  	  	  	  	 "3.identificadorDeServicio\n "
			  	  	  	  	  	  	  	  	  	  	  	  	 "4.eFecha.dia\n "
			  	  	  	  	  	  	  	  	  	  	  	  	 "5.eFecha.mes\n "
			  	  	  	  	  	  	  	  	  	  	  	  	 "6.eFecha.anio");
	  scanf("%d%*c", &modificacion);

	  switch(modificacion)
	  {
		  case 1:
			printf("Ingrese la nueva marca de bicicleta: ");
			fflush(stdin);
			gets(nuevaMarcaBicicleta);
			strcpy(listaDeTrabajo[indice].marcaBicicleta, nuevaMarcaBicicleta);

		  break;

		  case 2:
			printf("Ingrese el nuevo rodado de bicicleta: ");
			scanf("%d", &nuevoRodadoBicicleta);
			listaDeTrabajo[indice].rodadoBicicleta = nuevoRodadoBicicleta;
		  break;

		  case 3:
			  printf("ingrese el nuevo identificador de servicio");
			  scanf("%d", &NuevoIdentificadorDeServicio);
			  listaDeTrabajo[indice].identificadorDeServicio = NuevoIdentificadorDeServicio;
		  break;

		  case 4:
			  printf("ingrese el nuevo dia");
			  scanf("%d", &NuevoeDia);
			  listaDeTrabajo[indice].eFecha.dia = NuevoeDia;
		  break;

		  case 5:
			  printf("ingrese el nuevo mes");
			  scanf("%d", &NuevoeMes);
			  listaDeTrabajo[indice].eFecha.mes = NuevoeMes;
		  break;

		  case 6:
			  printf("ingrese el nuevo anio");
			  scanf("%d", &NuevoAnio);
			  listaDeTrabajo[indice].eFecha.anio = NuevoAnio;
		  break;
	  }
return indice;
} /*fin de modificar empleado */



int validarFecha(int dia, int mes, int anio)
{
	int devuelve = 0;

if ( mes >= 1 && mes <= 12 )
{
	switch (mes)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:

			if ( dia >= 1 && dia <= 31 )
			{
			  devuelve = 1;
			}
			else
			{
			  printf( "\n   la fecha debe ser mayor a 1 y menor a 31" );
			}
		break;

			case 4:
			case 6:
			case 9:
			case 11:
				if ( dia >= 1 && dia <= 30 )
				{
				  devuelve = 1;
				}
				else
				{
				  printf( "\n   la fecha debe ser mayor a 1 y menor a 30" );
				}
		break;

		case 2:
				if ( dia >= 1 && dia <= 29 )
				{
					devuelve = 1;
				}
				else
				{
					  printf( "\n   la fecha debe ser mayor a 1 y menor a 29" );
				}
		break;
	}// FIN DEL SWITCH
} // FIN DEL IF
return devuelve;
}

void OrdenarTrabajosPorAnio(eTrabajo listaDeTrabajo[], int tam)
{
eTrabajo auxiliarTrabajo;
eTrabajo auxiliarDos;
int i;
int j;

for(i=0; i<tam-1; i++)
{
	for(j=i+1; j<tam; j++)
	{
		if(listaDeTrabajo[i].eFecha.anio < listaDeTrabajo[j].eFecha.anio || listaDeTrabajo[i].eFecha.anio == listaDeTrabajo[j].eFecha.anio)
		{
			auxiliarTrabajo = listaDeTrabajo[i];
			listaDeTrabajo[i] = listaDeTrabajo[j];
			listaDeTrabajo[j] = auxiliarTrabajo;

			if(listaDeTrabajo[i].marcaBicicleta > listaDeTrabajo[j].marcaBicicleta)
			{
				auxiliarDos = listaDeTrabajo[i];
				listaDeTrabajo[i] = listaDeTrabajo[j];
				listaDeTrabajo[j] = auxiliarDos;
			}

		}// fin del if


	} // fin del primer for

}// fin del segundo for

}// fin del ordenamiento



/// parte de servicios





int buscarServicio(eServicio listaDeServicios[], int tam, int identificador)
{
int lugarLibre =-1;

	if(listaDeServicios != NULL && tam > 0)
	{
		for(int i=0; i < tam; i++)
		{
			if(listaDeServicios[i].isEmpty == 1)
			{
				lugarLibre = i;
				break;
			} // fin del if

		} // fin del for

	} // fin del if

return lugarLibre;
}// fin de buscar libre


int MostrarServicios(eServicio listaDeServicios[], int tam, int identificadorDeServicio)
{
int i;
int retorno = 0;

	if(listaDeServicios != NULL && tam > 0)
	{
		for(i=0; i<tam; i++)
		 {
			if(listaDeServicios[i].isEmpty == 0)
			{
				printf("%s %f %d\n ", listaDeServicios[i].descripcion,
									  listaDeServicios[i].precio,
									  listaDeServicios[i].identificadorDeServicio);

				retorno = 1;
			} // fin del if

		 } // fin del for

	} // fin del if

return retorno;
}

int cargarServicios(eServicio listaDeServicios[], int tam, int identificadorDeServicio)
{
	int retorno = 0;
	int libre;
	eServicio miServicio;
	libre = buscarServicio(listaDeServicios, tam, identificadorDeServicio);

		if(listaDeServicios != NULL && tam > 0 && libre > -1)
		{
			printf("Ingrese la descripcion del servicio: ");
			fflush(stdin);
			scanf("%[^\n]", miServicio.descripcion);

			printf(" Ingrese el servicio que va a usar\n 1.limpieza \n 2.parche \n 3.centrado \n 4.cadena: ");
			scanf("%f", &miServicio.precio);

			printf(" Ingrese id servicio : ");
			scanf("%d", &miServicio.identificadorDeServicio);

			strcpy(listaDeServicios[libre].descripcion , miServicio.descripcion);
			listaDeServicios[libre].precio = miServicio.precio;
			listaDeServicios[libre].identificadorDeServicio =miServicio.identificadorDeServicio;
			//listaDeServicios[libre].identificadorDeServicio = identificadorDeServicio;
			(identificadorDeServicio) ++;
			listaDeServicios[libre].isEmpty = 0;

		}// fin del if

return retorno;
}// fin de cargar servicios




