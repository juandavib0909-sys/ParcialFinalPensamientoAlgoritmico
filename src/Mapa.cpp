#include "../include/mapa.h"
#include <iostream>

/*
    MAPA BASICO
*/

void limpiarMapa(
    char mapa[][MAPA_COLUMNAS]
)
{
    int fila;
    int columna;

    for (fila = 0; fila < MAPA_FILAS; fila = fila + 1)
    {
        for (columna = 0; columna < MAPA_COLUMNAS; columna = columna + 1)
        {
            mapa[fila][columna] = PISO;
        }
    }
}

void crearBordes(
    char mapa[][MAPA_COLUMNAS]
)
{
    int fila;
    int columna;

    for (columna = 0; columna < MAPA_COLUMNAS; columna = columna + 1)
    {
        mapa[0][columna] = PARED;
        mapa[MAPA_FILAS - 1][columna] = PARED;
    }

    for (fila = 0; fila < MAPA_FILAS; fila = fila + 1)
    {
        mapa[fila][0] = PARED;
        mapa[fila][MAPA_COLUMNAS - 1] = PARED;
    }
}

void crearPuertas(
    char mapa[][MAPA_COLUMNAS],
    int habitacionActual
)
{
    int filaHabitacion;
    int columnaHabitacion;
    int puertaFila;
    int puertaColumna;

    filaHabitacion = habitacionActual / 3;
    columnaHabitacion = habitacionActual % 3;

    puertaFila = MAPA_FILAS / 2;
    puertaColumna = MAPA_COLUMNAS / 2;

    if (filaHabitacion > 0)
    {
        mapa[0][puertaColumna] = PUERTA;
    }

    if (filaHabitacion < 1)
    {
        mapa[MAPA_FILAS - 1][puertaColumna] = PUERTA;
    }

    if (columnaHabitacion > 0)
    {
        mapa[puertaFila][0] = PUERTA;
    }

    if (columnaHabitacion < 2)
    {
        mapa[puertaFila][MAPA_COLUMNAS - 1] = PUERTA;
    }
}

void cargarHabitacion(
    char mapa[][MAPA_COLUMNAS],
    int habitacionActual
)
{
    int fila;
    int columna;

    limpiarMapa(mapa);
    crearBordes(mapa);

    if (habitacionActual == 0)
    {
        for (columna = 6; columna <= 22; columna = columna + 1)
        {
            mapa[3][columna] = PARED;
        }

        mapa[3][14] = PISO;
        mapa[3][15] = PISO;
    }

    if (habitacionActual == 1)
    {
        for (fila = 3; fila <= 8; fila = fila + 1)
        {
            mapa[fila][10] = PARED;
        }

        mapa[5][10] = PISO;
    }

    if (habitacionActual == 2)
    {
        for (columna = 5; columna <= 24; columna = columna + 1)
        {
            mapa[8][columna] = PARED;
        }

        mapa[8][18] = PISO;
        mapa[8][19] = PISO;
    }

    if (habitacionActual == 3)
    {
        for (fila = 2; fila <= 9; fila = fila + 1)
        {
            mapa[fila][18] = PARED;
        }

        mapa[6][18] = PISO;
    }

    if (habitacionActual == 4)
    {
        for (columna = 7; columna <= 21; columna = columna + 1)
        {
            mapa[4][columna] = PARED;
        }

        for (columna = 7; columna <= 21; columna = columna + 1)
        {
            mapa[7][columna] = PARED;
        }

        mapa[4][14] = PISO;
        mapa[7][14] = PISO;
    }

    if (habitacionActual == 5)
    {
        for (fila = 2; fila <= 9; fila = fila + 1)
        {
            mapa[fila][8] = PARED;
            mapa[fila][21] = PARED;
        }

        mapa[5][8] = PISO;
        mapa[6][21] = PISO;
    }

    crearPuertas(mapa, habitacionActual);
}

/*
    COLISIONES
*/

int esPared(
    char mapa[][MAPA_COLUMNAS],
    int fila,
    int columna
)
{
    if (posicionDentroDelMapa(fila, columna) == 0)
    {
        return 1;
    }

    if (mapa[fila][columna] == PARED)
    {
        return 1;
    }

    return 0;
}

int esPuerta(
    char mapa[][MAPA_COLUMNAS],
    int fila,
    int columna
)
{
    if (posicionDentroDelMapa(fila, columna) == 0)
    {
        return 0;
    }

    if (mapa[fila][columna] == PUERTA)
    {
        return 1;
    }

    return 0;
}

int posicionDentroDelMapa(
    int fila,
    int columna
)
{
    if (fila < 0)
    {
        return 0;
    }

    if (fila >= MAPA_FILAS)
    {
        return 0;
    }

    if (columna < 0)
    {
        return 0;
    }

    if (columna >= MAPA_COLUMNAS)
    {
        return 0;
    }

    return 1;
}

int jugadorPuedeMoverse(
    char mapa[][MAPA_COLUMNAS],
    int nuevaFila,
    int nuevaColumna
)
{
    if (posicionDentroDelMapa(nuevaFila, nuevaColumna) == 0)
    {
        return 0;
    }

    if (esPared(mapa, nuevaFila, nuevaColumna) == 1)
    {
        return 0;
    }

    return 1;
}

/*
    HABITACIONES
*/

int obtenerNuevaHabitacion(
    int habitacionActual,
    int direccion
)
{
    int filaHabitacion;
    int columnaHabitacion;

    if (habitacionActual < 0 || habitacionActual >= TOTAL_HABITACIONES)
    {
        return habitacionActual;
    }

    filaHabitacion = habitacionActual / 3;
    columnaHabitacion = habitacionActual % 3;

    if (direccion == DIRECCION_ARRIBA)
    {
        if (filaHabitacion > 0)
        {
            return habitacionActual - 3;
        }
    }

    if (direccion == DIRECCION_ABAJO)
    {
        if (filaHabitacion < 1)
        {
            return habitacionActual + 3;
        }
    }

    if (direccion == DIRECCION_IZQUIERDA)
    {
        if (columnaHabitacion > 0)
        {
            return habitacionActual - 1;
        }
    }

    if (direccion == DIRECCION_DERECHA)
    {
        if (columnaHabitacion < 2)
        {
            return habitacionActual + 1;
        }
    }

    return habitacionActual;
}

int obtenerDireccionPuerta(
    int filaJugador,
    int columnaJugador
)
{
    int centroFila;
    int centroColumna;

    centroFila = MAPA_FILAS / 2;
    centroColumna = MAPA_COLUMNAS / 2;

    if (filaJugador == 0 && columnaJugador == centroColumna)
    {
        return DIRECCION_ARRIBA;
    }

    if (filaJugador == MAPA_FILAS - 1 && columnaJugador == centroColumna)
    {
        return DIRECCION_ABAJO;
    }

    if (filaJugador == centroFila && columnaJugador == 0)
    {
        return DIRECCION_IZQUIERDA;
    }

    if (filaJugador == centroFila && columnaJugador == MAPA_COLUMNAS - 1)
    {
        return DIRECCION_DERECHA;
    }

    return 0;
}

void cambiarHabitacion(
    int* habitacionActual,
    int* filaJugador,
    int* columnaJugador,
    int direccion
)
{
    int nuevaHabitacion;

    if (habitacionActual == 0 || filaJugador == 0 || columnaJugador == 0)
    {
        return;
    }

    nuevaHabitacion = obtenerNuevaHabitacion(*habitacionActual, direccion);

    if (nuevaHabitacion != *habitacionActual)
    {
        *habitacionActual = nuevaHabitacion;
        ubicarJugadorAlEntrar(filaJugador, columnaJugador, direccion);
    }
}

void ubicarJugadorAlEntrar(
    int* filaJugador,
    int* columnaJugador,
    int direccion
)
{
    int centroFila;
    int centroColumna;

    if (filaJugador == 0 || columnaJugador == 0)
    {
        return;
    }

    centroFila = MAPA_FILAS / 2;
    centroColumna = MAPA_COLUMNAS / 2;

    if (direccion == DIRECCION_ARRIBA)
    {
        *filaJugador = MAPA_FILAS - 2;
        *columnaJugador = centroColumna;
    }

    if (direccion == DIRECCION_ABAJO)
    {
        *filaJugador = 1;
        *columnaJugador = centroColumna;
    }

    if (direccion == DIRECCION_IZQUIERDA)
    {
        *filaJugador = centroFila;
        *columnaJugador = MAPA_COLUMNAS - 2;
    }

    if (direccion == DIRECCION_DERECHA)
    {
        *filaJugador = centroFila;
        *columnaJugador = 1;
    }
}

/*
    MOSTRAR MAPA
*/

void copiarMapaTemporal(
    char mapaBase[][MAPA_COLUMNAS],
    char mapaTemporal[][MAPA_COLUMNAS]
)
{
    int fila;
    int columna;

    for (fila = 0; fila < MAPA_FILAS; fila = fila + 1)
    {
        for (columna = 0; columna < MAPA_COLUMNAS; columna = columna + 1)
        {
            mapaTemporal[fila][columna] = mapaBase[fila][columna];
        }
    }
}

void ponerJugadorEnMapa(
    char mapaTemporal[][MAPA_COLUMNAS],
    int filaJugador,
    int columnaJugador,
    char simboloJugador
)
{
    if (posicionDentroDelMapa(filaJugador, columnaJugador) == 1)
    {
        mapaTemporal[filaJugador][columnaJugador] = simboloJugador;
    }
}

void ponerObjetosEnMapa(
    char mapaTemporal[][MAPA_COLUMNAS],
    char simbolosObjetos[],
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos
)
{
    int i;
    int limite;
    int fila;
    int columna;

    limite = cantidadObjetos;

    if (limite > MAX_OBJETOS)
    {
        limite = MAX_OBJETOS;
    }

    if (limite < 0)
    {
        return;
    }

    for (i = 0; i < limite; i = i + 1)
    {
        if (objetosActivos[i] == 1)
        {
            fila = filasObjetos[i];
            columna = columnasObjetos[i];

            if (posicionDentroDelMapa(fila, columna) == 1)
            {
                if (mapaTemporal[fila][columna] != PARED)
                {
                    mapaTemporal[fila][columna] = simbolosObjetos[i];
                }
            }
        }
    }
}

void ponerEnemigosEnMapa(
    char mapaTemporal[][MAPA_COLUMNAS],
    char simbolosEnemigos[],
    int filasEnemigos[],
    int columnasEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
)
{
    int i;
    int limite;
    int fila;
    int columna;

    limite = cantidadEnemigos;

    if (limite > MAX_ENEMIGOS)
    {
        limite = MAX_ENEMIGOS;
    }

    if (limite < 0)
    {
        return;
    }

    for (i = 0; i < limite; i = i + 1)
    {
        if (enemigosActivos[i] == 1)
        {
            fila = filasEnemigos[i];
            columna = columnasEnemigos[i];

            if (posicionDentroDelMapa(fila, columna) == 1)
            {
                if (mapaTemporal[fila][columna] != PARED)
                {
                    mapaTemporal[fila][columna] = simbolosEnemigos[i];
                }
            }
        }
    }
}

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
)
{
    char mapaTemporal[MAPA_FILAS][MAPA_COLUMNAS];
    int fila;
    int columna;

    copiarMapaTemporal(mapaBase, mapaTemporal);

    ponerObjetosEnMapa(
        mapaTemporal,
        simbolosObjetos,
        filasObjetos,
        columnasObjetos,
        objetosActivos,
        cantidadObjetos
    );

    ponerEnemigosEnMapa(
        mapaTemporal,
        simbolosEnemigos,
        filasEnemigos,
        columnasEnemigos,
        enemigosActivos,
        cantidadEnemigos
    );

    ponerJugadorEnMapa(
        mapaTemporal,
        filaJugador,
        columnaJugador,
        simboloJugador
    );

    std::cout << "Habitacion: " << habitacionActual + 1 << " / " << TOTAL_HABITACIONES << std::endl;

    for (fila = 0; fila < MAPA_FILAS; fila = fila + 1)
    {
        for (columna = 0; columna < MAPA_COLUMNAS; columna = columna + 1)
        {
            std::cout << mapaTemporal[fila][columna];
        }

        std::cout << std::endl;
    }
}
