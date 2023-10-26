/*
  Módulo de definición de 'TColaDePrioridadJugador'.

  Los elementos de tipo 'TColaDePrioridadJugador' son colas de prioridad cuyos
  elementos son de tipo 'TJugador' y cuya prioridad se define por la edad del jugador.

  Los jugadores son únicos, por lo que no es posible que haya dos jugadores con el
  mismo id ni con el mismo nombre.
  Se asume que los ids de los jugadores están acotados entre 1 y N, siendo N el
  tamaño de la cola.

  El criterio para establecer la prioridad entre jugadores es, de manera
  predeterminada, que un jugador es prioritario ante otro si la edad es menor que la del otro jugador. Este criterio se puede modificar (con la función invertirPrioridad), haciendo que el jugador prioritario sea el de mayor edad. 
  
   Si hay más de un jugador con la misma edad el prioritario es cualquiera de los dos.

  Si la 'TColaDePrioridadJugador' no es vacía hay un jugador considerado el
  prioritario, según el criterio de prioridad. 


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CP_H
#define _CP_H

#include "utils.h"
#include "jugador.h"

/* Representación de 'TColaDePrioridadJugador'
   Se debe definir en colaDePrioridadJugador.cpp
   el struct rep_colaDePrioridadJugador;
 
   Declaración del tipo 'TColaDePrioridadJugador'
*/
typedef struct rep_colaDePrioridadJugador *TColaDePrioridadJugador;


/*
  Devuelve una 'TColaDePrioridadJugador' vacía (sin elementos) que puede
  contener hasta N jugadores.
  La prioridad entre dos jugadores se define por el que tenga menor edad.
  El tiempo de ejecución en el peor caso es Theta(N).
 */
TColaDePrioridadJugador crearCP(nat N); 

/*
  Modifica el criterio de prioridad: si el prioritario era el jugador que tenía menor
  edad pasa a ser el que tiene mayor edad, y viceversa.
  Debe modificar la cola de forma de que se respete el nuevo criterio de prioridad.
  Se pide que el tiempo de ejecución en el peor caso sea O(n*log n), siendo 'n' la cantidad de
  elementos de 'cp'. Sin embargo, existe una solución que lo hace en O(n).
 */
void invertirPrioridad(TColaDePrioridadJugador &cp);

/*
  Libera la memoria asignada a 'cp' y a cada uno de sus elementos.
  Es decir, libera la memoria asociada a todos los jugadores que estén en la cola.
  El tiempo de ejecución en el peor caso es O(N*m), siendo 'N' el parámetro
  pasado en crearCP y 'm' la cantidad de jugadas en la partida con mayor cantidad
  de jugadas.
 */
void liberarCP(TColaDePrioridadJugador &cp);

/*
  Inserta 'jugador' en 'cp'.
  El tiempo de ejecución en el peor caso es Theta(log N) donde 'N' el parámetro pasado en crearCP.
  PRE: !estaEnCP(jugador, cp)
  PRE: 1 <= idJugador <= N, siendo 'N' el parámetro pasado en crearCP.
 */
void insertarEnCP(TJugador jugador, TColaDePrioridadJugador &cp);

/*
  Devuelve 'true' si y solo si en 'cp' no hay elementos.
  El tiempo de ejecución en el peor caso es Theta(1).
 */
bool estaVaciaCP(TColaDePrioridadJugador cp);

/*
  Devuelve el jugador prioritario de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
  PRE: !estaVaciaCP(cp).
 */
TJugador prioritario(TColaDePrioridadJugador cp);

/*
  Elimina de 'cp' el jugador prioritario y libera la memoria asociada.
  Si estaVacioCP(cp) la operación no tiene efecto.
  El tiempo de ejecución en el peor caso es O(log N + m), siendo 'N' el parámetro
  pasado en crearCP y 'm' la cantidad de jugadas del jugador prioritario.
 */
void eliminarPrioritario(TColaDePrioridadJugador &cp);

/*
  Devuelve 'true' si y solo si el jugador con 'id' es un elemento de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnCP(nat id, TColaDePrioridadJugador cp);

/*
  Devuelve el valor de prioridad (la edad) asociada al jugador con 'id'.
  Precondición: estaEnCp(id, cp).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat prioridad(nat id, TColaDePrioridadJugador cp);

#endif


