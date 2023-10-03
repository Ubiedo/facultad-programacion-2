#include "../include/fecha.h"

// Estructura para almacenar una fecha con día, mes y año
struct rep_fecha {
  nat dia, mes, anio;
};

// Función para crear un nuevo objeto de tipo TFecha con una fecha dada
TFecha crearTFecha(nat dia, nat mes, nat anio) {
  TFecha nuevaFecha = NULL;
  nuevaFecha = new rep_fecha;
  nuevaFecha->dia = dia;
  nuevaFecha->mes = mes;
  nuevaFecha->anio = anio;
  return nuevaFecha;
}

// Función para liberar un objeto de tipo TFecha previamente creado
void liberarTFecha(TFecha &fecha) {
  delete fecha;
  fecha = NULL;
}


// Función para imprimir una fecha representada por un objeto de tipo TFecha
void imprimirTFecha(TFecha fecha) {
  printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);
}

nat diasMes(nat mes, nat anio){
  switch (mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      return 31;
      break;
    case 2:
      if (anio % 4 == 0)
        {
	  return 29;
        }
      return 28;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
      break;
    default:
      // hubo un error, se introduce un mes no valido
      return 0;
    }
}

// Función para aumentar una fecha en una cantidad dada de días
void aumentarTFecha(TFecha &fecha, nat dias) {
  fecha->dia += dias;
  while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
    fecha->dia -= diasMes(fecha->mes, fecha->anio);
    fecha->mes++;
    if (fecha->mes > 12) {
      fecha->mes = 1;
      fecha->anio++;
    }
  } 
}

// Función para comparar dos fechas representadas por objetos de tipo TFecha
int compararTFechas(TFecha fecha1, TFecha fecha2) {
  int res = 0;
  if ((fecha1->anio > fecha2->anio) || (fecha1->anio == fecha2->anio && fecha1->mes > fecha2->mes) || (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia))
    {
      res = 1;
    } else if (!(fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia == fecha2->dia))
    {
      res = -1;
    }
  return res;
}

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha) {
  return crearTFecha(fecha->dia, fecha->mes, fecha->anio);
}