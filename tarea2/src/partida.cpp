#include "../include/partida.h"

struct rep_partida {
  TJugada jugada;
  TPartida sig;
};

TPartida crearTPartida(){
  return NULL;
}

void agregarEnTPartida(TPartida& partida, TJugada jugada){
  if (partida == NULL){
    // crear la partida, hay 0 elementos previos
    partida = new rep_partida;
    partida->jugada = jugada;
    partida->sig = NULL;
  } else {
    // hay almenos un elemento previo
    TPartida agregar = new rep_partida;
    agregar->jugada = jugada;
    agregar->sig = partida;
    if (numeroTJugada(partida->jugada) > numeroTJugada(jugada)){
      partida = agregar;
    } else {
      while (agregar->sig->sig != NULL && numeroTJugada(agregar->sig->sig->jugada) < numeroTJugada(jugada)){
	agregar->sig = agregar->sig->sig;
      }
      if (agregar->sig->sig == NULL){
	agregar->sig->sig = agregar;
	agregar->sig = NULL;
      } else {
	TPartida ubicacion = agregar->sig->sig;
	agregar->sig->sig = agregar;
	agregar->sig = ubicacion;
      }
    }
  }
}

void imprimirTPartida(TPartida partida){
  TPartida imprimir = partida;
  while (imprimir != NULL){
    imprimirTJugada(imprimir->jugada);
    imprimir = imprimir->sig;
  }
}

void liberarTPartida(TPartida& partida){
  TPartida liberar = partida;
  while (liberar != NULL){
    partida = partida->sig;
    liberarTJugada(liberar->jugada);
    delete liberar;
    liberar = partida;
  }
}

bool esVaciaTPartida(TPartida partida){
  return partida == NULL;
}

TPartida copiarTPartida(TPartida partida){
  TPartida nueva = NULL, copiar = partida, copia = NULL, conector = NULL;
  if (partida != NULL){
    nueva = new rep_partida;
    nueva->sig = NULL;
    nueva->jugada = copiarTJugada(copiar->jugada);
    conector = nueva;
    copiar = copiar->sig;
    while (copiar != NULL){
      copia = new rep_partida;
      copia->jugada = copiarTJugada(copiar->jugada);
      conector->sig = copia;
      conector = copia;
      copiar = copiar->sig;
    }
    copia->sig = NULL;
  }
  return nueva;
}

bool estaEnTPartida(TPartida partida, int numeroDeJugada){
  TPartida buscar = partida;
  while (buscar != NULL && numeroTJugada(buscar->jugada) != numeroDeJugada){
    buscar = buscar->sig;
  }
  return buscar != NULL;
}

TJugada obtenerDeTPartida(TPartida partida, int numeroDeJugada){
  TPartida buscada = partida;
  while (numeroTJugada(buscada->jugada) != numeroDeJugada){
    buscada = buscada->sig;
  }
  return buscada->jugada;
}

void imprimirJugadasConMovimiento(TPartida partida, int pos, Movimiento mov){
  TPartida buscada = partida;
  while (buscada != NULL){
    if (tieneMovimientoEnPosTJugada(buscada->jugada, pos, mov)){
      imprimirTJugada(buscada->jugada);
    }
    buscada = buscada->sig;
  }
}

void removerDeTPartida(TPartida& partida, int numeroDeJugada){
  TPartida buscada = partida, anterior = NULL;
  while (numeroTJugada(buscada->jugada) != numeroDeJugada){
    anterior = buscada;
    buscada = buscada->sig;
  }
  if (anterior != NULL){
    anterior->sig = buscada->sig;
  } else {
    partida = buscada->sig;
  }
  liberarTJugada(buscada->jugada);
  delete buscada;
}
