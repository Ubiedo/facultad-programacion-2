#include "../include/conjuntoIds.h"

struct rep_conjuntoIds{
  bool * elemento;
  nat cardinal;
  nat maximo;
};


TConjuntoIds crearTConjuntoIds(nat cantMax){
  TConjuntoIds conjunto = new rep_conjuntoIds;
  conjunto->elemento = new bool[cantMax];
  for (nat i = 0; i < cantMax; i++){
    conjunto->elemento[i] = false;
  }
  conjunto->maximo = cantMax;
  conjunto->cardinal = 0;
  return conjunto;
};


bool esVacioTConjuntoIds(TConjuntoIds c){
  return c->cardinal == 0;
};


void insertarTConjuntoIds(nat id, TConjuntoIds &c){
  if (id > 0 && id <= c->maximo){
    c->elemento[id%c->maximo] = true;
    c->cardinal++;
  }
}; 

void borrarTConjuntoIds(nat id, TConjuntoIds &c){
  c->elemento[id%c->maximo] = false;
  c->cardinal--;
};

bool perteneceTConjuntoIds(nat id, TConjuntoIds c){
    return c->elemento[id%c->maximo];
};


nat cardinalTConjuntoIds(TConjuntoIds c){
    return c->cardinal;
};

nat cantMaxTConjuntoIds(TConjuntoIds c){
    return c->maximo;
};

void imprimirTConjuntoIds(TConjuntoIds c){
  nat id = 1, impresos = 0;
  while (id <= c->maximo && impresos != c->cardinal){
    if (c->elemento[id%c->maximo]){
      printf("%d ", id);
      impresos++;
    }
    id++;
  }
};

void liberarTConjuntoIds(TConjuntoIds &c){
  if (c != NULL){
    delete c->elemento;
    c->elemento = NULL;
    delete c;
    c = NULL;
  }
};




TConjuntoIds unionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
  TConjuntoIds mezcla = crearTConjuntoIds(c1->maximo);
  nat restantes = c1->cardinal + c2->cardinal, id = 1;
  // bucle para hayar la union
  while (restantes > 0){
    if (c1->elemento[id%c1->maximo] && c2->elemento[id%c1->maximo]){
      insertarTConjuntoIds(id, mezcla);
      restantes-=2;
    } else if (c1->elemento[id%c1->maximo] || c2->elemento[id%c1->maximo]){
      insertarTConjuntoIds(id, mezcla);
      restantes--;
    }
    id++;
  }
  // devuelvo la union de los conjuntos
  return mezcla;
};

TConjuntoIds interseccionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
  TConjuntoIds interseccion = crearTConjuntoIds(c1->maximo), c = c1, x = c2;
  nat restantes = c1->cardinal, id = 1;
  if (c2->cardinal < restantes){
    restantes = c2->cardinal;
    c = c2;
    x = c1;
  }
  // bucle para hayar la interseccion
  while (restantes > 0){
    if (c->elemento[id%c1->maximo]){
      if (x->elemento[id%c1->maximo]){
	insertarTConjuntoIds(id, interseccion);
      }
      restantes--;
    }
    id++;
  }
  // devulevo la interseccion de los conjuntos
  return interseccion;
};

TConjuntoIds diferenciaTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
  TConjuntoIds diferencia = crearTConjuntoIds(c1->maximo);
  nat restantes = c1->cardinal, id = 1;
  // bucle para hayar la diferencia
  while (restantes > 0){
    if (c1->elemento[id%c1->maximo]){
      if (!(c2->elemento[id%c1->maximo])){
	insertarTConjuntoIds(id, diferencia);
      }
      restantes--;
    }
    id++;
  }
  // devuelvo la diferencia de los conjuntos
  return diferencia;
};
