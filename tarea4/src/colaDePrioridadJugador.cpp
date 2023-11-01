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
    nat maximo = cp->ultimo;
    TJugador* mantener = new TJugador[maximo];
    for (nat i = 0; i < maximo; i++){
      mantener[i] = cp->jugadores[maximo - i];
      cp->jugadores[maximo - i] = NULL;
    }
    cp->ultimo = 0;
    for (nat k = 0; k < maximo; k++){
      insertarEnCP(mantener[k], cp);
      mantener[k] = NULL;
    }
    delete[] mantener;
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

// PRE: posicion1 y posicion2 son >= 1 y <= cp->ultimo
nat mayorPrioridad(TColaDePrioridadJugador cp, nat posicion1, nat posicion2){
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

// misma PRE que mayorPrioridad
// cambia de lugar a los jugadores en pos1 y pos2
void swap(TColaDePrioridadJugador cp, nat posicion1, nat posicion2){
  TJugador mantener = cp->jugadores[posicion1];
  cp->jugadores[posicion1] = cp->jugadores[posicion2];
  cp->jugadores[posicion2] = mantener;
  cp->ids[idTJugador(mantener)] = posicion2;
  cp->ids[idTJugador(cp->jugadores[posicion1])] = posicion1;
  mantener = NULL;
}

void insertarEnCP(TJugador jugador, TColaDePrioridadJugador &cp) {
  cp->ultimo++;
  nat posicion = cp->ultimo;
  cp->jugadores[posicion] = jugador;
  cp->ids[idTJugador(jugador)] = posicion;
  while (posicion > 1 && mayorPrioridad(cp, posicion, posicion/2) == posicion){
    swap(cp, posicion, posicion/2);
    posicion /= 2;
  }
} // insertarEnCP

bool estaVaciaCP(TColaDePrioridadJugador cp) {
  return (cp != NULL && cp->ultimo == 0);
} // estaVacioCP

TJugador prioritario(TColaDePrioridadJugador cp) {
  return cp->jugadores[1];
} // prioritario

void eliminarPrioritario(TColaDePrioridadJugador &cp) {
  if (cp->ultimo > 0){
    cp->ids[idTJugador(cp->jugadores[1])] = 0; // elimino el registro, osea que ya pertenece
    liberarTJugador(cp->jugadores[1]); // lo elimino
    cp->ultimo--; // bajo la cantidad de jugadores en el conjunto
    if (cp->ultimo > 0){
      cp->jugadores[1] = cp->jugadores[cp->ultimo + 1]; // lo remplazo por el ultimo
      cp->ids[idTJugador(cp->jugadores[1])] = 1; // ajusto su ubicacion registrada
      nat posicion = 1, mayor;
      // definir mayor
      if (3 > cp->ultimo){
        mayor = 2;
      } else {
        mayor = mayorPrioridad(cp, 2, 3);
      }
      while (posicion*2 <= cp->ultimo && mayorPrioridad(cp, posicion, mayor) == mayor){
        swap(cp, posicion, mayor);
        posicion = mayor;
        // redefinir mayor
        if (posicion*2 + 1 <= cp->ultimo){
          mayor = mayorPrioridad(cp, posicion*2, posicion*2+1);
        } else if (posicion*2 <= cp->ultimo){
          mayor = posicion*2;
        }
      }
    }
  }
} // eliminarPrioritario

bool estaEnCP(nat id, TColaDePrioridadJugador cp) {
  return (cp != NULL && id > 0 && id <= cp->maximo && cp->ids[id] != 0);
} // estaEnCP

nat prioridad(nat id, TColaDePrioridadJugador cp){
  return edadTJugador(cp->jugadores[cp->ids[id]]);
}
