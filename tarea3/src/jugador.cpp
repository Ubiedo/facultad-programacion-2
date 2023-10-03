#include "../include/jugador.h"

struct rep_jugador {
  nat id;
  nat edad;
  char pais[100];
  char nombre[100];
  TPartida partida;
};

TJugador crearTJugador(nat id, nat edad, const char pais[100], const char nombre[100], TPartida partida) {
  TJugador jugador = new rep_jugador;
  jugador->id = id;
  jugador->edad = edad;
  strcpy(jugador->pais, pais);
  strcpy(jugador->nombre, nombre);
  jugador->partida = partida;
  return jugador;
}

void liberarTJugador(TJugador &jugador) {
  liberarTPartida(jugador->partida);
  delete jugador;
  jugador = NULL;
}

void imprimirTJugador(TJugador jugador) {
  printf("Jugador %d: %s, %s, %d años\n", jugador->id, jugador->nombre, jugador->pais, jugador->edad);
  imprimirTPartida(jugador->partida);
}

nat idTJugador(TJugador jugador) {
    return jugador->id;
}

nat edadTJugador(TJugador jugador) {
    return jugador->edad;
}

char* nombreTJugador(TJugador jugador) {
    return jugador->nombre;
}

char* paisTJugador(TJugador jugador) {
    return jugador->pais;
}

TPartida partidaTJugador(TJugador jugador) {
    return jugador->partida;
}

void agregarJugadaATJugador(TJugador &jugador, TJugada jugada){
  agregarEnTPartida(jugador->partida, jugada);
}

void removerJugadaDeTJugador(TJugador &jugador, int numeroDeJugada){
  removerDeTPartida(jugador->partida, numeroDeJugada);
}

bool estaEnPartidaDeTJugador(TJugador jugador, int numeroDeJugada){
  return estaEnTPartida(jugador->partida, numeroDeJugada);
}

TJugada obtenerDePartidaDeTJugador(TJugador jugador, int numeroDeJugada){
  return obtenerDeTPartida(jugador->partida, numeroDeJugada);
}

TJugador copiarTJugador(TJugador jugador){
  return crearTJugador(jugador->id, jugador->edad, jugador->pais, jugador->nombre, copiarTPartida(jugador->partida));
}
