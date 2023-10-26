#include "../include/tablaJugadores.h"

struct rep_elemento
{
    TJugador jugador;
    TFecha fecha;
    rep_elemento* proximo;    
};

typedef rep_elemento * TElemento;

struct rep_tablaJugadores {
    TElemento* columna;
    nat elementos;
    nat columnas;
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
    TTablaJugadores tabla = new rep_tablaJugadores;
    tabla->columna = new TElemento[max];
    nat n_max = max;
    for (nat i = 0; i < n_max; i++)
    {
        tabla->columna[i] = NULL;
    }
    tabla->elementos = 0;
    tabla->columnas = max;
    return tabla;
}

void liberarTTablaJugadores(TTablaJugadores &tabla){
    // si hay elementos buscarlos y borrarlos
    nat indice = 0;
    while (tabla->elementos > 0 && indice < tabla->columnas)
    {
        // si la columna no es NULL liberar los elemntos de la columna
        while (tabla->columna[indice] != NULL)
        {
            liberarTJugador(tabla->columna[indice]->jugador);
            liberarTFecha(tabla->columna[indice]->fecha);
            TElemento proximo = tabla->columna[indice]->proximo;
            delete tabla->columna[indice];
            tabla->columna[indice] = proximo;
            tabla->elementos--;
        }
        indice++;
    }
    // una vez sin elementos borramos el conjunto de columnas y la tabla
    delete[] tabla->columna;
    delete tabla;
    tabla = NULL;
}

void insertarJugadorEnTabla(TTablaJugadores &tabla, TJugador jugador, TFecha fecha){
    // ubicar la columna donde va y en que parte de la columna
    TElemento ubicarlo = tabla->columna[funcionDeDispersion(nombreTJugador(jugador))%tabla->columnas];
    // ver que no sea NULL la columna donde estamos
    // agregarlo por orden de fecha, mayor a menor
    if (ubicarlo == NULL)
    {
        ubicarlo = new rep_elemento;
        ubicarlo->jugador = jugador;
        ubicarlo->fecha = fecha;
        ubicarlo->proximo = NULL;
        tabla->columna[funcionDeDispersion(nombreTJugador(jugador))%tabla->columnas] = ubicarlo;
    } else // hay que ver donde va ubicado
    {
        TElemento previo = NULL, buscar = ubicarlo, nuevo = new rep_elemento;
        nuevo->jugador = jugador;
        nuevo->fecha = fecha;
        while (buscar != NULL && compararTFechas(fecha, buscar->fecha) < 0)
        {
            previo = buscar;
            buscar = buscar->proximo;
        }
        nuevo->proximo = buscar;
        if (previo == NULL) // entonces va al incio
        {
            tabla->columna[funcionDeDispersion(nombreTJugador(jugador))%tabla->columnas] = nuevo;
        } else {
            previo->proximo = nuevo;
        }
    }
    tabla->elementos++;
}

void eliminarJugadorDeTTablaJugadores(TTablaJugadores &tabla, const char nombre[100]){
    // ubicar la columna donde esta y en que parte de la columna
    TElemento ubicarlo = tabla->columna[funcionDeDispersion(nombre)%tabla->columnas];
    // buscarlo dentro de la columna
    TElemento previo = NULL;
    while (strcmp(nombreTJugador(ubicarlo->jugador), nombre) != 0)
    {
        previo = ubicarlo;
        ubicarlo = ubicarlo->proximo;
    }
    // una vez encontrado lo borramos
    if (previo == NULL) // entonces era el primero, hay que señalar en nuevo inicio de la columna
    {
        tabla->columna[funcionDeDispersion(nombre)%tabla->columnas] = ubicarlo->proximo;
    } else
    {
        previo->proximo = ubicarlo->proximo;
    }
    // tras arreglar los punteros lo borramos
    liberarTJugador(ubicarlo->jugador);
    liberarTFecha(ubicarlo->fecha);
    delete ubicarlo;
}

bool perteneceATTablaJugadores(TTablaJugadores tabla, const char nombre[100]){
    // ubicar la columna donde estaria y en que parte de la columna
    TElemento ubicarlo = tabla->columna[funcionDeDispersion(nombre)%tabla->columnas];
    while (ubicarlo != NULL && strcmp(nombreTJugador(ubicarlo->jugador), nombre) != 0)
    {
        ubicarlo = ubicarlo->proximo;
    }
    return ubicarlo != NULL;
}

TJugador obtenerJugadorDeTTablaJugadores(TTablaJugadores tabla, const char nombre[100]){
    // ubicar la columna donde esta y en que parte de la columna
    TElemento ubicarlo = tabla->columna[funcionDeDispersion(nombre)%tabla->columnas];
    while (strcmp(nombreTJugador(ubicarlo->jugador), nombre) != 0)
    {
        ubicarlo = ubicarlo->proximo;
    }
    // devolverlo
    return ubicarlo->jugador;
}

void imprimirTTablaJugadores(TTablaJugadores tabla){
    nat indice = 0;
    nat aImprimir = tabla->elementos;
    while (aImprimir > 0 && indice < tabla->columnas)
    {
        // si la columna no es NULL imprimir los elemntos de la columna
        TElemento imprimir = tabla->columna[indice];
        while (imprimir != NULL)
        {
            imprimirTJugador(imprimir->jugador);
            imprimirTFecha(imprimir->fecha);
            imprimir = imprimir->proximo;
            aImprimir--;
        }
        indice++;
    }
}