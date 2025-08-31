#include "tablero.h"

Tablero::Tablero()
{
    iniciarTablero();
}

Tablero::~Tablero()
{
    for(Casilla *casilla : casillas) {
        delete casilla;
    }
}

Casilla* Tablero::obtenerCasilla(int numero)
{
    if(numero < 1 || numero > casillas.size()) {
        return nullptr;
    }
    return casillas[numero - 1];
}

void Tablero::iniciarTablero()
{
    casillas.resize(63);

    // Crear todas como normales primero
    for(int i = 0; i < 63; i++) {
        casillas[i] = new CasillaNormal(i+1);
    }

    // Reemplazar con casillas especiales
    delete casillas[5]; // Casilla 6
    casillas[5] = new CasillaPuente(6, 12);

    delete casillas[8]; // Casilla 9
    casillas[8] = new CasillaOca(9, 18);

    delete casillas[17]; // Casilla 18
    casillas[17] = new CasillaOca(18, 27);

    delete casillas[26]; // Casilla 27
    casillas[26] = new CasillaOca(27, 36);

    delete casillas[35]; // Casilla 36
    casillas[35] = new CasillaOca(36, 45);

    delete casillas[44]; // Casilla 45
    casillas[44] = new CasillaOca(45, 54);

    delete casillas[53]; // Casilla 54
    casillas[53] = new CasillaOca(54, 63);

    delete casillas[18]; // Casilla 19
    casillas[18] = new CasillaPosada(19);

    delete casillas[30]; // Casilla 31
    casillas[30] = new CasillaPozo(31);

    delete casillas[41]; // Casilla 42
    casillas[41] = new CasillaLaberinto(42, 30);

    delete casillas[55]; // Casilla 56
    casillas[55] = new CasillaCarcel(56);

    delete casillas[57]; // Casilla 58
    casillas[57] = new CasillaCalavera(58);
}

bool Tablero::casillaFinal(int posicion) const
{
    return posicion == 63;
}
