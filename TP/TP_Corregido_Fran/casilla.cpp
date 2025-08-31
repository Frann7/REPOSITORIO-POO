#include "casilla.h"
#include "jugador.h"

// Casilla base
Casilla::Casilla(int numero) : numero(numero) {}

int Casilla::getNumero() const {
    return numero;
}

// Casilla Normal
CasillaNormal::CasillaNormal(int numero) : Casilla(numero) {}

QString CasillaNormal::getTipo() const {
    return "Normal";
}

void CasillaNormal::aplicarEfecto(Jugador *jugador) {
    // No hace nada
}

// Casilla Oca
CasillaOca::CasillaOca(int numero, int destino) : Casilla(numero), destino(destino) {}

QString CasillaOca::getTipo() const {
    return "Oca";
}

void CasillaOca::aplicarEfecto(Jugador *jugador) {
    if(destino > 0 && destino <= 63) {
        jugador->avanzar(destino - jugador->getPosicion());
    }
}

// Casilla Puente
CasillaPuente::CasillaPuente(int numero, int destino) : Casilla(numero), destino(destino) {}

QString CasillaPuente::getTipo() const {
    return "Puente";
}

void CasillaPuente::aplicarEfecto(Jugador *jugador) {
    jugador->avanzar(destino - jugador->getPosicion());
}

// Casilla Posada
CasillaPosada::CasillaPosada(int numero) : Casilla(numero) {}

QString CasillaPosada::getTipo() const {
    return "Posada";
}

void CasillaPosada::aplicarEfecto(Jugador *jugador) {
    jugador->perderTurno(1);
}

// Casilla Pozo
CasillaPozo::CasillaPozo(int numero) : Casilla(numero) {}

QString CasillaPozo::getTipo() const {
    return "Pozo";
}

void CasillaPozo::aplicarEfecto(Jugador *jugador) {
    jugador->perderTurno(99);
}

// Casilla Laberinto
CasillaLaberinto::CasillaLaberinto(int numero, int destino) : Casilla(numero), destino(destino) {}

QString CasillaLaberinto::getTipo() const {
    return "Laberinto";
}

void CasillaLaberinto::aplicarEfecto(Jugador *jugador) {
    jugador->avanzar(destino - jugador->getPosicion());
}

// Casilla Carcel
CasillaCarcel::CasillaCarcel(int numero) : Casilla(numero) {}

QString CasillaCarcel::getTipo() const {
    return "Carcel";
}

void CasillaCarcel::aplicarEfecto(Jugador *jugador) {
    jugador->perderTurno(2);
}

// Casilla Calavera
CasillaCalavera::CasillaCalavera(int numero) : Casilla(numero) {}

QString CasillaCalavera::getTipo() const {
    return "Calavera";
}

void CasillaCalavera::aplicarEfecto(Jugador *jugador) {
    jugador->avanzar(1 - jugador->getPosicion());
}
