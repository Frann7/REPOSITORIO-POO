#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>
#include <QColor>
#include <QVector>

class Jugador
{
public:
    explicit Jugador(const QString &nombre);

    // Getters
    QString getNombre() const;
    int getPosicion() const;
    int getTurnosPerdidos() const;
    QColor getColor() const;
    QString getIcono() const;

    // Métodos de juego
    void avanzar(int pasos);
    void perderTurno(int turnos);
    void establecerTurnosPerdidos(int turnos); // Método más seguro
    void reducirTurnosPerdidos(); // Nuevo método
    void reiniciar();
    void setPosicion(int nuevaPosicion);

    // Método estático para resetear contador
    static void resetContadorJugadores();

private:
    QString nombre;
    int posicion;
    int turnosPerdidos;
    QColor color;
    QString icono;

    // Variables estáticas para asignación de colores e iconos
    static QVector<QColor> coloresDisponibles;
    static QVector<QString> iconosDisponibles;
    static int contadorJugadores;

    void asignarColorEIcono();
};

#endif // JUGADOR_H
