#include "../include/agenda.h"

struct rep_agenda {
    /************ Parte 5.1 ************/
    /*Escriba el código a continuación */
    TEvento eventos[MAX_EVENTOS];
    nat tope;
    /****** Fin de parte Parte 5.1 *****/
};

TAgenda crearTAgenda() {
    TAgenda nuevaAgenda = NULL;
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    nuevaAgenda = new rep_agenda;
    nuevaAgenda->tope = 0;
    /****** Fin de parte Parte 5.2 *****/
    return nuevaAgenda;
}

void agregarEnAgenda(TAgenda &agenda, TEvento evento) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    if (agenda->tope < MAX_EVENTOS) {
        nat indice = 0;
        while (indice < agenda->tope && compararTFechas(fechaTEvento(evento), fechaTEvento(agenda->eventos[indice])) == 1)
        {
            indice++;
        }
        for (nat i = agenda->tope; i > indice; i--)
        {
            agenda->eventos[i] = agenda->eventos[i-1];
        }
        agenda->eventos[indice] = evento;
        agenda->tope++;
    }
    /****** Fin de parte Parte 5.2 *****/
}

void liberarTAgenda(TAgenda &agenda) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope; i++)
    {
        liberarTEvento(agenda->eventos[i]);
    }
    delete agenda;
    agenda = NULL;
    /****** Fin de parte Parte 5.2 *****/
}

void imprimirTAgenda(TAgenda agenda) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    if (agenda->tope > 0)
    {
        for (nat i = 0; i < agenda->tope; i++)
        {
            imprimirTEvento(agenda->eventos[i]);
        }
    }
    /****** Fin de parte Parte 5.2 *****/
}

bool estaEnAgenda(TAgenda agenda, int id) {
    bool res = false;
    /************ Parte 5.4 ************/
    /*Escriba el código a continuación */
    nat indice = 0;
    while (indice < agenda->tope && idTEvento(agenda->eventos[indice]) != id)
    {
        indice++;
    }
    res = indice < agenda->tope;
    /****** Fin de parte Parte 5.4 *****/
    return res;
}

TEvento obtenerDeAgenda(TAgenda agenda, int id) {
    TEvento res = NULL;
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    nat indice = 0;
    while (indice < agenda->tope && idTEvento(agenda->eventos[indice]) != id)
    {
        indice++;
    }
    res = agenda->eventos[indice];
    /****** Fin de parte Parte 5.5 *****/
    return res;
}

void posponerEnAgenda(TAgenda &agenda, int id, nat n) {
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    nat indice = 0;
    while (idTEvento(agenda->eventos[indice]) != id)
    {
        indice++;
    }

    int int_n = n;
    posponerTEvento(agenda->eventos[indice], int_n);
    
    TEvento swap = NULL;
    while (indice < agenda->tope && indice + 1 < agenda->tope && compararTFechas(fechaTEvento(agenda->eventos[indice]), fechaTEvento(agenda->eventos[indice+1])) == 1)
    {
        indice++;
        swap = agenda->eventos[indice];
        agenda->eventos[indice] = agenda->eventos[indice-1];
        agenda->eventos[indice-1] = swap;   
    }
    /****** Fin de parte Parte 5.5 *****/
}

void imprimirEventosFecha(TAgenda agenda, TFecha fecha) {
    /************ Parte 5.7 ************/
    /*Escriba el código a continuación */
    nat indice = 0;
    while (indice < agenda->tope && compararTFechas(fechaTEvento(agenda->eventos[indice]), fecha) == -1)
    {
        indice++;
    }
    
    while (indice < agenda->tope && compararTFechas(fechaTEvento(agenda->eventos[indice]), fecha) == 0)
    {
        imprimirTEvento(agenda->eventos[indice]);
        indice++;
    }
    /****** Fin de parte Parte 5.7 *****/
}

bool hayEventosFecha(TAgenda agenda, TFecha fecha) {
    bool res = false;
    /************ Parte 5.7 ************/
    /*Escriba el código a continuación */
    /*La función debe ejecutar una versión */
    /*Iterativa del algoritmo de búsqueda  */
    /*binaria.                              */
    if (agenda->tope > 0){
        int minimo = 0, maximo = agenda->tope, indice;
        while (minimo <= maximo)
        {
            indice = (minimo + maximo)/2;
            if (compararTFechas(fechaTEvento(agenda->eventos[indice]), fecha) == 0){
                res = true;
                minimo = maximo + 1;
            } else if (compararTFechas(fechaTEvento(agenda->eventos[indice]), fecha) > 0) {
                maximo = indice - 1;
            } else {
                minimo = indice + 1;
            }
        }
    }
    /****** Fin de parte Parte 5.7 *****/
    return res;
}

void removerDeAgenda(TAgenda &agenda, int id) {
    /************ Parte 5.8 ************/
    /*Escriba el código a continuación */
    nat indice = 0;
    while (idTEvento(agenda->eventos[indice]) != id){
        indice++;
    }

    liberarTEvento(agenda->eventos[indice]);
    agenda->tope--;
    
    while (indice < agenda->tope){
        agenda->eventos[indice] = agenda->eventos[indice + 1];
        indice++;
    }
    /****** Fin de parte Parte 5.8 *****/
}
