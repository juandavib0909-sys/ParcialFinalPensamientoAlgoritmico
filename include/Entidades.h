#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <string>

const int MAX_ENEMIGOS = 10;
const int MAX_OBJETOS = 10;

struct Posicion
{
    int fila;
    int columna;
};

struct Objeto
{
    std::string nombre;
    char simbolo;
    Posicion posicion;
    bool activo;
};

struct Personaje
{
    std::string nombre;
    char simbolo;
    Posicion posicion;
    int vidas;
    bool tieneObjeto;
    Objeto* inventario;
};

struct Enemigo
{
    std::string nombre;
    char simbolo;
    Posicion posicion;
    int tipo;
    bool activo;
};

void inicializarPosicion(Posicion* posicion, int fila, int columna);

void inicializarObjeto(Objeto* objeto, std::string nombre, char simbolo, int fila, int columna);
void mostrarObjeto(Objeto* objeto);
void activarObjeto(Objeto* objeto);
void desactivarObjeto(Objeto* objeto);

void inicializarPersonaje(Personaje* personaje, std::string nombre, char simbolo, int fila, int columna);
void moverPersonaje(Personaje* personaje, int cambioFila, int cambioColumna);
void recogerObjeto(Personaje* personaje, Objeto* objeto);
void soltarObjeto(Personaje* personaje);
void quitarVida(Personaje* personaje);

void inicializarEnemigo(Enemigo* enemigo, std::string nombre, char simbolo, int tipo, int fila, int columna);
void moverEnemigoBasico(Enemigo* enemigo, Personaje* personaje);
void moverEnemigoRapido(Enemigo* enemigo, Personaje* personaje);
void moverEnemigo(Enemigo* enemigo, Personaje* personaje);

bool mismaPosicion(Posicion* primera, Posicion* segunda);
bool personajeEstaVivo(Personaje* personaje);
bool enemigoTocaPersonaje(Enemigo* enemigo, Personaje* personaje);

#endif
