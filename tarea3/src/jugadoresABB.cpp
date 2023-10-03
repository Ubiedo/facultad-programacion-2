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

nat amplitudNivel(TColaJugadoresABB &nivel){
    nat actual = cantidadEnTColaJugadoresABB(nivel);
    while (actual > 0)
    {
        TJugadoresABB frente = frenteDeTColaJugadoresABB(nivel);
        desencolarDeTColaJugadoresABB(nivel);
        encolarEnTColaJugadoresABB(frente->derecha, nivel);
        encolarEnTColaJugadoresABB(frente->izquierda, nivel);
    }
    return cantidadEnTColaJugadoresABB(nivel);
}

nat amplitudTJugadoresABB(TJugadoresABB t) {
    if (t != NULL)
    {
        // recorrido por niveles
        TColaJugadoresABB nivel = crearTColaJugadoresABB();
        encolarEnTColaJugadoresABB(t, nivel);
        nat actual = 1, max = 1; // guarda la amplitud actual del nivel y la amplitud maxima hasta el momento
        // bucle para hayar la cantidad de nodos en cada nivel
        while (actual = amplitudNivel(nivel) > 0) // termina cuando ya no hayan nodos en el nivel
        {
            if (actual > max)
            {
                max = actual;
            }
        }
        liberarTColaJugadoresABB(nivel); // libero la memoria del nivel
        // devolver el maximo
        return max;
    }
    return 0; // ya que no hay nodos
}

void niveles(TColaJugadoresABB &nivel, TColaJugadoresABB &arbol){
    nat actual = cantidadEnTColaJugadoresABB(nivel);
    while (actual > 0)
    {
        TJugadoresABB frente = frenteDeTColaJugadoresABB(nivel);
        desencolarDeTColaJugadoresABB(nivel);
        encolarEnTColaJugadoresABB(frente->derecha, nivel);
        encolarEnTColaJugadoresABB(frente->izquierda, nivel);
        encolarEnTColaJugadoresABB(frente, arbol);
    }
}

TPilaJugador serializarTJugadoresABB(TJugadoresABB t) {
    if (t != NULL)
    {
        // recorrido por niveles y agregado a la pila, no comparte memoria
        TPilaJugador apilado = crearTPilaJugador();
        TColaJugadoresABB nivel = crearTColaJugadoresABB(), arbol = crearTColaJugadoresABB();
        encolarEnTColaJugadoresABB(t, nivel);
        apilarEnTPilaJugador(apilado, copiarTJugador(t->jugador));
        nat nodos = 1;
        // recorrido por niveles y agregar a la pila
        while (nodos = cantidadEnTColaJugadoresABB(nivel) > 0) // termina cuando ya no hayan nodos en el nivel
        {
            niveles(nivel, arbol);
        }
        // devuelvo la pila
        return apilado;
    }    
    return crearTPilaJugador(); // pila vacia o NULL?
}

TJugadoresABB deserializarTJugadoresABB(TPilaJugador &p) {
    if (cantidadEnTPilaJugador(p) > 0)
    {
        TJugadoresABB raiz = NULL;
        // van en mod 2

        // devuelvo la raiz del arbol
        return raiz;
    }
    return NULL;
}


///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
