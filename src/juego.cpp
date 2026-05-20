#include "../include/juego.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif
int habitacionesObjetos[MAX_OBJETOS];
int habitacionesEnemigos[MAX_ENEMIGOS];

int habitacionTurnoJuego = 0;
char mapaTurnoEnemigos[MAPA_FILAS][MAPA_COLUMNAS];

int contadorEnemigos = 0;
int pantallaPreparada = 0;

/*
    FUNCIONES PEQUENAS PARA QUE EL JUEGO SE SIENTA MAS FLUIDO
*/

void esperarUnMomento()
{
#ifdef _WIN32
    Sleep(90);
#else
    usleep(90000);
#endif
}

int debeMoverEnemigos()
{
    contadorEnemigos = contadorEnemigos + 1;

    if (contadorEnemigos >= 4)
    {
        contadorEnemigos = 0;
        return 1;
    }

    return 0;
}

/*
    INICIO DEL JUEGO
*/

void mostrarTitulo()
{
    std::cout << "          FLIPANTES MAZMORRAS DE JUAN Y JUAN C++         " << std::endl;
}

void mostrarControles()
{
    std::cout << "WASD mover | E recoger | Q soltar | X salir" << std::endl;
}

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
)
{
    int i;

    iniciarJugador(
        nombreJugador,
        simboloJugador,
        filaJugador,
        columnaJugador,
        vidasJugador,
        inventarioJugador
    );

    if (habitacionActual != 0)
    {
        *habitacionActual = 0;
    }

    for (i = 0; i < MAX_OBJETOS; i = i + 1)
    {
        nombresObjetos[i] = "";
        simbolosObjetos[i] = ' ';
        filasObjetos[i] = 0;
        columnasObjetos[i] = 0;
        objetosActivos[i] = 0;
        habitacionesObjetos[i] = 0;
    }

    for (i = 0; i < MAX_ENEMIGOS; i = i + 1)
    {
        nombresEnemigos[i] = "";
        simbolosEnemigos[i] = ' ';
        filasEnemigos[i] = 0;
        columnasEnemigos[i] = 0;
        tiposEnemigos[i] = ENEMIGO_LENTO;
        enemigosActivos[i] = 0;
        habitacionesEnemigos[i] = 0;
    }

    iniciarObjeto(
        nombresObjetos,
        simbolosObjetos,
        filasObjetos,
        columnasObjetos,
        objetosActivos,
        OBJETO_LLAVE,
        "Llave",
        'L',
        2,
        6
    );

    habitacionesObjetos[OBJETO_LLAVE] = 1;

    iniciarObjeto(
        nombresObjetos,
        simbolosObjetos,
        filasObjetos,
        columnasObjetos,
        objetosActivos,
        OBJETO_TESORO,
        "Tesoro",
        'T',
        9,
        24
    );

    habitacionesObjetos[OBJETO_TESORO] = 5;

    if (cantidadObjetos != 0)
    {
        *cantidadObjetos = 2;
    }

    iniciarEnemigo(
        nombresEnemigos,
        simbolosEnemigos,
        filasEnemigos,
        columnasEnemigos,
        tiposEnemigos,
        enemigosActivos,
        0,
        "Murcielago",
        'M',
        ENEMIGO_LENTO,
        8,
        23
    );

    habitacionesEnemigos[0] = 0;

    iniciarEnemigo(
        nombresEnemigos,
        simbolosEnemigos,
        filasEnemigos,
        columnasEnemigos,
        tiposEnemigos,
        enemigosActivos,
        1,
        "Fantasma",
        'F',
        ENEMIGO_DIRECTO,
        2,
        24
    );

    habitacionesEnemigos[1] = 2;

    iniciarEnemigo(
        nombresEnemigos,
        simbolosEnemigos,
        filasEnemigos,
        columnasEnemigos,
        tiposEnemigos,
        enemigosActivos,
        2,
        "Arana",
        'A',
        ENEMIGO_LENTO,
        9,
        5
    );

    habitacionesEnemigos[2] = 4;

    iniciarEnemigo(
        nombresEnemigos,
        simbolosEnemigos,
        filasEnemigos,
        columnasEnemigos,
        tiposEnemigos,
        enemigosActivos,
        3,
        "Demonio",
        'D',
        ENEMIGO_DIRECTO,
        2,
        4
    );

    habitacionesEnemigos[3] = 5;

    if (cantidadEnemigos != 0)
    {
        *cantidadEnemigos = 4;
    }
}

/*
    CICLO PRINCIPAL
*/

void ejecutarJuego()
{
    char mapaBase[MAPA_FILAS][MAPA_COLUMNAS];

    std::string nombreJugador;
    char simboloJugador;
    int filaJugador;
    int columnaJugador;
    int vidasJugador;
    int inventarioJugador;
    int habitacionActual;
    int estadoJuego;

    std::string nombresObjetos[MAX_OBJETOS];
    char simbolosObjetos[MAX_OBJETOS];
    int filasObjetos[MAX_OBJETOS];
    int columnasObjetos[MAX_OBJETOS];
    int objetosActivos[MAX_OBJETOS];
    int cantidadObjetos;

    std::string nombresEnemigos[MAX_ENEMIGOS];
    char simbolosEnemigos[MAX_ENEMIGOS];
    int filasEnemigos[MAX_ENEMIGOS];
    int columnasEnemigos[MAX_ENEMIGOS];
    int tiposEnemigos[MAX_ENEMIGOS];
    int enemigosActivos[MAX_ENEMIGOS];
    int cantidadEnemigos;

    estadoJuego = ESTADO_JUGANDO;

    iniciarDatosJuego(
        &nombreJugador,
        &simboloJugador,
        &filaJugador,
        &columnaJugador,
        &vidasJugador,
        &inventarioJugador,
        &habitacionActual,
        nombresObjetos,
        simbolosObjetos,
        filasObjetos,
        columnasObjetos,
        objetosActivos,
        &cantidadObjetos,
        nombresEnemigos,
        simbolosEnemigos,
        filasEnemigos,
        columnasEnemigos,
        tiposEnemigos,
        enemigosActivos,
        &cantidadEnemigos
    );

    cargarHabitacion(mapaBase, habitacionActual);

    while (estadoJuego == ESTADO_JUGANDO)
    {
        jugarTurno(
            mapaBase,
            &nombreJugador,
            &simboloJugador,
            &filaJugador,
            &columnaJugador,
            &vidasJugador,
            &inventarioJugador,
            &habitacionActual,
            &estadoJuego,
            nombresObjetos,
            simbolosObjetos,
            filasObjetos,
            columnasObjetos,
            objetosActivos,
            cantidadObjetos,
            nombresEnemigos,
            simbolosEnemigos,
            filasEnemigos,
            columnasEnemigos,
            tiposEnemigos,
            enemigosActivos,
            cantidadEnemigos
        );

        esperarUnMomento();
    }

    pantallaPreparada = 0;
    limpiarPantalla();
    mostrarTitulo();
    mostrarMensajeFinal(estadoJuego);
}

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
)
{
    int i;
    int objetosVisibles[MAX_OBJETOS];
    int enemigosVisibles[MAX_ENEMIGOS];
    char tecla;

    if (
        nombreJugador == 0 ||
        simboloJugador == 0 ||
        filaJugador == 0 ||
        columnaJugador == 0 ||
        vidasJugador == 0 ||
        inventarioJugador == 0 ||
        habitacionActual == 0 ||
        estadoJuego == 0
    )
    {
        return;
    }

    habitacionTurnoJuego = *habitacionActual;

    cargarHabitacion(mapaBase, *habitacionActual);
    copiarMapaTemporal(mapaBase, mapaTurnoEnemigos);

    for (i = 0; i < MAX_OBJETOS; i = i + 1)
    {
        objetosVisibles[i] = 0;
    }

    for (i = 0; i < cantidadObjetos && i < MAX_OBJETOS; i = i + 1)
    {
        if (objetosActivos[i] == 1)
        {
            if (habitacionesObjetos[i] == *habitacionActual)
            {
                objetosVisibles[i] = 1;
            }
        }
    }

    for (i = 0; i < MAX_ENEMIGOS; i = i + 1)
    {
        enemigosVisibles[i] = 0;
    }

    for (i = 0; i < cantidadEnemigos && i < MAX_ENEMIGOS; i = i + 1)
    {
        if (enemigosActivos[i] == 1)
        {
            if (habitacionesEnemigos[i] == *habitacionActual)
            {
                enemigosVisibles[i] = 1;
            }
        }
    }

    limpiarPantalla();
    mostrarTitulo();

    mostrarEstadoJugador(
        *nombreJugador,
        *vidasJugador,
        *habitacionActual,
        *inventarioJugador,
        nombresObjetos
    );

    mostrarMapa(
        mapaBase,
        *habitacionActual,
        *filaJugador,
        *columnaJugador,
        *simboloJugador,
        simbolosObjetos,
        filasObjetos,
        columnasObjetos,
        objetosVisibles,
        cantidadObjetos,
        simbolosEnemigos,
        filasEnemigos,
        columnasEnemigos,
        enemigosVisibles,
        cantidadEnemigos
    );

    mostrarControles();

    tecla = leerTecla();

    if (tecla != '\0')
    {
        procesarTecla(
            tecla,
            mapaBase,
            filaJugador,
            columnaJugador,
            inventarioJugador,
            habitacionActual,
            estadoJuego,
            filasObjetos,
            columnasObjetos,
            objetosActivos,
            cantidadObjetos
        );
    }

    habitacionTurnoJuego = *habitacionActual;

    cargarHabitacion(mapaBase, *habitacionActual);
    copiarMapaTemporal(mapaBase, mapaTurnoEnemigos);

    if (*estadoJuego == ESTADO_JUGANDO)
    {
        revisarChoqueConEnemigos(
            filaJugador,
            columnaJugador,
            habitacionActual,
            vidasJugador,
            inventarioJugador,
            filasObjetos,
            columnasObjetos,
            objetosActivos,
            filasEnemigos,
            columnasEnemigos,
            enemigosActivos,
            cantidadEnemigos
);

        if (debeMoverEnemigos() == 1)
        {
            actualizarEnemigos(
                *filaJugador,
                *columnaJugador,
                filasEnemigos,
                columnasEnemigos,
                tiposEnemigos,
                enemigosActivos,
                cantidadEnemigos
            );
        }

        revisarChoqueConEnemigos(
            filaJugador,
            columnaJugador,
            habitacionActual,
            vidasJugador,
            inventarioJugador,
            filasObjetos,
            columnasObjetos,
            objetosActivos,
            filasEnemigos,
            columnasEnemigos,
            enemigosActivos,
            cantidadEnemigos
);

        actualizarEstadoJuego(
            estadoJuego,
            *habitacionActual,
            *inventarioJugador,
            *vidasJugador
        );
    }
}

/*
    ENTRADA DEL JUGADOR
*/

char leerTecla()
{
#ifdef _WIN32
    char tecla;

    if (_kbhit() == 0)
    {
        return '\0';
    }

    tecla = (char)_getch();

    return tecla;
#else
    struct termios configuracionAnterior;
    struct termios configuracionNueva;
    int banderasAnteriores;
    int caracter;

    if (tcgetattr(STDIN_FILENO, &configuracionAnterior) == -1)
    {
        return '\0';
    }

    configuracionNueva = configuracionAnterior;
    configuracionNueva.c_lflag = configuracionNueva.c_lflag & ~(ICANON | ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &configuracionNueva) == -1)
    {
        return '\0';
    }

    banderasAnteriores = fcntl(STDIN_FILENO, F_GETFL, 0);

    if (banderasAnteriores == -1)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &configuracionAnterior);
        return '\0';
    }

    fcntl(STDIN_FILENO, F_SETFL, banderasAnteriores | O_NONBLOCK);

    caracter = std::getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &configuracionAnterior);
    fcntl(STDIN_FILENO, F_SETFL, banderasAnteriores);

    if (caracter == EOF)
    {
        return '\0';
    }

    return (char)caracter;
#endif
}

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
)
{
    if (
        filaJugador == 0 ||
        columnaJugador == 0 ||
        inventarioJugador == 0 ||
        habitacionActual == 0 ||
        estadoJuego == 0
    )
    {
        return;
    }

    habitacionTurnoJuego = *habitacionActual;

    if (tecla == TECLA_ARRIBA || tecla == 'W')
    {
        intentarMoverJugador(
            mapaBase,
            filaJugador,
            columnaJugador,
            habitacionActual,
            -1,
            0
        );
    }
    else
    {
        if (tecla == TECLA_ABAJO || tecla == 'S')
        {
            intentarMoverJugador(
                mapaBase,
                filaJugador,
                columnaJugador,
                habitacionActual,
                1,
                0
            );
        }
        else
        {
            if (tecla == TECLA_IZQUIERDA || tecla == 'A')
            {
                intentarMoverJugador(
                    mapaBase,
                    filaJugador,
                    columnaJugador,
                    habitacionActual,
                    0,
                    -1
                );
            }
            else
            {
                if (tecla == TECLA_DERECHA || tecla == 'D')
                {
                    intentarMoverJugador(
                        mapaBase,
                        filaJugador,
                        columnaJugador,
                        habitacionActual,
                        0,
                        1
                    );
                }
                else
                {
                    if (tecla == TECLA_RECOGER || tecla == 'E')
                    {
                        revisarRecogerObjeto(
                            *filaJugador,
                            *columnaJugador,
                            inventarioJugador,
                            filasObjetos,
                            columnasObjetos,
                            objetosActivos,
                            cantidadObjetos
                        );
                    }
                    else
                    {
                        if (tecla == TECLA_SOLTAR || tecla == 'Q')
                        {
                            revisarSoltarObjeto(
                                *filaJugador,
                                *columnaJugador,
                                inventarioJugador,
                                filasObjetos,
                                columnasObjetos,
                                objetosActivos
                            );
                        }
                        else
                        {
                            if (tecla == TECLA_SALIR || tecla == 'X')
                            {
                                *estadoJuego = ESTADO_SALIR;
                            }
                        }
                    }
                }
            }
        }
    }
}

void intentarMoverJugador(
    char mapaBase[][MAPA_COLUMNAS],
    int* filaJugador,
    int* columnaJugador,
    int* habitacionActual,
    int cambioFila,
    int cambioColumna
)
{
    int nuevaFila;
    int nuevaColumna;
    int direccion;

    if (filaJugador == 0 || columnaJugador == 0 || habitacionActual == 0)
    {
        return;
    }

    nuevaFila = *filaJugador + cambioFila;
    nuevaColumna = *columnaJugador + cambioColumna;

    if (jugadorPuedeMoverse(mapaBase, nuevaFila, nuevaColumna) == 0)
    {
        return;
    }

    if (esPuerta(mapaBase, nuevaFila, nuevaColumna) == 1)
    {
        direccion = obtenerDireccionPuerta(nuevaFila, nuevaColumna);

        cambiarHabitacion(
            habitacionActual,
            filaJugador,
            columnaJugador,
            direccion
        );

        cargarHabitacion(mapaBase, *habitacionActual);
    }
    else
    {
        moverJugador(
            filaJugador,
            columnaJugador,
            cambioFila,
            cambioColumna
        );
    }
}

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
)
{
    int i;
    int limite;

    if (inventarioJugador == 0)
    {
        return;
    }

    if (*inventarioJugador != INVENTARIO_VACIO)
    {
        return;
    }

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
            if (habitacionesObjetos[i] == habitacionTurnoJuego)
            {
                if (mismaPosicion(
                    filaJugador,
                    columnaJugador,
                    filasObjetos[i],
                    columnasObjetos[i]
                ) == 1)
                {
                    recogerObjeto(
                        inventarioJugador,
                        i,
                        objetosActivos
                    );

                    return;
                }
            }
        }
    }
}

void revisarSoltarObjeto(
    int filaJugador,
    int columnaJugador,
    int* inventarioJugador,
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

    indiceObjeto = *inventarioJugador;

    if (indiceObjeto == INVENTARIO_VACIO)
    {
        return;
    }

    if (indiceObjeto < 0 || indiceObjeto >= MAX_OBJETOS)
    {
        *inventarioJugador = INVENTARIO_VACIO;
        return;
    }

    habitacionesObjetos[indiceObjeto] = habitacionTurnoJuego;

    soltarObjeto(
        inventarioJugador,
        filaJugador,
        columnaJugador,
        filasObjetos,
        columnasObjetos,
        objetosActivos
    );
}

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
)
{
    int i;
    int limite;
    int nuevaFila;
    int nuevaColumna;

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
            if (habitacionesEnemigos[i] == habitacionTurnoJuego)
            {
                nuevaFila = filasEnemigos[i];
                nuevaColumna = columnasEnemigos[i];

                moverEnemigo(
                    &nuevaFila,
                    &nuevaColumna,
                    tiposEnemigos[i],
                    filaJugador,
                    columnaJugador
                );

                if (jugadorPuedeMoverse(mapaTurnoEnemigos, nuevaFila, nuevaColumna) == 1)
                {
                    filasEnemigos[i] = nuevaFila;
                    columnasEnemigos[i] = nuevaColumna;
                }
            }
        }
    }
}

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
)
{
    int i;
    int limite;
    int indiceObjeto;
    int filaGolpe;
    int columnaGolpe;
    int habitacionGolpe;

    if (
        filaJugador == 0 ||
        columnaJugador == 0 ||
        habitacionActual == 0 ||
        vidasJugador == 0 ||
        inventarioJugador == 0
    )
    {
        return;
    }

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
            if (habitacionesEnemigos[i] == habitacionTurnoJuego)
            {
                if (enemigoTocaJugador(
                    filasEnemigos[i],
                    columnasEnemigos[i],
                    *filaJugador,
                    *columnaJugador
                ) == 1)
                {
                    filaGolpe = *filaJugador;
                    columnaGolpe = *columnaJugador;
                    habitacionGolpe = *habitacionActual;

                    if (*inventarioJugador != INVENTARIO_VACIO)
                    {
                        indiceObjeto = *inventarioJugador;

                        if (indiceObjeto >= 0 && indiceObjeto < MAX_OBJETOS)
                        {
                            filasObjetos[indiceObjeto] = filaGolpe;
                            columnasObjetos[indiceObjeto] = columnaGolpe;
                            objetosActivos[indiceObjeto] = 1;
                            habitacionesObjetos[indiceObjeto] = habitacionGolpe;
                        }

                        *inventarioJugador = INVENTARIO_VACIO;
                    }

                    quitarVidaJugador(vidasJugador);

                    if (*vidasJugador > 0)
                    {
                        *habitacionActual = 0;
                        *filaJugador = 5;
                        *columnaJugador = 5;
                        habitacionTurnoJuego = 0;
                    }

                    return;
                }
            }
        }
    }
}

/*
    VICTORIA Y DERROTA
*/

int revisarVictoria(
    int habitacionActual,
    int inventarioJugador
)
{
    if (habitacionActual == TOTAL_HABITACIONES - 1)
    {
        if (inventarioJugador == OBJETO_TESORO)
        {
            return 1;
        }
    }

    return 0;
}

int revisarDerrota(
    int vidasJugador
)
{
    if (jugadorSigueVivo(vidasJugador) == 0)
    {
        return 1;
    }

    return 0;
}

void actualizarEstadoJuego(
    int* estadoJuego,
    int habitacionActual,
    int inventarioJugador,
    int vidasJugador
)
{
    if (estadoJuego == 0)
    {
        return;
    }

    if (revisarDerrota(vidasJugador) == 1)
    {
        *estadoJuego = ESTADO_DERROTA;
        return;
    }

    if (revisarVictoria(habitacionActual, inventarioJugador) == 1)
    {
        *estadoJuego = ESTADO_VICTORIA;
        return;
    }

    *estadoJuego = ESTADO_JUGANDO;
}

void mostrarMensajeFinal(
    int estadoJuego
)
{
    std::cout << "##############################" << std::endl;
    std::cout << "#                            #" << std::endl;

    if (estadoJuego == ESTADO_VICTORIA)
    {
        std::cout << "#          GANASTE           #" << std::endl;
        std::cout << "#                            #" << std::endl;
        std::cout << "#   Llegaste con el tesoro   #" << std::endl;
    }
    else
    {
        if (estadoJuego == ESTADO_DERROTA)
        {
            std::cout << "#          PERDISTE          #" << std::endl;
            std::cout << "#                            #" << std::endl;
            std::cout << "#   Te quedaste sin vidas    #" << std::endl;
        }
        else
        {
            if (estadoJuego == ESTADO_SALIR)
            {
                std::cout << "#       SALISTE DEL JUEGO    #" << std::endl;
                std::cout << "#                            #" << std::endl;
                std::cout << "#   Cerraste la partida      #" << std::endl;
            }
        }
    }

    std::cout << "#                            #" << std::endl;
    std::cout << "##############################" << std::endl;
}

/*
    INFORMACION EN PANTALLA
*/

void mostrarEstadoJugador(
    std::string nombreJugador,
    int vidasJugador,
    int habitacionActual,
    int inventarioJugador,
    std::string nombresObjetos[]
)
{
    std::cout << "Jugador: " << nombreJugador << std::endl;
    std::cout << "Vidas: " << vidasJugador << std::endl;
    std::cout << "Habitacion actual: " << habitacionActual + 1 << std::endl;

    if (inventarioJugador == INVENTARIO_VACIO)
    {
        std::cout << "Inventario: vacio" << std::endl;
    }
    else
    {
        if (inventarioJugador >= 0 && inventarioJugador < MAX_OBJETOS)
        {
            std::cout << "Inventario: " << nombresObjetos[inventarioJugador] << std::endl;
        }
        else
        {
            std::cout << "Inventario: error" << std::endl;
        }
    }

    std::cout << std::endl;
}

void limpiarPantalla()
{
    if (pantallaPreparada == 0)
    {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif

        pantallaPreparada = 1;
    }
    else
    {
        std::cout << "\033[H";
    }
}

void pausarJuego()
{
    std::cout << "Presiona ENTER para continuar.";
    std::cin.ignore(1000, '\n');
    std::cin.get();
}
