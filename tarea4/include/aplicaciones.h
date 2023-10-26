/*
  Módulo de definición de 'aplicaciones'.

  El módulo de acplicaciones es para practicar el USO de TADs.
  Durante la implementación sólo se deben utilizar los TADs.
  Nunca se puede acceder a la representación de los datos.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef APLICACIONES_H
#define APLICACIONES_H

#include "tablaJugadores.h"

#define MAX_ID 10

/*
  Dada una tabla de jugadores 't' y un arreglo de nombres 'nombres' de
  longitud 'n', imprime en pantalla los datos de los jugadores en 'nombres'
  que están en 't', en orden ascendente según su edad (de menor a mayor).
  Se  asume que los IDs de los jugadores están acotados entre 1 y MAX_ID.
  El tiempo de ejecución en promedio es O(n*log n+ n*m), siendo 'n' la cantidad de nombres de los jugadores de la tabla y 'm' la maxima cantidad de jugadas que posea un jugador.
  Se debe utilizar una cola de prioridad auxiliar para resolver el problema.
 */
void listarEnOrden(TTablaJugadores t, char** nombres, nat n);

#endif  // APLICACIONES_H
