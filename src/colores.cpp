#include "../include/colores.h"

#ifdef _WIN32
    #include <windows.h>

    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif

const char* colorJugador()
{
    return "\033[36m";
}

const char* colorEnemigo()
{
    return "\033[31m";
}

const char* colorObjeto()
{
    return "\033[33m";
}

const char* colorPared()
{
    return "\033[38;5;94m";
}

const char* colorPuerta()
{
    return "\033[34m";
}

const char* colorPiso()
{
    return "\033[38;5;180m";
}

const char* colorTextoNormal()
{
    return "\033[0m";
}

const char* obtenerColorPorSimbolo(char simbolo)
{
    if (simbolo == '@')
    {
        return colorJugador();
    }

    if (simbolo == 'M' || simbolo == 'F' || simbolo == 'A' || simbolo == 'D')
    {
        return colorEnemigo();
    }

    if (simbolo == 'L' || simbolo == 'T')
    {
        return colorObjeto();
    }

    if (simbolo == '#')
    {
        return colorPared();
    }

    if (simbolo == '+')
    {
        return colorPuerta();
    }

    if (simbolo == '.')
    {
        return colorPiso();
    }

    return colorTextoNormal();
}

void prepararColores()
{
#ifdef _WIN32
    HANDLE salida;
    DWORD modo;

    salida = GetStdHandle(STD_OUTPUT_HANDLE);

    if (salida == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (GetConsoleMode(salida, &modo) == 0)
    {
        return;
    }

    modo = modo | ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    SetConsoleMode(salida, modo);
#endif
}