/*
  Módulo de implementación de `TColaDePrioridadJugador`.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/colaDePrioridadJugador.h"
#include "../include/utils.h"


#include <assert.h>
//#include <stdlib.h>
//#include <string.h>

struct rep_colaDePrioridadJugador {
  TJugador* jugadores;
  nat* ids;
  int prioridad;
  nat ultimo;
  nat maximo;
};

TColaDePrioridadJugador crearCP(nat N) {
  TColaDePrioridadJugador cola = new rep_colaDePrioridadJugador;
  cola->jugadores = new TJugador[(N+1)];
  cola->ids = new nat[(N+1)];
  for (nat i = 0; i < N+1; i++)
  {
    cola->jugadores[i] = NULL;
    cola->ids[i] = 0;
  }
  cola->maximo = N;
  cola->ultimo = 0;
  cola->prioridad = 1;
  return cola;
} // crearCP

void invertirPrioridad(TColaDePrioridadJugador &cp) {
  cp->prioridad *= -1;
  // resta invertir el heap
  // creo donde guardar de momento el nuevo conjunto
  TJugador* nuevo = new TJugador[(cp->ultimo)]
  // ahora voy agregando desde cp->ultimo hasta 0 en nuevo de menos prioritario a mas
  nat restanAgregar = cp->ultimo;
  if (restanAgregar > 1){
    nuevo[restanAgregar] = cp->jugadores[1];
    restanAgregar--;
  }
  if (restanAgregar > 1){
    nuevo[restanAgregar] = cp->jugadores[2];
    restanAgregar--;
  }
  // ahora el caso general
  while (restanAgregar > 0){
    // saber cual hay que agregar
    // como escribir en codigo lo hehco en papel
    restanAgregar--;
  }
  // agregar los de nuevo a la cola de prioridad
  for (nat i = 0; i < cp->ultimo; i++)
  {
    cola->jugadores[i] = nuevo[i];
    cola->ids[cola->jugadores[i]] = i;
    nuevo[i] = NULL;
  }
  // eliminamos nuevo que ahora esta vacio
  delete[] nuevo;
}

void liberarCP(TColaDePrioridadJugador &cp) {
  while (cp->ultimo > 0)
  {
    liberarTJugador(cp->jugadores[cp->ultimo]);
    cp->ultimo--;
  }
  delete[] cp->jugadores;
  delete[] cp->ids;
  delete cp;
  cp = NULL;
} // liberarCP

// tengo que hacerlo nuevo con el criterio de el menos prioritario a la izquierda
void insertarEnCP(TJugador jugador, TColaDePrioridadJugador &cp) {
  cp->ultimo++;
  // ubico el ultimo agregado donde corresponde
  nat posicion = cp->ultimo;
  while (posicion > 1 && (cp->prioridad*edadTJugador(cp->jugadores[posicion/2]) - cp->prioridad*edadTJugador(jugador) > 0))
  {
    cp->jugadores[posicion] = cp->jugadores[posicion/2];
    cp->ids[idTJugador(cp->jugadores[posicion])] = posicion;
    posicion /= 2;
  }
  cp->jugadores[posicion] = jugador;
  cp->ids[idTJugador(jugador)] = posicion;
} // insertarEnCP

bool estaVaciaCP(TColaDePrioridadJugador cp) {
  return (cp != NULL && cp->ultimo == 0);
} // estaVacioCP

TJugador prioritario(TColaDePrioridadJugador cp) {
  return cp->jugadores[1];
} // prioritario

nat mayorPrioridad(TColaDePrioridadJugador cp, nat posicion){
  if (posicion + 1 > cp->ultimo)
  {
    return posicion;
  } else if (edadTJugador(cp->jugadores[posicion]) > edadTJugador(cp->jugadores[posicion + 1]))
  {
    return posicion;
  }
  return posicion+1;
}

void eliminarPrioritario(TColaDePrioridadJugador &cp) {
  cp->ids[idTJugador(cp->jugadores[1])] = 0;
  liberarTJugador(cp->jugadores[1]);
  TJugador reubicar = cp->jugadores[cp->ultimo];
  cp->ultimo--;
  // reubicar el jugador deseado suponiendo que arranca como prioritario, dejarlo donde corresponde 
  nat posicion = 1, mayor;
  while (posicion*2 <= cp->ultimo && (cp->prioridad*edadTJugador(reubicar) - cp->prioridad*edadTJugador(cp->jugadores[(mayor = mayorPrioridad(cp, posicion*2))]) > 0))
  {
    cp->jugadores[posicion] = cp->jugadores[mayor];
    cp->ids[idTJugador(cp->jugadores[posicion])] = posicion;
    posicion = mayor;
  }
  cp->jugadores[posicion] = reubicar;
  cp->ids[idTJugador(reubicar)] = posicion;
} // eliminarPrioritario

bool estaEnCP(nat id, TColaDePrioridadJugador cp) {
  return (cp != NULL && id > 0 && id <= cp->maximo && cp->ids[id] != 0);
} // estaEnCP

nat prioridad(nat id, TColaDePrioridadJugador cp){
  return edadTJugador(cp->jugadores[cp->ids[id]]);
}



