#ifndef MENU_H
#define MENU_H

const int MENU_INICIAR = 1;
const int MENU_SALIR = 0;

const char OPCION_INICIAR = '1';
const char OPCION_SALIR = '2';
const char OPCION_CONTINUAR = 'c';
const char OPCION_CONTINUAR_MAYUSCULA = 'C';

/*
    MENU PRINCIPAL
*/

void mostrarMenuPrincipal();

char leerOpcionMenu();

int ejecutarMenuInicial();

/*
    PANTALLAS DEL MENU
*/

void mostrarPantallaInstrucciones();

void mostrarPantallaObjetivo();

void mostrarPantallaControles();

/*
    FUNCIONES DE APOYO DEL MENU
*/

void esperarContinuar();

void limpiarPantallaMenu();

#endif