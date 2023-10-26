/*
  Módulo de definición de 'TTablaJugadores'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef TABLAJUGADORES_H
#define TABLAJUGADORES_H

#include "jugadoresLDE.h"
#include "utils.h"

// Definición de tipo TablaJugadores como un puntero a rep_tablaJugadores
typedef struct rep_tablaJugadores *TTablaJugadores;

// Función para crear una nueva Tabla vacía de jugadores, en la que se estima que se insertarán max jugadores.
// La función es Theta(max) peor caso.
TTablaJugadores crearTTablaJugadores(int max);

// Función para insertar un jugador (y fecha) en la tabla de jugadores.
// Para calcular la posición en la que se debe insertar al jugador en
// la tabla de dispersión abierta se debe utilizar la función brindada funcionDeDispersion
// (la función está declarada al comienzo de tablaJugadores.cpp.
// Esta función recibe el nombre de un jugador y devuelve un natural calculado como
// la suma de los valores ascii de los caracteres que conforman el nombre.
// El jugador debe ser insertado en la posición p = funcionDeDispersion(nombreJugador) % tamanio,
// donde % es la operación de módulo y tamanio es el tamaño con el que se creó la tabla de dispersión.
// La función asocia al jugador (y su fecha) con el nombre del jugador.
// PRE: !perteneceATTablaJugadores(tabla, nombreTJugador(jugador))
// La función es Theta(1) en caso promedio
void insertarJugadorEnTabla(TTablaJugadores &tabla, TJugador jugador, TFecha fecha);

// Función para eliminar al jugador de nombre "nombre" de la TTablaJugadores "tabla".
// La función libera la memoria del jugador eliminado. 
// La función es Theta(m) promedio, donde m es la cantidad de jugadas en la partida del jugador con nombre "nombre".
// PRE: perteneceATTablaJugadores(tabla, nombre)
void eliminarJugadorDeTTablaJugadores(TTablaJugadores &tabla, const char nombre[100]);

// Función para verificar si en una TTablaJugadores "tabla" existe un jugador con nombre "nombre".
// Devuelve true si existe, false en caso contrario.
// La función es Theta(1) promedio.
bool perteneceATTablaJugadores(TTablaJugadores tabla, const char nombre[100]);

// Función para obtener el jugador con nombre "nombre" de la TTablaJugadores "tabla".
// La función es Theta(1) promedio.
// PRE: perteneceATTablaJugadores(tabla, nombre)
TJugador obtenerJugadorDeTTablaJugadores(TTablaJugadores tabla, const char nombre[100]);

// Función para liberar la memoria asignada a una TTablaJugadores (tabla) de jugadores
// La función es O(n*m + max) peor caso, donde n es la cantidad de jugadores en la tabla y m es la cantidad de jugadas de la partida con mas jugadas entre todos los jugadores de la tabla.
void liberarTTablaJugadores(TTablaJugadores &tabla);

// Función para imprimir todos los jugadores de la TTablaJugadores "tabla" .
// Imprime cada jugador de la tabla, en orden creciente de posiciones asociadas en la tabla.
// En caso de que haya más de un jugador en la misma posición, se deben imprimir por fecha, de mayor a menor.
// La función es Theta(n*m + max) peor caso, donde n es la cantidad de jugadores en la tabla y m es la cantidad de eventos de la agenda con mas eventos entre todos los jugadores de la tabla.
void imprimirTTablaJugadores(TTablaJugadores tabla);

#endif  // TABLAJUGADORES_H
