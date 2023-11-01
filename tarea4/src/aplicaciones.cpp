#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadJugador.h"

void listarEnOrden(TTablaJugadores t, char** nombres, nat n){
    // creamos la cola
    nat max;
    if (n > MAX_ID){
        max = n;
    } else {
        max = MAX_ID;
    }
    TColaDePrioridadJugador cola = crearCP(max);
    // insertar una copia en la cola
    for (nat i = 0; i < n; i++){
        // obtener el jugador y agregarlo
        if (perteneceATTablaJugadores(t, nombres[i])){
            insertarEnCP(copiarTJugador(obtenerJugadorDeTTablaJugadores(t, nombres[i])), cola);
        }
    }
    // imprimimos los jugadores por orden de prioridad
    while (!estaVaciaCP(cola)){
        imprimirTJugador(prioritario(cola));
        eliminarPrioritario(cola);
    }
    // liberamos la cola
    liberarCP(cola);
}