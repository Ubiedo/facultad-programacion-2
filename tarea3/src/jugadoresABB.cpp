#include "../include/jugadoresABB.h"
#include "../include/colaJugadoresABB.h"
#include "../include/pilaJugador.h"

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
  if (jugadoresABB->derecha == NULL){
    return jugadoresABB->jugador;
  }
  return maxIdJugador(jugadoresABB->derecha);
}

void removerTJugadoresABB(TJugadoresABB &jugadoresABB, nat id) {
  if (idTJugador(jugadoresABB->jugador) < id){
    removerTJugadoresABB(jugadoresABB->derecha, id);
  } else if (idTJugador(jugadoresABB->jugador) > id){
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
      TJugador max = copiarTJugador(maxIdJugador(jugadoresABB->izquierda));
      jugadoresABB->jugador = max;
      // eliminar el nodo donde estaba el maxIdJugador
      removerTJugadoresABB(jugadoresABB->izquierda, idTJugador(jugadoresABB->jugador));
    }
  }
}

bool estaTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
  if (jugadoresABB != NULL){
    if (idTJugador(jugadoresABB->jugador) < id){
      return estaTJugadoresABB(jugadoresABB->derecha, id);
    } else if (idTJugador(jugadoresABB->jugador) > id){
      return estaTJugadoresABB(jugadoresABB->izquierda, id);
    }
  }
  return jugadoresABB != NULL;
}

TJugador obtenerDeTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
  if (idTJugador(jugadoresABB->jugador) < id){
    return obtenerDeTJugadoresABB(jugadoresABB->derecha, id);
  } else if (idTJugador(jugadoresABB->jugador) > id){
    return obtenerDeTJugadoresABB(jugadoresABB->izquierda, id);
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

// no esta hecho en theta(n), CUIDADO!!!!
bool esPerfectoTJugadoresABB(TJugadoresABB jugadoresABB) {
  if (jugadoresABB != NULL && (jugadoresABB->izquierda != NULL || jugadoresABB->derecha != NULL)){
    // estos son los casos a analizar el comportamiento de los hijos
    if (jugadoresABB->izquierda != NULL && jugadoresABB->derecha != NULL){
      // tiene ambos hijos
      // un arbol es perfecto si sus subarboles son perfectos y tienen la misma altura
      // el siguiente codigo funciona, recorre muchas veces los nodos. mejorar este caso..
      return ((esPerfectoTJugadoresABB(jugadoresABB->izquierda) && esPerfectoTJugadoresABB(jugadoresABB->derecha)) && (alturaTJugadoresABB(jugadoresABB->izquierda) == alturaTJugadoresABB(jugadoresABB->derecha)));
    } else {
      // ya que hay hijos de un lado pero no del otro
      return false;
    }
  }
  return true;
}

TJugadoresABB mayoresTJugadoresABB(TJugadoresABB jugadoresABB, nat edad) {
  if (jugadoresABB != NULL){
    // ver si cumple criterio de la edad
    if (edadTJugador(jugadoresABB->jugador) > edad){
      TJugadoresABB mayor = new rep_jugadoresABB;
      mayor->jugador = copiarTJugador(jugadoresABB->jugador);
      mayor->izquierda = mayoresTJugadoresABB(jugadoresABB->izquierda, edad);
      mayor->derecha = mayoresTJugadoresABB(jugadoresABB->derecha, edad);
      return mayor;
    } else {
      // buscamos nueva raiz el maxId Izquierda que cumpla el criterio de la edad
      TJugadoresABB mayor = mayoresTJugadoresABB(jugadoresABB->izquierda, edad);
      if (mayor == NULL){
        // si es NULL entonces ninguno del hijo izquierdo cumple condicion de la edad, nos quedamos con los de la derecha nomas
        mayor = mayoresTJugadoresABB(jugadoresABB->derecha, edad);
      } else {
        // hay que modificar la raiz al maxId del arbol izquierdo, y revisar si asi esta bien o hay que modificar algo para que quede como se supone en los test
	if (mayor->derecha != NULL){
	  TJugadoresABB raiz = new rep_jugadoresABB;
	  raiz->jugador = copiarTJugador(maxIdJugador(mayor));
	  removerTJugadoresABB(mayor, idTJugador(raiz->jugador));
	  raiz->izquierda = mayor;
	  mayor = raiz;
	}
	mayor->derecha = mayoresTJugadoresABB(jugadoresABB->derecha, edad);
      }
      return mayor;
    }
  }
  return NULL;
}


///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void descenderNivel(TColaJugadoresABB &nivel){
  nat cantidad = cantidadEnTColaJugadoresABB(nivel);
  TJugadoresABB frente = NULL;
  while(cantidad > 0){
    frente = frenteDeTColaJugadoresABB(nivel);
    if (frente->izquierda != NULL){
      encolarEnTColaJugadoresABB(frente->izquierda, nivel);
    }
    if(frente->derecha != NULL){
      encolarEnTColaJugadoresABB(frente->derecha, nivel);
    }
    desencolarDeTColaJugadoresABB(nivel);
    cantidad--;
  }
}

nat amplitudTJugadoresABB(TJugadoresABB t) {
  if (t != NULL){
    TColaJugadoresABB nivel = crearTColaJugadoresABB();
    encolarEnTColaJugadoresABB(t, nivel);
    nat maximo = 1, actual = 1;
    // ir por cada nivel y hayar su amplitud
    while (actual > 0){
      descenderNivel(nivel);
      actual = cantidadEnTColaJugadoresABB(nivel);
      if (actual > maximo){
	maximo = actual;
      }
    }
    // liberar la memoria de nivel
    liberarTColaJugadoresABB(nivel);
    // devolver el maximo encontrado
    return maximo;
  }
  return 0;
}

void apilar(TColaJugadoresABB &nivel, TPilaJugador &apilado){
  nat cantidad = cantidadEnTColaJugadoresABB(nivel);
  TJugadoresABB frente = NULL;
  while(cantidad > 0){
    frente = frenteDeTColaJugadoresABB(nivel);
    if (frente->izquierda != NULL){
      encolarEnTColaJugadoresABB(frente->izquierda, nivel);
    }
    if(frente->derecha != NULL){
      encolarEnTColaJugadoresABB(frente->derecha, nivel);
    }
    apilarEnTPilaJugador(apilado, frente->jugador);
    desencolarDeTColaJugadoresABB(nivel);
    cantidad--;
  }
}

TPilaJugador invertir(TPilaJugador &apilado){
  TPilaJugador invertido = crearTPilaJugador();
  while (cantidadEnTPilaJugador(apilado) > 0){
    apilarEnTPilaJugador(invertido, cimaDeTPilaJugador(apilado));
    desapilarDeTPilaJugador(apilado);
  }
  liberarTPilaJugador(apilado);
  return invertido;
}

TPilaJugador serializarTJugadoresABB(TJugadoresABB t) {
  TPilaJugador apilado = crearTPilaJugador();
  if (t != NULL){
    TColaJugadoresABB nivel = crearTColaJugadoresABB();
    encolarEnTColaJugadoresABB(t, nivel);
    while (cantidadEnTColaJugadoresABB(nivel) > 0){
      apilar(nivel, apilado);
    }
    // liberamos la memoria del nivel
    liberarTColaJugadoresABB(nivel);
    // devolvemos la pila invertida para que quede en el orden correcto
    return invertir(apilado);
  }
  return apilado;
}

void adoptar(TColaJugadoresABB &padres, TPilaJugador &p, bool nexo){
  // hayamos al padre y lo sacamos de la lista de padres a la espera de hijos
  TJugadoresABB padre = frenteDeTColaJugadoresABB(padres);
  // creamos el nodo para el hijo
  TJugadoresABB hijo = new rep_jugadoresABB;
  hijo->jugador = copiarTJugador(cimaDeTPilaJugador(p));
  hijo->izquierda = NULL;
  hijo->derecha = NULL;
  if (nexo){
    padre->izquierda = hijo;
  } else {
    padre->derecha = hijo;
  }
  // agregamos al hijo a la lista de posibles padres
  encolarEnTColaJugadoresABB(hijo, padres);
  desapilarDeTPilaJugador(p); // lo sacamos de la pila de hijos sin padre
}

TJugadoresABB deserializarTJugadoresABB(TPilaJugador &p) {
  TJugadoresABB raiz = NULL;
  if (cantidadEnTPilaJugador(p) > 0){
    // como hay un elemento al menos, creamos la raiz
    raiz = new rep_jugadoresABB;
    raiz->jugador = copiarTJugador(cimaDeTPilaJugador(p));
    raiz->izquierda = NULL;
    raiz->derecha = NULL;
    desapilarDeTPilaJugador(p); // lo sacamos de la pila de hijos ya que es la raiz
    // creamos una cola para saber a quien le hay que agregar los hijos
    TColaJugadoresABB padres = crearTColaJugadoresABB();
    encolarEnTColaJugadoresABB(raiz, padres);
    // asignamos cada dupla de hijos a los padres
    while (cantidadEnTPilaJugador(p) > 1){ // entonces quedan ambos hijos que asignar
      adoptar(padres, p, true);
      adoptar(padres, p, false);
      // sacamos al padre de la lista de padres sin hijos
      desencolarDeTColaJugadoresABB(padres);
    }
    // si queda un hijo va con el padre del frente
    if(cantidadEnTPilaJugador(p) > 0){
      adoptar(padres, p, true);
    }
    // liberamos la fila de padres y la pila de hijos vacia
    liberarTPilaJugador(p);
    liberarTColaJugadoresABB(padres);
  }
  return raiz;
}


///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
