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
  bool prioridad;
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
  cola->prioridad = true;
  return cola;
} // crearCP

void invertirPrioridad(TColaDePrioridadJugador &cp) {
  cp->prioridad = !cp->prioridad;
  // resta invertir el heap si no es vacio
  if (cp->ultimo > 0){
    // creamos una nueva cp auxiliar para guardar los datos en el nuevo orden, O(n)
    TJugador* nuevo = new TJugador[(cp->ultimo)];
    for (nat k = 0; k <= cp->ultimo; k++){
      if (cp->jugadores[cp->ultimo - k] == NULL){
        printf("\n\nERROR\n\n");
      }
      nuevo[k] = cp->jugadores[cp->ultimo - k];
      cp->jugadores[k+1] = NULL;
    }
    nat max = cp->ultimo;
    cp->ultimo = 0;
    // agregar los de nuevo a la cola de prioridad O(n)
    for (nat i = 0; i < max; i++){
      insertarEnCP(nuevo[i], cp);
      nuevo[i] = NULL;
    }
    // eliminamos nuevo que ahora esta vacio
    delete[] nuevo;
  }
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

nat mayorPrioridad(TColaDePrioridadJugador cp, nat posicion1, nat posicion2){
  if (posicion2 > cp->ultimo){
    return posicion1;
  }
  if (cp->prioridad){ // es prioritario el menor
    if (edadTJugador(cp->jugadores[posicion1]) > edadTJugador(cp->jugadores[posicion2])){
      return posicion2;
    }
    return posicion1;
  } // sino es prioritario el mayor
  if (edadTJugador(cp->jugadores[posicion1]) > edadTJugador(cp->jugadores[posicion2])){
    return posicion1;
  }
  return posicion2;
}

void insertarEnCP(TJugador jugador, TColaDePrioridadJugador &cp) {
  cp->ultimo++;
  nat posicion = cp->ultimo;
  cp->jugadores[posicion] = jugador;
  imprimirTJugador(jugador);
  while (posicion > 1 && mayorPrioridad(cp, posicion, posicion/2) == posicion)
  {
    cp->jugadores[posicion] = cp->jugadores[posicion/2];
    cp->jugadores[posicion/2] = jugador;
    cp->ids[idTJugador(cp->jugadores[posicion])] = posicion;
    posicion /= 2;
  }
  cp->ids[idTJugador(jugador)] = posicion;
} // insertarEnCP

bool estaVaciaCP(TColaDePrioridadJugador cp) {
  return (cp != NULL && cp->ultimo == 0);
} // estaVacioCP

TJugador prioritario(TColaDePrioridadJugador cp) {
  return cp->jugadores[1];
} // prioritario

void eliminarPrioritario(TColaDePrioridadJugador &cp) {
  if (cp->ultimo > 0){
    cp->ids[idTJugador(cp->jugadores[1])] = 0;
    liberarTJugador(cp->jugadores[1]);
    cp->ultimo--;
    if (cp->ultimo > 0){
      TJugador reubicar = cp->jugadores[cp->ultimo+1];
      cp->jugadores[1] = reubicar;
      // reubicar el jugador deseado suponiendo que arranca como prioritario, dejarlo donde corresponde 
      nat posicion = 1, mayor;
      while (posicion*2 <= cp->ultimo && (mayor = mayorPrioridad(cp, posicion*2, posicion*2+1)) > 0 && mayorPrioridad(cp, mayor, posicion) == mayor)
      {
        cp->jugadores[posicion] = cp->jugadores[mayor];
        cp->jugadores[mayor] = reubicar;
        cp->ids[idTJugador(cp->jugadores[posicion])] = posicion;
        posicion = mayor;
      }
      cp->jugadores[posicion] = reubicar;
      cp->ids[idTJugador(reubicar)] = posicion;
    }
  }
} // eliminarPrioritario

bool estaEnCP(nat id, TColaDePrioridadJugador cp) {
  return (cp != NULL && id > 0 && id <= cp->maximo && cp->ids[id] != 0);
} // estaEnCP

nat prioridad(nat id, TColaDePrioridadJugador cp){
  return edadTJugador(cp->jugadores[cp->ids[id]]);
}
