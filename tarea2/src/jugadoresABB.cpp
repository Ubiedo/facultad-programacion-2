#include "../include/jugadoresABB.h"

struct rep_jugadoresABB {
  TJugador jugador;
  TJugadoresABB izquierda;
  TJugadoresABB derecha;
};

TJugadoresABB crearTJugadoresABB() {
  TJugadoresABB arbol = new rep_jugadoresABB;
  arbol->jugador = NULL;
  arbol->izquierda = NULL;
  arbol->derecha = NULL;
  return arbol;
}

bool esVacioTJugadoresABB(TJugadoresABB jugadoresABB) {
    return jugadoresABB->jugador != NULL;
}

void insertarTJugadoresABB(TJugadoresABB &jugadoresABB, TJugador jugador) {
  if (jugadoresABB == NULL){
    jugadoresABB = crearTJugadoresABB();
    jugadoresABB->jugador = jugador;
  } else {
    if (idTJugador(jugador) < idTJugador(jugadoresABB)){
      insertartTJugadores(jugadoresABB->izquierda, jugador);
    } else {
      insertarTJugadores(jugadoresABB->derecha, jugador);
    }
  }
}

void liberarTJugadoresABB(TJugadoresABB &jugadoresABB) {
  if (jugadoresABB->izquierda != NULL){
    liberarTJugadoresABB(jugadoresABB->izquierda);
  }
  if (jugadoresABB->derecha != NULL){
    liberarTJugadoresABB(jugadoresABB->derecha);
  }
  liberarTJugador(jugadoresABB->jugador);
  delete jugadoresABB;
  jugadoresABB = NULL;
}

void imprimirTJugadoresABB(TJugadoresABB jugadoresABB) {
  if (jugadoresABB->izquierda != NULL){
    imprimirTJugadoresABB(jugadoresABB->izquierda);
  }
  imprimirTJugador(jugadoresABB->jugador);
  if (jugadoresABB->derecha){
    imprimirTJugadoresABB(jugadoresABB->derecha);
  }
}

nat cantidadTJugadoresABB(TJugadoresABB jugadoresABB) {
  nat cantidad = 1;
  if (jugadoresABB->izquierda != NULL){
    cantidad += cantidadTJugadoresABB(jugadoresABB->izquierda);
  }
  if (jugadoresABB->derecha != NULL){
    cantidad += cantidadTJugadoresABB(jugadoresABB->derecha);
  }
  return cantidad;
}

TJugador maxIdJugador(TJugadoresABB jugadoresABB) {
  if (jugadoresABB->derecha != NULL){
    return idTJugador(jugadoresABB->jugador);
  }
  return maxIdJugador(jugadoresABB->derecha);
}

void removerTJugadoresABB(TJugadoresABB &jugadoresABB, nat id) {
  if (id < idTJugador(jugadoresABB->jugador)){
    remoiverTJugadoresABB(jugadoresABB->izquierda);
  } else if (id > idTJugador(jugadoresABB->derecha)){
    removerTJugadoresABB(jugadoresABB->derecha);
  } else {
    // encontrado, queda remplazarlo nomas
    liberarTJugador(jugadoresABB->jugador);
  }
}

bool estaTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
    return false;
}

TJugador obtenerDeTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
    return NULL;
}

nat alturaTJugadoresABB(TJugadoresABB jugadoresABB) {
    return 0;
}

bool esPerfectoTJugadoresABB(TJugadoresABB jugadoresABB) {
    return false;
}

TJugadoresABB mayoresTJugadoresABB(TJugadoresABB jugadoresABB, nat edad) {
    return NULL;
}
