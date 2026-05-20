#ifndef JUEGOS_H
#define JUEGOS_H

#include "mapa.h"
#include "entidades.h"

const int ESTADO_JUGANDO = 1;
const int ESTADO_VICTORIA = 2;
const int ESTADO_DERROTA = 3;
const int ESTADO_SALIR = 4;

const char TECLA_ARRIBA = 'w';
const char TECLA_ABAJO = 's';
const char TECLA_IZQUIERDA = 'a';
const char TECLA_DERECHA = 'd';

const char TECLA_RECOGER = 'e';
const char TECLA_SOLTAR = 'q';
const char TECLA_SALIR = 'x';

const int OBJETO_LLAVE = 0;
const int OBJETO_TESORO = 1;

/*
    INICIO DEL JUEGO
*/

void mostrarTitulo();

void mostrarControles();

void iniciarDatosJuego(
    std::string* nombreJugador,
    char* simboloJugador,
    int* filaJugador,
    int* columnaJugador,
    int* vidasJugador,
    int* inventarioJugador,
    int* habitacionActual,
    std::string nombresObjetos[],
    char simbolosObjetos[],
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int* cantidadObjetos,
    std::string nombresEnemigos[],
    char simbolosEnemigos[],
    int filasEnemigos[],
    int columnasEnemigos[],
    int tiposEnemigos[],
    int enemigosActivos[],
    int* cantidadEnemigos
);

/*
    CICLO PRINCIPAL
*/

void ejecutarJuego();

void jugarTurno(
    char mapaBase[][MAPA_COLUMNAS],
    std::string* nombreJugador,
    char* simboloJugador,
    int* filaJugador,
    int* columnaJugador,
    int* vidasJugador,
    int* inventarioJugador,
    int* habitacionActual,
    int* estadoJuego,
    std::string nombresObjetos[],
    char simbolosObjetos[],
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos,
    std::string nombresEnemigos[],
    char simbolosEnemigos[],
    int filasEnemigos[],
    int columnasEnemigos[],
    int tiposEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
);

/*
    ENTRADA DEL JUGADOR
*/

char leerTecla();

void procesarTecla(
    char tecla,
    char mapaBase[][MAPA_COLUMNAS],
    int* filaJugador,
    int* columnaJugador,
    int* inventarioJugador,
    int* habitacionActual,
    int* estadoJuego,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos
);

void intentarMoverJugador(
    char mapaBase[][MAPA_COLUMNAS],
    int* filaJugador,
    int* columnaJugador,
    int* habitacionActual,
    int cambioFila,
    int cambioColumna
);

/*
    OBJETOS E INVENTARIO
*/

void revisarRecogerObjeto(
    int filaJugador,
    int columnaJugador,
    int* inventarioJugador,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos
);

void revisarSoltarObjeto(
    int filaJugador,
    int columnaJugador,
    int* inventarioJugador,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[]
);

/*
    ENEMIGOS
*/

void actualizarEnemigos(
    int filaJugador,
    int columnaJugador,
    int filasEnemigos[],
    int columnasEnemigos[],
    int tiposEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
);

void revisarChoqueConEnemigos(
    int* filaJugador,
    int* columnaJugador,
    int* habitacionActual,
    int* vidasJugador,
    int* inventarioJugador,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int filasEnemigos[],
    int columnasEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
);

/*
    VICTORIA Y DERROTA
*/

int revisarVictoria(
    int habitacionActual,
    int inventarioJugador
);

int revisarDerrota(
    int vidasJugador
);

void actualizarEstadoJuego(
    int* estadoJuego,
    int habitacionActual,
    int inventarioJugador,
    int vidasJugador
);

void mostrarMensajeFinal(
    int estadoJuego
);

/*
    INFORMACION EN PANTALLA
*/

void mostrarEstadoJugador(
    std::string nombreJugador,
    int vidasJugador,
    int habitacionActual,
    int inventarioJugador,
    std::string nombresObjetos[]
);

void limpiarPantalla();

void pausarJuego();

#endif
