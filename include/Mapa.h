#ifndef MAPA_H
#define MAPA_H

#include "entidades.h"

const int MAPA_FILAS = 12;
const int MAPA_COLUMNAS = 30;

const int TOTAL_HABITACIONES = 6;

const char PARED = '#';
const char PISO = '.';
const char PUERTA = '+';
const char VACIO = ' ';

const int DIRECCION_ARRIBA = 1;
const int DIRECCION_ABAJO = 2;
const int DIRECCION_IZQUIERDA = 3;
const int DIRECCION_DERECHA = 4;

/*
    MAPA BASICO
*/

void limpiarMapa(
    char mapa[][MAPA_COLUMNAS]
);

void crearBordes(
    char mapa[][MAPA_COLUMNAS]
);

void crearPuertas(
    char mapa[][MAPA_COLUMNAS],
    int habitacionActual
);

void cargarHabitacion(
    char mapa[][MAPA_COLUMNAS],
    int habitacionActual
);

/*
    COLISIONES
*/

int esPared(
    char mapa[][MAPA_COLUMNAS],
    int fila,
    int columna
);

int esPuerta(
    char mapa[][MAPA_COLUMNAS],
    int fila,
    int columna
);

int posicionDentroDelMapa(
    int fila,
    int columna
);

int jugadorPuedeMoverse(
    char mapa[][MAPA_COLUMNAS],
    int nuevaFila,
    int nuevaColumna
);

/*
    HABITACIONES
*/

int obtenerNuevaHabitacion(
    int habitacionActual,
    int direccion
);

int obtenerDireccionPuerta(
    int filaJugador,
    int columnaJugador
);

void cambiarHabitacion(
    int* habitacionActual,
    int* filaJugador,
    int* columnaJugador,
    int direccion
);

void ubicarJugadorAlEntrar(
    int* filaJugador,
    int* columnaJugador,
    int direccion
);

/*
    MOSTRAR MAPA
*/

void copiarMapaTemporal(
    char mapaBase[][MAPA_COLUMNAS],
    char mapaTemporal[][MAPA_COLUMNAS]
);

void ponerJugadorEnMapa(
    char mapaTemporal[][MAPA_COLUMNAS],
    int filaJugador,
    int columnaJugador,
    char simboloJugador
);

void ponerObjetosEnMapa(
    char mapaTemporal[][MAPA_COLUMNAS],
    char simbolosObjetos[],
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos
);

void ponerEnemigosEnMapa(
    char mapaTemporal[][MAPA_COLUMNAS],
    char simbolosEnemigos[],
    int filasEnemigos[],
    int columnasEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
);

void mostrarMapa(
    char mapaBase[][MAPA_COLUMNAS],
    int habitacionActual,
    int filaJugador,
    int columnaJugador,
    char simboloJugador,
    char simbolosObjetos[],
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos,
    char simbolosEnemigos[],
    int filasEnemigos[],
    int columnasEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
);

#endif
