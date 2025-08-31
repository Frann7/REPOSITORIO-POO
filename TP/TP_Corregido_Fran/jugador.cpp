#include "jugador.h"
#include <QVector>

// Variables estáticas para colores e iconos
QVector<QColor> Jugador::coloresDisponibles = {
    QColor(255, 0, 0),    // Rojo
    QColor(0, 0, 255),    // Azul
    QColor(0, 255, 0),    // Verde
    QColor(255, 255, 0),  // Amarillo
    QColor(255, 0, 255),  // Magenta
    QColor(0, 255, 255),  // Cian
    QColor(255, 165, 0),  // Naranja
    QColor(128, 0, 128)   // Púrpura
};

QVector<QString> Jugador::iconosDisponibles = {
    "🔴", "🔵", "🟢", "🟡", "🟣", "🟠", "⚫", "⚪"
};

int Jugador::contadorJugadores = 0;

Jugador::Jugador(const QString &nombre)
    : nombre(nombre), posicion(1), turnosPerdidos(0)
{
    asignarColorEIcono();
}

QString Jugador::getNombre() const
{
    return nombre;
}

int Jugador::getPosicion() const
{
    return posicion;
}

int Jugador::getTurnosPerdidos() const
{
    return turnosPerdidos;
}

QColor Jugador::getColor() const
{
    return color;
}

QString Jugador::getIcono() const
{
    return icono;
}

void Jugador::avanzar(int pasos)
{
    posicion += pasos;
    if (posicion < 1) posicion = 1;
    if (posicion > 63) posicion = 63;
}

void Jugador::perderTurno(int turnos)
{
    turnosPerdidos += turnos;
    if (turnosPerdidos < 0) turnosPerdidos = 0;
}

void Jugador::reiniciar()
{
    posicion = 1;
    turnosPerdidos = 0;
}

void Jugador::setPosicion(int nuevaPosicion)
{
    posicion = nuevaPosicion;
    if (posicion < 1) posicion = 1;
    if (posicion > 63) posicion = 63;
}

void Jugador::asignarColorEIcono()
{
    int indice = contadorJugadores % coloresDisponibles.size();
    color = coloresDisponibles[indice];
    icono = iconosDisponibles[indice];
    contadorJugadores++;
}
