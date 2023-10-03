#include "../include/jugada.h"

// Define la estructura Jugada
struct rep_jugada {
  int numero;
  Movimiento movimientos[4];
};

// Crea una jugada con los valores dados
TJugada crearTJugada(int numero, Movimiento mov1, Movimiento mov2, Movimiento mov3, Movimiento mov4){
  TJugada jugada = new rep_jugada;
  jugada->numero = numero;
  jugada->movimientos[0] = mov1;
  jugada->movimientos[1] = mov2;
  jugada->movimientos[2] = mov3;
  jugada->movimientos[3] = mov4;
  return jugada;
}

// Función que retorna el numero de la jugada
int numeroTJugada(TJugada jugada){
  return jugada->numero;
}

// Función que retorna los movimientos de una jugada
Movimiento * movimientoTJugada(TJugada jugada) {
  return jugada->movimientos;
}

// Devuelve true si y solo si la jugada tiene el movimiento mov en la posicion pos
bool tieneMovimientoEnPosTJugada(TJugada jugada, int pos, Movimiento mov){
  return jugada->movimientos[pos-1] == mov;
}

// Imprime la jugada
void imprimirTJugada(TJugada jugada) {
  printf("Jugada: %d \n", jugada->numero);
  printf("Movimientos: ");
  for (int i = 0; i < 4; i++){
    //Derecha = 1, Izquierda = 2, Arriba = 3, Abajo = 4
    switch(jugada->movimientos[i]){
    case Derecha:
    printf("Derecha ");
    break;
    case Izquierda:
      printf("Izquierda ");
      break;
    case Arriba:
    printf("Arriba ");
    break;
    case Abajo:
      printf("Abajo ");
      break;
    }
  }
  printf("\n");
}

// Libera la memoria asignada para un jugada
void liberarTJugada(TJugada &jugada) {
  delete jugada;
  jugada = NULL;
}

// Retorna una copia de la jugada
TJugada copiarTJugada(TJugada jugada) {
  return crearTJugada(jugada->numero, jugada->movimientos[0], jugada->movimientos[1], jugada->movimientos[2], jugada->movimientos[3]);
}