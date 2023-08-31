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
  if (jugadores->primero == NULL){
    // la lista esta vacia
    nuevo->proximo = NULL;
    nuevo->previo = NULL;
    jugadores->primero = nuevo;
    jugadores->ultimo = nuevo;
  } else {
    TNodo ubicacion = jugadores->primero->proximo;
    // hay almenos un nodo
    if (compararTFechas(jugadores->primero->fecha, fecha) < 0){
      // va al inicio
      nuevo->proximo = jugadores->primero;
      nuevo->previo = NULL;
      jugadores->primero = nuevo;
    } else if (compararTFechas(jugadores->ultimo->fecha, fecha) > 0) {
      // va al final
      nuevo->proximo = NULL;
      nuevo->previo = jugadores->ultimo;
      jugadores->ultimo = nuevo;
    } else {
      // entonces va entre dos nodos
      while (compararTFechas(ubicacion->fecha, fecha) < 1){
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
    imprimir = imprimir->proximo;
  }
}

void imprimirMenorAMayorTJugadoresLDE(TJugadoresLDE jugadores){
  TNodo imprimir = jugadores->ultimo;
  while (imprimir != NULL){
    imprimirTJugador(imprimir->jugador);
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
  TJugadoresLDE mezcla = crearTJugadoresLDE();
  TNodo buscarEn1 = jugadores1->primero, buscarEn2 = jugadores2->primero;
  nat caso = 1;
  // 1 AMBOS NULL
  // 2 BUSCAR EN 1 ES NULL
  // 3 BUSCAR EN 2 ES NULL
  // 6 NIGUNO ES NULL
  if (buscarEn1 != NULL){
    caso*=3;
  }
  if (buscarEn2 != NULL){
    caso*=2;
  }
  int comparacion;
  while (caso != 1){
    switch ( caso )
      {
      case 2:
	insertarTJugadoresLDE(mezcla, buscarEn2->jugador, buscarEn2->fecha);
	if ((buscarEn2 = buscarEn2->proximo) == NULL){
	  caso = 1;
	}
	break;
      case 3:
	insertarTJugadoresLDE(mezcla, buscarEn1->jugador, buscarEn1->fecha);
	if ((buscarEn1 = buscarEn1->proximo) == NULL){
	  caso = 1;
	}
	break;
      case 6:
	comparacion = compararTFechas(buscarEn1->fecha, buscarEn2->fecha);
	if (comparacion == -1 || (comparacion == 0 && idTJugador(buscarEn1->jugador) < idTJugador(buscarEn2->jugador))){
	  insertarTJugadoresLDE(mezcla, buscarEn1->jugador, buscarEn1->fecha);
	} else {
	  insertarTJugadoresLDE(mezcla, buscarEn2->jugador, buscarEn2->fecha);
	}
	if ((buscarEn2 = buscarEn2->proximo) == NULL){
	  caso /= 2;
	}
	if ((buscarEn1 = buscarEn1->proximo) == NULL){
	  caso /= 3;
	}
	break;
      default:
	break;
      }
  }
  delete jugadores1;
  delete jugadores2;
  jugadores1 = NULL;
  jugadores2 = NULL;
  return mezcla;
}
