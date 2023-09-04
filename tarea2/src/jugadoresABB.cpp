#include "../include/jugadoresABB.h"

struct rep_jugadoresABB {
  TJugador jugador;
  TJugadoresABB izquierda;
  TJugadoresABB derecha;
};

TJugadoresABB crearTJugadoresABB() {
  return NULL;
}

bool esVacioTJugadoresABB(TJugadoresABB jugadoresABB) {
    return jugadoresABB == NULL;
}

void insertarTJugadoresABB(TJugadoresABB &jugadoresABB, TJugador jugador) {
  if (jugadoresABB == NULL){
    jugadoresABB = new rep_jugadoresABB;
    jugadoresABB->izquierda = NULL;
    jugadoresABB->derecha = NULL;
    jugadoresABB->jugador = jugador;
  } else {
    if (idTJugador(jugador) < idTJugador(jugadoresABB->jugador)){
      insertarTJugadoresABB(jugadoresABB->izquierda, jugador);
    } else {
      insertarTJugadoresABB(jugadoresABB->derecha, jugador);
    }
  }
}

void liberarNodo(TJugadoresABB &jugadoresABB){
    delete jugadoresABB;
    jugadoresABB = NULL;
}

void liberarTJugadoresABB(TJugadoresABB &jugadoresABB) {
  if (jugadoresABB != NULL){
    liberarTJugadoresABB(jugadoresABB->izquierda);
    liberarTJugadoresABB(jugadoresABB->derecha);
    liberarTJugador(jugadoresABB->jugador);
    liberarNodo(jugadoresABB);
  }
}

void imprimirTJugadoresABB(TJugadoresABB jugadoresABB) {
  if (jugadoresABB != NULL){
    imprimirTJugadoresABB(jugadoresABB->izquierda);
    imprimirTJugador(jugadoresABB->jugador);
    imprimirTJugadoresABB(jugadoresABB->derecha);
  }
}

nat cantidadTJugadoresABB(TJugadoresABB jugadoresABB) {
  if (jugadoresABB != NULL){
    return cantidadTJugadoresABB(jugadoresABB->izquierda) + cantidadTJugadoresABB(jugadoresABB->derecha) + 1;
  }
  return 0;
}

TJugador maxIdJugador(TJugadoresABB jugadoresABB) {
  if (jugadoresABB->derecha != NULL){
    return jugadoresABB->jugador;
  }
  return maxIdJugador(jugadoresABB->derecha);
}

void removerTJugadoresABB(TJugadoresABB &jugadoresABB, nat id) {
  if (idTJugador(jugadoresABB->jugador) < id){
    removerTJugadoresABB(jugadoresABB->derecha, id);
  } else if (idTJugador(jugadoresABB->izquierda) > id){
    removerTJugadoresABB(jugadoresABB->izquierda, id);
  } else {
    // remplazar el encontrado
    liberarTJugador(jugadoresABB->jugador);
    if (jugadoresABB->izquierda == NULL){
      TJugadoresABB remplazo = jugadoresABB->derecha;
      liberarNodo(jugadoresABB);
      jugadoresABB = remplazo;
    } else if (jugadoresABB->derecha == NULL){
      TJugadoresABB remplazo = jugadoresABB->izquierda;
      liberarNodo(jugadoresABB);
      jugadoresABB = remplazo;
    } else {
      // tiene ambos subarboles no vacios, reemplazar por jugador de mayor id del subarbol izquierdo
      jugadoresABB->jugador = copiarTJugador(maxIdJugador(jugadoresABB->izquierda));
      // eliminar el nodo donde estaba el maxIdJugador
      removerTJugadoresABB(jugadoresABB->izquierda, idTJugador(jugadoresABB->jugador));
    }
  }
}

bool estaTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
  if (idTJugador(jugadoresABB->jugador) < id){
    return estaTJugadoresABB(jugadoresABB->derecha, id);
  } else if (idTJugador(jugadoresABB->izquierda) > id){
    return estaTJugadoresABB(jugadoresABB->izquierda, id);
  }
  return jugadoresABB != NULL;
}

TJugador obtenerDeTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
  if (idTJugador(jugadoresABB->jugador) < id){
    return estaTJugadoresABB(jugadoresABB->derecha, id);
  } else if (idTJugador(jugadoresABB->izquierda) > id){
    return estaTJugadoresABB(jugadoresABB->izquierda, id);
  }
  return jugadoresABB->jugador;
}

nat alturaTJugadoresABB(TJugadoresABB jugadoresABB) {
  if (jugadoresABB != NULL){
    nat alturaIzquierda = alturaTJugadoresABB(jugadoresABB->izquierda);
    nat alturaDerecha = alturaTJugadoresABB(jugadoresABB->derecha);
    if (alturaIzquierda > alturaDerecha){
      return alturaIzquierda + 1;
    } else {
      return alturaDerecha + 1;
    }
  }
  return 0;
}

bool esPerfectoTJugadoresABB(TJugadoresABB jugadoresABB) {
  if (jugadoresABB != NULL && (jugadoresABB->izquierda != NULL || jugadoresABB->derecha != NULL)){
    // estos son los casos a analizar el comportamiento de los hijos
    if ((jugadoresABB->izquierda != NULL && jugadoresABB->derecha == NULL) || (jugadoresABB->izquierda == NULL && jugadoresABB->derecha != NULL)){
      // ya que hay hijos de un lado pero no del otro
      return false;
    } else {
      // tiene ambos hijos
      // el codigo de abajo recorre mas de una vez los nodos, modificarlo
      return cantidadTJugadoresABB(jugadoresABB->izquierda) == cantidadTJugadoresABB(jugadoresABB->derecha);
    }
  }
  return true;
}

TJugadoresABB mayoresTJugadoresABB(TJugadoresABB jugadoresABB, nat edad) {
  return NULL;
}
