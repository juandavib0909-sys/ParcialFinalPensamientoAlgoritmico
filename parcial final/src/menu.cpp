#include "../include/menu.h"
#include "../include/colores.h" 
#include <iostream>
#include <cstdlib>

/*
    MENU PRINCIPAL
*/

void mostrarMenuPrincipal()
{
    limpiarPantallaMenu();

    std::cout << colorObjeto();
    std::cout << "Las flipantes mazmorras de Juan y Juan" << std::endl;
    std::cout << colorTextoNormal();

    std::cout << std::endl;

    std::cout << colorPuerta();
    std::cout << "1. Start" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << colorTextoNormal();
    std::cout << std::endl;

    std::cout << "Seleccione una opcion: ";
}

char leerOpcionMenu()
{
    char opcion;

    std::cin >> opcion;

    return opcion;
}

int ejecutarMenuInicial()
{
    char opcion;
    int opcionValida;

    prepararColores();

    opcionValida = 0;

    while (opcionValida == 0)
    {
        mostrarMenuPrincipal();

        opcion = leerOpcionMenu();

        if (opcion == OPCION_INICIAR)
        {
            opcionValida = 1;

            mostrarPantallaInstrucciones();
            esperarContinuar();

            mostrarPantallaObjetivo();
            esperarContinuar();

            mostrarPantallaControles();
            esperarContinuar();

            return MENU_INICIAR;
        }
        else
        {
            if (opcion == OPCION_SALIR)
            {
                opcionValida = 1;
                return MENU_SALIR;
            }
            else
            {
                limpiarPantallaMenu();

                std::cout << "Opcion no valida." << std::endl;
                std::cout << "Use 1 para iniciar o 2 para salir." << std::endl;
                std::cout << std::endl;

                esperarContinuar();
            }
        }
    }

    return MENU_SALIR;
}

/*
    PANTALLAS DEL MENU
*/

void mostrarPantallaInstrucciones()
{
    limpiarPantallaMenu();

    std::cout << "             INSTRUCCIONES            " << std::endl;
    std::cout << std::endl;

    std::cout << "@  = Jugador" << std::endl;
    std::cout << "M  = Enemigo lento" << std::endl;
    std::cout << "F  = Enemigo directo" << std::endl;
    std::cout << "A  = Enemigo lento" << std::endl;
    std::cout << "D  = Enemigo directo" << std::endl;
    std::cout << "L  = Llave" << std::endl;
    std::cout << "T  = Tesoro" << std::endl;
    std::cout << "#  = Pared" << std::endl;
    std::cout << "+  = Puerta" << std::endl;
    std::cout << ".  = Piso" << std::endl;
    std::cout << std::endl;

    std::cout << "Presione C para continuar." << std::endl;
}

void mostrarPantallaObjetivo()
{
    limpiarPantallaMenu();

    std::cout << "                OBJETIVO              " << std::endl;
    std::cout << std::endl;

    std::cout << "Explora las habitaciones del mapa." << std::endl;
    std::cout << "Evita que los enemigos te quiten todas las vidas." << std::endl;
    std::cout << "Encuentra los objetos importantes del juego." << std::endl;
    std::cout << "Llega a la ultima habitacion con el tesoro para ganar." << std::endl;
    std::cout << std::endl;

    std::cout << "Presione C para continuar." << std::endl;
}

void mostrarPantallaControles()
{
    limpiarPantallaMenu();

    std::cout << "               CONTROLES              " << std::endl;
    std::cout << std::endl;

    std::cout << "W  = moverse arriba" << std::endl;
    std::cout << "S  = moverse abajo" << std::endl;
    std::cout << "A  = moverse izquierda" << std::endl;
    std::cout << "D  = moverse derecha" << std::endl;
    std::cout << "E  = recoger objeto" << std::endl;
    std::cout << "Q  = soltar objeto" << std::endl;
    std::cout << "X  = salir del juego" << std::endl;
    std::cout << std::endl;

    std::cout << "Presione C para empezar el juego." << std::endl;
}

/*
    FUNCIONES DE APOYO DEL MENU
*/

void esperarContinuar()
{
    char opcion;
    int continuar;

    continuar = 0;

    while (continuar == 0)
    {
        std::cout << "> ";
        std::cin >> opcion;

        if (opcion == OPCION_CONTINUAR || opcion == OPCION_CONTINUAR_MAYUSCULA)
        {
            continuar = 1;
        }
        else
        {
            std::cout << "Presione C para continuar." << std::endl;
        }
    }
}

void limpiarPantallaMenu()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}