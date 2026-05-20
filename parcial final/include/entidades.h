#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <string>

const int MAX_ENEMIGOS = 10;
const int MAX_OBJETOS = 10;

const int INVENTARIO_VACIO = -1;

const int ENEMIGO_LENTO = 1;
const int ENEMIGO_DIRECTO = 2;

/*
    JUGADOR
*/

void iniciarJugador(
    std::string* nombreJugador,
    char* simboloJugador,
    int* filaJugador,
    int* columnaJugador,
    int* vidasJugador,
    int* inventarioJugador
);

void moverJugador(
    int* filaJugador,
    int* columnaJugador,
    int cambioFila,
    int cambioColumna
);

void quitarVidaJugador(
    int* vidasJugador
);

int jugadorSigueVivo(
    int vidasJugador
);

/*
    OBJETOS
*/

void iniciarObjeto(
    std::string nombresObjetos[],
    char simbolosObjetos[],
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int indice,
    std::string nombre,
    char simbolo,
    int fila,
    int columna
);

int buscarObjetoEnPosicion(
    int filaJugador,
    int columnaJugador,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos
);

void recogerObjeto(
    int* inventarioJugador,
    int indiceObjeto,
    int objetosActivos[]
);

void soltarObjeto(
    int* inventarioJugador,
    int filaJugador,
    int columnaJugador,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[]
);

int jugadorTieneObjeto(
    int inventarioJugador
);

/*
    ENEMIGOS
*/

void iniciarEnemigo(
    std::string nombresEnemigos[],
    char simbolosEnemigos[],
    int filasEnemigos[],
    int columnasEnemigos[],
    int tiposEnemigos[],
    int enemigosActivos[],
    int indice,
    std::string nombre,
    char simbolo,
    int tipo,
    int fila,
    int columna
);

void moverEnemigoLento(
    int* filaEnemigo,
    int* columnaEnemigo,
    int filaJugador,
    int columnaJugador
);

void moverEnemigoDirecto(
    int* filaEnemigo,
    int* columnaEnemigo,
    int filaJugador,
    int columnaJugador
);

void moverEnemigo(
    int* filaEnemigo,
    int* columnaEnemigo,
    int tipoEnemigo,
    int filaJugador,
    int columnaJugador
);

int buscarEnemigoEnPosicion(
    int filaJugador,
    int columnaJugador,
    int filasEnemigos[],
    int columnasEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
);

int enemigoTocaJugador(
    int filaEnemigo,
    int columnaEnemigo,
    int filaJugador,
    int columnaJugador
);

/*
    POSICIONES
*/

int mismaPosicion(
    int primeraFila,
    int primeraColumna,
    int segundaFila,
    int segundaColumna
);

#endif