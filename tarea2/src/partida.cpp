#include "../include/partida.h"

struct rep_partida {
  TJugada jugada;
  TPartida sig;
};

TPartida crearTPartida(){
  TPartida partida = new rep_partida;
  partida->jugada = NULL;
  partida->sig = NULL;
  return partida;
}

void agregarEnTPartida(TPartida& partida, TJugada jugada){
  if (partida->jugada == NULL){
    partida->jugada = jugada;
  } else {
    TPartida nueva = crearTPartida();
    nueva->jugada = jugada;
    nueva->sig = partida;
    if (numeroTJugada(partida->jugada) > numeroTJugada(jugada)){
      partida = nueva;
    } else {
      while (nueva->sig->sig != NULL && numeroTJugada(nueva->sig->sig->jugada) < numeroTJugada(jugada)){
	nueva->sig = nueva->sig->sig;
      }
      if (nueva->sig->sig == NULL){
	nueva->sig->sig = nueva;
	nueva->sig = NULL;
      } else {
	TPartida ubicacion = nueva->sig->sig;
	nueva->sig->sig = nueva;
	nueva->sig = ubicacion;
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
  TPartida liberar = NULL;
  while (partida != NULL){
    liberar = partida;
    liberarTJugada(liberar->jugada);
    partida = partida->sig;
    delete liberar;
  }
}

bool esVaciaTPartida(TPartida partida){
    return partida->jugada == NULL;
}

TPartida copiarTPartida(TPartida partida){
  TPartida nueva = crearTPartida(), copiar = partida, copia = NULL, conector = NULL;
  if (copiar->jugada != NULL){
    nueva->jugada = copiarTJugada(copiar->jugada);
    conector = nueva;
    copiar = copiar->sig;
    while (copiar != NULL){
      copia = crearTPartida();
      copia->jugada = copiarTJugada(copiar->jugada);
      conector->sig = copia;
      conector = copia;
      copiar = copiar->sig;
    }
  }
  return nueva;
}

bool estaEnTPartida(TPartida partida, int numeroDeJugada){
  TPartida jugada = partida;
  while (jugada != NULL && numeroTJugada(jugada->jugada) != numeroDeJugada){
    jugada = jugada->sig;
  }
  return jugada != NULL;
}

TJugada obtenerDeTPartida(TPartida partida, int numeroDeJugada){
  TPartida jugada = partida;
  while (jugada != NULL && numeroTJugada(jugada->jugada) != numeroDeJugada){
    jugada = jugada->sig;
  }
  return jugada->jugada;
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
  liberarTJugada(buscada->jugada);
  anterior->sig = buscada->sig;
  delete buscada;
}
