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
  // resta invertir el heap si no es vacio
  if (cp->ultimo > 0){
    // creamos una nueva cp auxiliar para guardar los datos en el nuevo orden, O(n)
    TColaDePrioridadJugador nuevo = crearCP(cp->ultimo);
    // agrego los elemento, O(n*log(n))
    while (nuevo->ultimo != cp->ultimo){
      insertarEnCP(cp->jugadores[cp->ultimo - nuevo->ultimo], nuevo);
    }
    // agregar los de nuevo a la cola de prioridad O(n)
    for (nat i = 1; i <= cp->ultimo; i++)
    {
      cp->jugadores[i] = nuevo->jugadores[i];
      cp->ids[idTJugador(cp->jugadores[i])] = i;
      nuevo->jugadores[i] = NULL;
    }
    // eliminamos nuevo que ahora esta vacio
    liberarCP(nuevo); // O(n)
  }
  // por lo que nos queda O(n + n*log(n) + n + n) = O(n*log(n))
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
  int resultado; // es necesario ya que la resta puede ser negativa
  while (posicion > 1 && ((resultado = cp->prioridad*edadTJugador(cp->jugadores[posicion/2]) - cp->prioridad*edadTJugador(jugador)) > 0))
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
  int resultado;
  if (posicion + 1 > cp->ultimo)
  {
    return posicion;
  } else if ((resultado = cp->prioridad*edadTJugador(cp->jugadores[posicion]) - cp->prioridad*edadTJugador(cp->jugadores[posicion + 1])) > 0)
  {
    return posicion+1;
  }
  return posicion;
}

void eliminarPrioritario(TColaDePrioridadJugador &cp) {
  if (cp->ultimo > 0){
    cp->ids[idTJugador(cp->jugadores[1])] = 0;
    liberarTJugador(cp->jugadores[1]);
    cp->ultimo--;
    if (cp->ultimo > 0){
      TJugador reubicar = cp->jugadores[cp->ultimo+1];
      // reubicar el jugador deseado suponiendo que arranca como prioritario, dejarlo donde corresponde 
      nat posicion = 1, mayor;
      int resultado;
      while (posicion*2 <= cp->ultimo && ((resultado = cp->prioridad*edadTJugador(reubicar) - cp->prioridad*edadTJugador(cp->jugadores[(mayor = mayorPrioridad(cp, posicion*2))])) > 0))
      {
        cp->jugadores[posicion] = cp->jugadores[mayor];
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
