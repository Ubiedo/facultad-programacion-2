#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadJugador.h"

void listarEnOrden(TTablaJugadores t, char** nombres, nat n){
    // creamos la cola
    TColaDePrioridadJugador cola = crearCP(n);
    // insertar una copia en la cola
    for (nat i = 1; i <= n; i++){
        // obtener el jugador y agregarlo
        insertarEnCP(copiarTJugador(obtenerJugadorDeTTablaJugadores(t, nombres[i])), cola);
    }
    // imprimimos los jugadores por orden de prioridad
    while (!estaVaciaCP(cola)){
        imprimirTJugador(prioritario(cola));
        eliminarPrioritario(cola);
    }
    // liberamos la cola
    liberarCP(cola);
}