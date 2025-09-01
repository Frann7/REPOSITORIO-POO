#include "casilla.h"
#include "jugador.h"
#include <QDebug>

// Variable estática para rastrear jugadores en el pozo
static QVector<Jugador*> jugadoresEnPozo;

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
    if(destino > 0 && destino <= 63 && jugador->getPosicion() != destino) {
        jugador->setPosicion(destino);
    }
}

// Casilla Puente
CasillaPuente::CasillaPuente(int numero, int destino) : Casilla(numero), destino(destino) {}

QString CasillaPuente::getTipo() const {
    return "Puente";
}

void CasillaPuente::aplicarEfecto(Jugador *jugador) {
    if(destino > 0 && destino <= 63 && jugador->getPosicion() != destino) {
        jugador->setPosicion(destino);
    }
}

// Casilla Posada
CasillaPosada::CasillaPosada(int numero) : Casilla(numero) {}

QString CasillaPosada::getTipo() const {
    return "Posada";
}

void CasillaPosada::aplicarEfecto(Jugador *jugador) {
    // Solo aplicar si no tiene ya turnos perdidos para evitar acumulación
    if (jugador->getTurnosPerdidos() == 0) {
        jugador->establecerTurnosPerdidos(1);
    }
}

// Casilla Pozo
CasillaPozo::CasillaPozo(int numero) : Casilla(numero) {}

QString CasillaPozo::getTipo() const {
    return "Pozo";
}

void CasillaPozo::aplicarEfecto(Jugador *jugador) {
    // Solo aplicar si no está ya en el pozo
    if (jugador->getTurnosPerdidos() != 99) {
        // Verificar si ya hay jugadores en el pozo y liberarlos
        for (int i = jugadoresEnPozo.size() - 1; i >= 0; i--) {
            Jugador* j = jugadoresEnPozo[i];
            if (j != jugador && j->getTurnosPerdidos() == 99) {
                j->establecerTurnosPerdidos(0); // Liberar jugador del pozo
                jugadoresEnPozo.removeAt(i);
                qDebug() << j->getNombre() << "liberado del pozo";
            }
        }

        // El jugador actual cae en el pozo
        jugador->establecerTurnosPerdidos(99);
        if (!jugadoresEnPozo.contains(jugador)) {
            jugadoresEnPozo.append(jugador);
        }
        qDebug() << jugador->getNombre() << "cae en el pozo";
    }
}

// Casilla Laberinto
CasillaLaberinto::CasillaLaberinto(int numero, int destino) : Casilla(numero), destino(destino) {}

QString CasillaLaberinto::getTipo() const {
    return "Laberinto";
}

void CasillaLaberinto::aplicarEfecto(Jugador *jugador) {
    if(destino > 0 && destino <= 63 && jugador->getPosicion() != destino) {
        jugador->setPosicion(destino);
    }
}

// Casilla Carcel
CasillaCarcel::CasillaCarcel(int numero) : Casilla(numero) {}

QString CasillaCarcel::getTipo() const {
    return "Carcel";
}

void CasillaCarcel::aplicarEfecto(Jugador *jugador) {
    // Solo aplicar si no tiene ya turnos perdidos para evitar acumulación
    if (jugador->getTurnosPerdidos() == 0) {
        jugador->establecerTurnosPerdidos(2);
    }
}

// Casilla Calavera
CasillaCalavera::CasillaCalavera(int numero) : Casilla(numero) {}

QString CasillaCalavera::getTipo() const {
    return "Calavera";
}

void CasillaCalavera::aplicarEfecto(Jugador *jugador) {
    if (jugador->getPosicion() != 1) {
        jugador->setPosicion(1);
    }
}
