#include "../include/jugadoresLDE.h"

struct rep_nodo {
  TJugador jugador;
  TFecha fecha;
  rep_nodo * proximo;
  rep_nodo * previo;
};

typedef struct rep_nodo * TNodo;

struct rep_jugadoresLDE {
  TNodo primero;
  TNodo ultimo;
  nat cantidad;
};

TJugadoresLDE crearTJugadoresLDE(){
  TJugadoresLDE jugadores = new rep_jugadoresLDE;
  jugadores->primero = NULL;
  jugadores->ultimo = NULL;
  jugadores->cantidad = 0;
  return jugadores;
}

void insertarTJugadoresLDE(TJugadoresLDE &jugadores, TJugador &jugador, TFecha &fecha){
  TNodo nuevo = new rep_nodo;
  nuevo->jugador = jugador;
  nuevo->fecha = fecha;
  nuevo->proximo = NULL;
  nuevo->previo = NULL;
  if (jugadores->primero == NULL){
    // la lista esta vacia
    jugadores->primero = nuevo;
    jugadores->ultimo = nuevo;
  } else {
    // hay almenos un nodo
    if (compararTFechas(jugadores->primero->fecha, fecha) < 1){
      // va al inicio
      nuevo->proximo = jugadores->primero;
      nuevo->proximo->previo = nuevo;
      jugadores->primero = nuevo;
    } else if (compararTFechas(jugadores->ultimo->fecha, fecha) > 0) {
      // va al final
      nuevo->previo = jugadores->ultimo;
      nuevo->previo->proximo = nuevo;
      jugadores->ultimo = nuevo;
    } else {
      TNodo ubicacion = jugadores->primero->proximo;
      // entonces va entre dos nodos
      while (compararTFechas(ubicacion->fecha, fecha) > 0){
	ubicacion = ubicacion->proximo;
      }
      nuevo->proximo = ubicacion->proximo;
      ubicacion->proximo = nuevo;
      nuevo->previo = ubicacion;
      nuevo->proximo->previo = nuevo;
    }
  }
  jugadores->cantidad++;
}

void liberarTNodo(TNodo &nodo){
  liberarTJugador(nodo->jugador);
  liberarTFecha(nodo->fecha);
  nodo->proximo = NULL;
  nodo->previo = NULL;
  delete nodo;
  nodo = NULL;
}

void liberarTJugadoresLDE(TJugadoresLDE &jugadoresLDE){
  TNodo liberar = jugadoresLDE->primero;
  while (liberar != NULL){
    liberar = liberar->proximo;
    liberarTNodo(jugadoresLDE->primero);
    jugadoresLDE->primero = liberar;
  }
  delete jugadoresLDE;
  jugadoresLDE = NULL;
}

void imprimirMayorAMenorTJugadoresLDE(TJugadoresLDE jugadores){
  TNodo imprimir = jugadores->primero;
  while (imprimir != NULL){
    imprimirTJugador(imprimir->jugador);
    imprimirTFecha(imprimir->fecha);
    imprimir = imprimir->proximo;
  }
}

void imprimirMenorAMayorTJugadoresLDE(TJugadoresLDE jugadores){
  TNodo imprimir = jugadores->ultimo;
  while (imprimir != NULL){
    imprimirTJugador(imprimir->jugador);
    imprimirTFecha(imprimir->fecha);
    imprimir = imprimir->previo;
  }
}

nat cantidadTJugadoresLDE(TJugadoresLDE jugadores){
    return jugadores->cantidad;
}

void eliminarInicioTJugadoresLDE(TJugadoresLDE &jugadores){
  TNodo liberar = jugadores->primero;
  jugadores->primero = liberar->proximo;
  if (liberar->proximo != NULL){
    jugadores->primero->previo = NULL;
  } else {
    jugadores->ultimo = NULL;
  }
  jugadores->cantidad--;
  liberarTNodo(liberar);
}

void eliminarFinalTJugadoresLDE(TJugadoresLDE &jugadores){
  TNodo liberar = jugadores->ultimo;
  jugadores->ultimo = liberar->previo;
  if (liberar->previo != NULL){
    jugadores->ultimo->proximo = NULL;
  } else {
    jugadores->primero = NULL;
  }
  jugadores->cantidad--;
  liberarTNodo(liberar);
}

bool estaEnTJugadoresLDE(TJugadoresLDE jugadores, nat id){ 
  TNodo buscar = jugadores->primero;
  while (buscar != NULL && idTJugador(buscar->jugador) != id){
    buscar = buscar->proximo;
  }
  return buscar != NULL;
}

TJugador obtenerTJugadorDeTJugadoresLDE(TJugadoresLDE jugadores, nat id){
  TNodo buscar = jugadores->primero;
  while (idTJugador(buscar->jugador) != id){
    buscar = buscar->proximo;
  }
  return buscar->jugador;
}

TFecha obtenerTFechaDeTJugadoresLDE(TJugadoresLDE jugadores, nat id){
  TNodo buscar = jugadores->primero;
  while (idTJugador(buscar->jugador) != id){
    buscar = buscar->proximo;
  }
  return buscar->fecha;
}

TJugadoresLDE obtenerSegunTFecha(TJugadoresLDE jugadores, TFecha fecha){
  TJugadoresLDE encontrados = crearTJugadoresLDE();
  TNodo buscar = jugadores->primero;
  while (buscar != NULL && compararTFechas(buscar->fecha, fecha) != 0){
    buscar = buscar->proximo;
  }
  while (buscar != NULL && compararTFechas(buscar->fecha, fecha) == 0){
    TJugador jugadorCopiado = copiarTJugador(buscar->jugador);
    TFecha fechaCopiada = copiarTFecha(buscar->fecha);
    insertarTJugadoresLDE(encontrados, jugadorCopiado, fechaCopiada);
    buscar = buscar->proximo;
  }
  return encontrados;
}

TJugadoresLDE unirTJugadoresLDE(TJugadoresLDE &jugadores1, TJugadoresLDE &jugadores2){
  TJugadoresLDE junta = crearTJugadoresLDE();
  if (jugadores1 == NULL || jugadores1->primero == NULL){
    if (jugadores2 != NULL && jugadores2->primero != NULL){
      junta->primero = jugadores2->primero;
      junta->ultimo = jugadores2->ultimo;
      junta->cantidad = jugadores2->cantidad;
    }
  } else if (jugadores2 == NULL || jugadores2->primero == NULL){
    if (jugadores1 != NULL && jugadores1->primero != NULL){
      junta->primero = jugadores1->primero;
      junta->ultimo = jugadores1->ultimo;
      junta->cantidad = jugadores1->cantidad;
    }
  } else {
    // ninguno es NULL, entonces hay que recorrer ambos y re hacer los vinculos
    TNodo buscarEn1 = jugadores1->primero, buscarEn2 = jugadores2->primero;
    // fijamos el primero para ponerlo en mezcla->primero
    if (compararTFechas(buscarEn1->fecha, buscarEn2->fecha) < 1){
      junta->primero = buscarEn2;
      buscarEn2 = buscarEn2->proximo;
    } else {
      junta->primero = buscarEn1;
      buscarEn1 = buscarEn1->proximo;
    }
    TNodo juntar = junta->primero;
    while (buscarEn1 != NULL || buscarEn2 != NULL){
      if (buscarEn1 != NULL && buscarEn2 != NULL){
	if (compararTFechas(buscarEn1->fecha, buscarEn2->fecha) < 1){
	  juntar->proximo = buscarEn2;
	  buscarEn2->previo = juntar;
	  buscarEn2 = buscarEn2->proximo;
	} else {
	  juntar->proximo = buscarEn1;
	  buscarEn1->previo = juntar;
	  buscarEn1 = buscarEn1->proximo;
	}
      } else if (buscarEn1 != NULL){
	juntar->proximo = buscarEn1;
	buscarEn1->previo = juntar;
	buscarEn1 = buscarEn1->proximo;
      } else {
	juntar->proximo = buscarEn2;
	buscarEn2->previo = juntar;
	buscarEn2 = buscarEn2->proximo;
      }
    }
    junta->ultimo = juntar;
    junta->cantidad = jugadores1->cantidad + jugadores2->cantidad;
  }
  if (jugadores1 != NULL){
    delete jugadores1;
    jugadores1 = NULL;
  }
  if (jugadores2 != NULL){
    delete jugadores2;
    jugadores2 = NULL;
  }
  return junta;
}
