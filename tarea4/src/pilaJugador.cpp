#include "../include/pilaJugador.h"

struct elementos
{
  TJugador jugador;
  elementos * proximo;
};

typedef elementos * TElementos;

struct rep_pilaJugador {
  nat cantidad;
  TElementos pila;
};

TPilaJugador crearTPilaJugador() {
  TPilaJugador p = new rep_pilaJugador;
  p->cantidad = 0;
  p->pila = NULL;
  return p;
}

void liberarTPilaJugador(TPilaJugador &p) {
  if (p != NULL)
  {
    TElementos aBorrar = NULL;
    while (p->cantidad > 0)
    {
      liberarTJugador(p->pila->jugador);
      aBorrar = p->pila;
      p->pila = p->pila->proximo;
      delete aBorrar;
      p->cantidad--;
    }
    delete p;
    p = NULL;
  }
}

nat cantidadEnTPilaJugador(TPilaJugador p) { 
  return p->cantidad;
}

void apilarEnTPilaJugador(TPilaJugador &p, TJugador jugador) {
  TElementos elemento = new elementos;
  elemento->proximo = p->pila;
  elemento->jugador = copiarTJugador(jugador);
  p->pila = elemento;
}

TJugador cimaDeTPilaJugador(TPilaJugador p) { 
  return p->pila->jugador;
}

void desapilarDeTPilaJugador(TPilaJugador &p) {
  if (p != NULL && p->cantidad > 0)
  {
    TElementos aBorrar = p->pila;
    p->pila = aBorrar->proximo;
    liberarTJugador(aBorrar->jugador);
    delete aBorrar;
    p->cantidad--;
  }
}
