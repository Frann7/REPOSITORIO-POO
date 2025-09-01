#include "juego.h"
#include <QRandomGenerator>
#include <QDebug>

Juego::Juego(QObject *parent)
    : QObject(parent), tablero(nullptr), turnoActual(0), dado(0)
{
}

Juego::~Juego()
{
    // Limpiar jugadores
    for (Jugador* jugador : jugadores) {
        delete jugador;
    }
    jugadores.clear();

    // Limpiar tablero
    if (tablero) {
        delete tablero;
        tablero = nullptr;
    }
}

void Juego::iniciar(int numJugadores)
{
    // Limpiar juego anterior
    for (Jugador* jugador : jugadores) {
        delete jugador;
    }
    jugadores.clear();

    if (tablero) {
        delete tablero;
    }

    // Crear nuevo tablero
    tablero = new Tablero();

    // Crear jugadores
    for (int i = 0; i < numJugadores; i++) {
        QString nombre = QString("Jugador %1").arg(i + 1);
        jugadores.append(new Jugador(nombre));
    }

    turnoActual = 0;
    // Resetear contador de jugadores para colores
    Jugador::resetContadorJugadores();

    emit mensajeActualizado("¡Juego iniciado!");
    emit mensajeActualizado(QString("Turno de %1").arg(jugadores[turnoActual]->getNombre()));
}

void Juego::jugarTurno()
{
    if (jugadores.isEmpty() || !tablero) {
        return;
    }

    Jugador* jugadorActual = jugadores[turnoActual];

    // Verificar si el jugador tiene turnos perdidos
    if (jugadorActual->getTurnosPerdidos() > 0) {
        jugadorActual->reducirTurnosPerdidos(); // Nuevo método para reducir correctamente
        emit mensajeActualizado(QString("%1 pierde el turno (turnos restantes: %2)")
                                    .arg(jugadorActual->getNombre())
                                    .arg(jugadorActual->getTurnosPerdidos()));

        // Pasar al siguiente jugador
        turnoActual = (turnoActual + 1) % jugadores.size();
        emit mensajeActualizado(QString("Turno de %1").arg(jugadores[turnoActual]->getNombre()));
        emit tableroActualizado();
        return;
    }

    // Lanzar dado
    int resultadoDado = lanzarDado();
    emit mensajeActualizado(QString("%1 lanzó el dado: %2")
                                .arg(jugadorActual->getNombre())
                                .arg(resultadoDado));

    // Mover jugador
    moverJugador(jugadorActual, resultadoDado);

    // Verificar ganador
    if (verificarGanador()) {
        emit juegoTerminado(jugadorActual->getNombre());
        return;
    }

    // Pasar al siguiente jugador
    turnoActual = (turnoActual + 1) % jugadores.size();
    emit mensajeActualizado(QString("Turno de %1").arg(jugadores[turnoActual]->getNombre()));

    emit tableroActualizado();
}

int Juego::lanzarDado()
{
    dado = QRandomGenerator::global()->bounded(1, 7); // 1-6
    return dado;
}

bool Juego::verificarGanador()
{
    if (jugadores.isEmpty() || !tablero) {
        return false;
    }

    Jugador* jugadorActual = jugadores[turnoActual];
    return tablero->casillaFinal(jugadorActual->getPosicion());
}

void Juego::moverJugador(Jugador *jugador, int pasos)
{
    if (!jugador || !tablero) {
        return;
    }

    int posicionAnterior = jugador->getPosicion();

    // Mover jugador
    jugador->avanzar(pasos);

    // Verificar límites del tablero
    if (jugador->getPosicion() > 63) {
        int exceso = jugador->getPosicion() - 63;
        jugador->setPosicion(63 - exceso); // Rebotar
        emit mensajeActualizado(QString("%1 rebota y va a la casilla %2")
                                    .arg(jugador->getNombre())
                                    .arg(jugador->getPosicion()));
    }

    emit mensajeActualizado(QString("%1 se movió de la casilla %2 a la %3")
                                .arg(jugador->getNombre())
                                .arg(posicionAnterior)
                                .arg(jugador->getPosicion()));

    // Aplicar efecto de la casilla SOLO UNA VEZ
    Casilla* casilla = tablero->obtenerCasilla(jugador->getPosicion());
    if (casilla) {
        QString tipoCasilla = casilla->getTipo();
        if (tipoCasilla != "Normal") {
            emit mensajeActualizado(QString("%1 cayó en casilla %2 (%3)")
                                        .arg(jugador->getNombre())
                                        .arg(jugador->getPosicion())
                                        .arg(tipoCasilla));
        }

        int posicionAntesEfecto = jugador->getPosicion();
        int turnosAntesEfecto = jugador->getTurnosPerdidos();

        // Aplicar efecto UNA SOLA VEZ
        casilla->aplicarEfecto(jugador);

        // Verificar si la posición cambió después del efecto
        if (jugador->getPosicion() != posicionAntesEfecto) {
            emit mensajeActualizado(QString("%1 se movió por efecto especial a la casilla %2")
                                        .arg(jugador->getNombre())
                                        .arg(jugador->getPosicion()));
        }

        // Verificar turnos perdidos SOLO si cambió
        if (jugador->getTurnosPerdidos() != turnosAntesEfecto) {
            QString mensaje;
            if (jugador->getTurnosPerdidos() == 99) {
                mensaje = QString("%1 cayó en el pozo y esperará hasta que otro jugador también caiga")
                              .arg(jugador->getNombre());
            } else if (jugador->getTurnosPerdidos() > 0) {
                mensaje = QString("%1 perderá %2 turno(s)")
                              .arg(jugador->getNombre())
                              .arg(jugador->getTurnosPerdidos());
            }
            if (!mensaje.isEmpty()) {
                emit mensajeActualizado(mensaje);
            }
        }
    }
}

QVector<Jugador*> Juego::getJugadores() const
{
    return jugadores;
}

Tablero* Juego::getTablero() const
{
    return tablero;
}

int Juego::getTurnoActual() const
{
    return turnoActual;
}
