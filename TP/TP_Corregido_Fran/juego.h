#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>
#include <QVector>
#include "jugador.h"
#include "tablero.h"

class Juego : public QObject
{
    Q_OBJECT
public:
    explicit Juego(QObject *parent = nullptr);
    ~Juego();

    void iniciar(int numJugadores);
    void jugarTurno();
    int lanzarDado();
    bool verificarGanador();
    void moverJugador(Jugador *jugador, int pasos);

    // Getters para la interfaz gráfica
    QVector<Jugador*> getJugadores() const;
    Tablero* getTablero() const;
    int getTurnoActual() const;

signals:
    void mensajeActualizado(const QString &mensaje);
    void juegoTerminado(const QString &ganador);
    void tableroActualizado();

private:
    QVector<Jugador*> jugadores;
    Tablero *tablero;
    int turnoActual;
    int dado;
};

#endif // JUEGO_H
