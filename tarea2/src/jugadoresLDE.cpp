#include "../include/jugadoresLDE.h"

struct rep_nodo {
  TJugador jugador;
  TFecha fecha;
  nodo * proximo;
  nodo * previo;
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
  TNodo ubicacion = jugadores->primero, conector = NULL;
  if (ubicacion == NULL){
    jugadores->primero = new rep_nodo;
    jugadores->primero->jugador = jugador;
    jugadores->primero->fecha = fecha;
    jugadores->primero->proximo = NULL;
    jugadores->primero->previo = NULL;
    jugadores->ultimo = jugadores->primero;
  } else {
    while (ubicacion != NULL && compararTFechas(ubicacion->fecha, fecha) < 1){
      conector = ubicacion;
      ubicacion = ubicacion->proximo;
    }
    if (conector == NULL){
      conector= new rep_nodo;
      conector->jugador = jugador;
      conector->fecha = fecha;
      conector->previo = NULL;
      conector->proximo = ubicacion;
      ubicacion->previo = conector;
      jugadores->primero = conector;
    } else { 
      conector->proximo = new rep_nodo;
      conector->proxiom->jugador = jugador;
      conector->proximo->fecha = fecha;
      conector->proximo->previo = conector;
      conector->proximo->proximo = ubicacion;
      if (ubicacion == NULL;){
	jugadores->ultimo = conector->sig;
      } else {
	ubicacion->previo = conector->sig;
      }
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
  TNodo liberar = jugadores->primero;
  while (liberar != NULL){
    liberar = liberar->proximo;
    liberarTNodo(jugadores->primero);
    jugadores->primero = liberar;
  }
  delete jugadores;
  jugadores = NULL;
}

void imprimirMayorAMenorTJugadoresLDE(TJugadoresLDE jugadores){
  TNodo imprimir = jugadores->primero;
  while (imprimir != NULL){
    imprimirTJugador(imprimir);
    imprimir = imprimir->proximo;
  }
}

void imprimirMenorAMayorTJugadoresLDE(TJugadoresLDE jugadores){
  TNodo imprimir = jugadores->ultimo;
  while (imprimir != NULL){
    imprimirTJugador(imprimir);
    imprimir = imprimir->previo;
  }
}

nat cantidadTJugadoresLDE(TJugadoresLDE jugadores){
    return jugadores->cantidad;
}

void eliminarInicioTJugadoresLDE(TJugadoresLDE &jugadores){
  TNodo liberar = jugadores->primero;
  jugadores->primero = liberar->proximo;
  if (jugadores->primero != NULL){
    jugadores->primero->previo = NULL;
  } else {
    jugadores->ultimo = NULL;
  }
  jugadores->cantidad--;
}

void eliminarFinalTJugadoresLDE(TJugadoresLDE &jugadores){
  TNodo liberar = jugadores->ultimo;
  jugadores->ultimo = liberar->previo;
  if (jugadores->previo != NULL){
    jugadores->ultimo->proximo = NULL;
  } else {
    jugadores->primero = NULL;
  }
  jugadores->cantidad--;
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
  TJugadoresLDE encontrados = crearTJugadoresLDE;
  TNodo buscar = jugadores->primero;
  while (buscar != NULL && compararTFecha(buscar->fecha, fecha) != 0){
    buscar = buscar->proximo;
  }
  while (buscar != NULL && compararTFecha(buscar->fecha, fecha) == 0){
    insertarTJugadoresLDE(encontrados, copiarTJugador(buscar->jugador), copiarTFecha(buscar->fecha));
    buscar = buscar->proximo,
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
	insertarEnTJugadores(buscarEn2->jugadores, buscarEn2->fecha);
	if (buscarEn2 = buscarEn2->proximo == NULL){
	  caso = 1;
	}
	break;
      case 3:
	insertarEnTJugadores(buscarEn1->jugadores, buscarEn1->fecha);
	if (buscarEn1 = buscarEn1->proximo == NULL){
	  caso = 1;
	}
	break;
      case 6:
	comparacion = compararTFechas(buscarEn1->fecha, busacrEn2->fecha);
	if (comparacion == -1 || comparacion == 0 && idTJugador(buscarEn1->jugador) < idTJugador(buscarEn2->jugador)){
	  insertarEnTJugadores(buscarEn1->jugadores, buscarEn1->fecha);
	} else {
	  insertarEnTJugadores(buscarEn2->jugadores, buscarEn2->fecha);
	}
	if (buscarEn2 = buscarEn2->proximo == NULL){
	  caso /= 2;
	}
	if (buscarEn1 = buscarEn1->proximo == NULL){
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
}
