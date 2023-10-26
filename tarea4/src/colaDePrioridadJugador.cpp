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

void insertarEnCP(TJugador jugador, TColaDePrioridadJugador &cp) {
  cp->ultimo++;
  // ubico el ultimo agregado donde corresponde
  nat posicion = cp->ultimo;
  while (posicion > 1 && edadTJugador(cp->jugadores[posicion/2]) > cp->prioridad*edadTJugador(jugador))
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

void eliminarPrioritario(TColaDePrioridadJugador &cp) {

} // eliminarPrioritario

bool estaEnCP(nat id, TColaDePrioridadJugador cp) {
  return (cp != NULL && id > 0 && id <= cp->maximo && cp->ids[id] != 0);
} // estaEnCP

nat prioridad(nat id, TColaDePrioridadJugador cp){
  return edadTJugador(cp->jugadores[1]);
}



