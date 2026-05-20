#include "../include/entidades.h"

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
)
{
    if (nombreJugador != 0)
    {
        *nombreJugador = "Jugador";
    }

    if (simboloJugador != 0)
    {
        *simboloJugador = '@';
    }

    if (filaJugador != 0)
    {
        *filaJugador = 5;
    }

    if (columnaJugador != 0)
    {
        *columnaJugador = 5;
    }

    if (vidasJugador != 0)
    {
        *vidasJugador = 3;
    }

    if (inventarioJugador != 0)
    {
        *inventarioJugador = INVENTARIO_VACIO;
    }
}

void moverJugador(
    int* filaJugador,
    int* columnaJugador,
    int cambioFila,
    int cambioColumna
)
{
    if (filaJugador != 0)
    {
        *filaJugador = *filaJugador + cambioFila;
    }

    if (columnaJugador != 0)
    {
        *columnaJugador = *columnaJugador + cambioColumna;
    }
}

void quitarVidaJugador(
    int* vidasJugador
)
{
    if (vidasJugador != 0)
    {
        if (*vidasJugador > 0)
        {
            *vidasJugador = *vidasJugador - 1;
        }
    }
}

int jugadorSigueVivo(
    int vidasJugador
)
{
    if (vidasJugador > 0)
    {
        return 1;
    }

    return 0;
}

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
)
{
    if (indice < 0 || indice >= MAX_OBJETOS)
    {
        return;
    }

    nombresObjetos[indice] = nombre;
    simbolosObjetos[indice] = simbolo;
    filasObjetos[indice] = fila;
    columnasObjetos[indice] = columna;
    objetosActivos[indice] = 1;
}

int buscarObjetoEnPosicion(
    int filaJugador,
    int columnaJugador,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[],
    int cantidadObjetos
)
{
    int limite;
    int i;

    limite = cantidadObjetos;

    if (limite > MAX_OBJETOS)
    {
        limite = MAX_OBJETOS;
    }

    if (limite < 0)
    {
        return INVENTARIO_VACIO;
    }

    for (i = 0; i < limite; i = i + 1)
    {
        if (objetosActivos[i] == 1)
        {
            if (mismaPosicion(filaJugador, columnaJugador, filasObjetos[i], columnasObjetos[i]) == 1)
            {
                return i;
            }
        }
    }

    return INVENTARIO_VACIO;
}

void recogerObjeto(
    int* inventarioJugador,
    int indiceObjeto,
    int objetosActivos[]
)
{
    if (inventarioJugador == 0)
    {
        return;
    }

    if (indiceObjeto < 0 || indiceObjeto >= MAX_OBJETOS)
    {
        return;
    }

    if (*inventarioJugador != INVENTARIO_VACIO)
    {
        return;
    }

    if (objetosActivos[indiceObjeto] == 0)
    {
        return;
    }

    *inventarioJugador = indiceObjeto;
    objetosActivos[indiceObjeto] = 0;
}

void soltarObjeto(
    int* inventarioJugador,
    int filaJugador,
    int columnaJugador,
    int filasObjetos[],
    int columnasObjetos[],
    int objetosActivos[]
)
{
    int indiceObjeto;

    if (inventarioJugador == 0)
    {
        return;
    }

    if (*inventarioJugador == INVENTARIO_VACIO)
    {
        return;
    }

    indiceObjeto = *inventarioJugador;

    if (indiceObjeto < 0 || indiceObjeto >= MAX_OBJETOS)
    {
        *inventarioJugador = INVENTARIO_VACIO;
        return;
    }

    filasObjetos[indiceObjeto] = filaJugador;
    columnasObjetos[indiceObjeto] = columnaJugador;
    objetosActivos[indiceObjeto] = 1;

    *inventarioJugador = INVENTARIO_VACIO;
}

int jugadorTieneObjeto(
    int inventarioJugador
)
{
    if (inventarioJugador != INVENTARIO_VACIO)
    {
        return 1;
    }

    return 0;
}

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
)
{
    if (indice < 0 || indice >= MAX_ENEMIGOS)
    {
        return;
    }

    nombresEnemigos[indice] = nombre;
    simbolosEnemigos[indice] = simbolo;
    filasEnemigos[indice] = fila;
    columnasEnemigos[indice] = columna;
    tiposEnemigos[indice] = tipo;
    enemigosActivos[indice] = 1;
}

void moverEnemigoLento(
    int* filaEnemigo,
    int* columnaEnemigo,
    int filaJugador,
    int columnaJugador
)
{
    int diferenciaFila;
    int diferenciaColumna;

    if (filaEnemigo == 0 || columnaEnemigo == 0)
    {
        return;
    }

    diferenciaFila = filaJugador - *filaEnemigo;
    diferenciaColumna = columnaJugador - *columnaEnemigo;

    if (diferenciaFila < 0)
    {
        diferenciaFila = diferenciaFila * -1;
    }

    if (diferenciaColumna < 0)
    {
        diferenciaColumna = diferenciaColumna * -1;
    }

    if (diferenciaFila >= diferenciaColumna)
    {
        if (*filaEnemigo < filaJugador)
        {
            *filaEnemigo = *filaEnemigo + 1;
        }
        else
        {
            if (*filaEnemigo > filaJugador)
            {
                *filaEnemigo = *filaEnemigo - 1;
            }
        }
    }
    else
    {
        if (*columnaEnemigo < columnaJugador)
        {
            *columnaEnemigo = *columnaEnemigo + 1;
        }
        else
        {
            if (*columnaEnemigo > columnaJugador)
            {
                *columnaEnemigo = *columnaEnemigo - 1;
            }
        }
    }
}

void moverEnemigoDirecto(
    int* filaEnemigo,
    int* columnaEnemigo,
    int filaJugador,
    int columnaJugador
)
{
    if (filaEnemigo == 0 || columnaEnemigo == 0)
    {
        return;
    }

    if (*filaEnemigo < filaJugador)
    {
        *filaEnemigo = *filaEnemigo + 1;
    }
    else
    {
        if (*filaEnemigo > filaJugador)
        {
            *filaEnemigo = *filaEnemigo - 1;
        }
    }

    if (*columnaEnemigo < columnaJugador)
    {
        *columnaEnemigo = *columnaEnemigo + 1;
    }
    else
    {
        if (*columnaEnemigo > columnaJugador)
        {
            *columnaEnemigo = *columnaEnemigo - 1;
        }
    }
}

void moverEnemigo(
    int* filaEnemigo,
    int* columnaEnemigo,
    int tipoEnemigo,
    int filaJugador,
    int columnaJugador
)
{
    if (tipoEnemigo == ENEMIGO_LENTO)
    {
        moverEnemigoLento(filaEnemigo, columnaEnemigo, filaJugador, columnaJugador);
    }
    else
    {
        if (tipoEnemigo == ENEMIGO_DIRECTO)
        {
            moverEnemigoDirecto(filaEnemigo, columnaEnemigo, filaJugador, columnaJugador);
        }
        else
        {
            moverEnemigoLento(filaEnemigo, columnaEnemigo, filaJugador, columnaJugador);
        }
    }
}

int buscarEnemigoEnPosicion(
    int filaJugador,
    int columnaJugador,
    int filasEnemigos[],
    int columnasEnemigos[],
    int enemigosActivos[],
    int cantidadEnemigos
)
{
    int limite;
    int i;

    limite = cantidadEnemigos;

    if (limite > MAX_ENEMIGOS)
    {
        limite = MAX_ENEMIGOS;
    }

    if (limite < 0)
    {
        return -1;
    }

    for (i = 0; i < limite; i = i + 1)
    {
        if (enemigosActivos[i] == 1)
        {
            if (mismaPosicion(filaJugador, columnaJugador, filasEnemigos[i], columnasEnemigos[i]) == 1)
            {
                return i;
            }
        }
    }

    return -1;
}

int enemigoTocaJugador(
    int filaEnemigo,
    int columnaEnemigo,
    int filaJugador,
    int columnaJugador
)
{
    if (mismaPosicion(filaEnemigo, columnaEnemigo, filaJugador, columnaJugador) == 1)
    {
        return 1;
    }

    return 0;
}

/*
    POSICIONES
*/

int mismaPosicion(
    int primeraFila,
    int primeraColumna,
    int segundaFila,
    int segundaColumna
)
{
    if (primeraFila == segundaFila && primeraColumna == segundaColumna)
    {
        return 1;
    }

    return 0;
}