#include "../include/colaJugadoresABB.h"
#include "../include/jugadoresLDE.h"

struct arboles
{
  TJugadoresABB arbol;
  arboles * proximo;
};

typedef arboles * TArboles;

struct rep_colaJugadoresABB {
  TArboles primero;
  TArboles ultimo;
  nat cantidad;
};

TColaJugadoresABB crearTColaJugadoresABB() {
  TColaJugadoresABB c = new rep_colaJugadoresABB;
  c->cantidad = 0;
  c->primero = NULL;
  c->ultimo = NULL;
  return c;
}

void liberarTColaJugadoresABB(TColaJugadoresABB &c) {
  if (c != NULL)
  {
    TArboles aBorrar = NULL;
    while (c->primero != NULL)
    {
      aBorrar = c->primero;
      c->primero = aBorrar->proximo;
      delete aBorrar;
    }
    c->ultimo = NULL;
    delete c;
    c = NULL;
  }
}

nat cantidadEnTColaJugadoresABB(TColaJugadoresABB c) { 
  return c->cantidad;
 }

void encolarEnTColaJugadoresABB(TJugadoresABB t, TColaJugadoresABB &c) {
  if (c != NULL)
  {
    TArboles nuevo = new arboles;
    nuevo->arbol = t;
    nuevo->proximo = NULL;
    c->ultimo->proximo = nuevo;
    c->cantidad++;
  }
}

TJugadoresABB frenteDeTColaJugadoresABB(TColaJugadoresABB c) { 
  return c->primero->arbol;
}

void desencolarDeTColaJugadoresABB(TColaJugadoresABB &c) {
  TArboles aBorrar = c->primero;
  c->primero = c->primero->proximo;
  delete aBorrar;
  c->cantidad--;
}
