#include "../include/aplicaciones.h"

TPilaJugador menoresQueElResto(TJugadoresLDE lista) {
  TPilaJugador apilado = crearTPilaJugador();
  if (cantidadTJugadoresLDE(lista) > 0){
    TJugador apilar = obtenerInicioDeTJugadoresLDE(lista);
    apilarEnTPilaJugador(apilado, apilar);
    eliminarInicioTJugadoresLDE(lista);
    while (cantidadTJugadoresLDE(lista) > 0){ // mientras es > 0 hay elementos
      apilar = obtenerInicioDeTJugadoresLDE(lista);
      // comparo con los que estan
      while (cantidadEnTPilaJugador(apilado) > 0 && edadTJugador(apilar) <= edadTJugador(cimaDeTPilaJugador(apilado))){
	// hay que sacar a los de la pila que no son menores que el nuevo
	desapilarDeTPilaJugador(apilado);
      }
      // lo agrego tras haber sacado a los que no cumplian lo pedido
      apilarEnTPilaJugador(apilado, apilar);
      eliminarInicioTJugadoresLDE(lista);
    }
  }
  // retornamos la pila
  return apilado;
}

bool sumaPares(nat k, TConjuntoIds c){
  if (k >= 2*(cantMaxTConjuntoIds(c)) || k <= 0 || cardinalTConjuntoIds(c) < 2){
    return false;
  }
  // entonces es posible
  nat i = 1;
  while (i < cantMaxTConjuntoIds(c)){ // optimizar la condicion del while
    if (perteneceTConjuntoIds(i, c) && perteneceTConjuntoIds(k-i, c) && i != (k-i)){
      return true;
    }
    i++;
  }
  return false;
}
