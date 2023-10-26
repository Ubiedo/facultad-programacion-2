#include "../include/tablaJugadores.h"

struct columna
{
    TJugador jugador;
    TJugador proximo;    
};

struct rep_tablaJugadores {
    columna** tabla;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaJugadores crearTTablaJugadores(int max){
    return NULL;
}

void liberarTTablaJugadores(TTablaJugadores &tabla){
}


void insertarJugadorEnTabla(TTablaJugadores &tabla, TJugador jugador, TFecha fecha){
}


void eliminarJugadorDeTTablaJugadores(TTablaJugadores &tabla, const char nombre[100]){
}

bool perteneceATTablaJugadores(TTablaJugadores tabla, const char nombre[100]){
    return false;
}

TJugador obtenerJugadorDeTTablaJugadores(TTablaJugadores tabla, const char nombre[100]){
    return NULL;
}

void imprimirTTablaJugadores(TTablaJugadores tabla){
}