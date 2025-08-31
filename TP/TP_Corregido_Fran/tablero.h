// tablero.h
#ifndef TABLERO_H
#define TABLERO_H

#include <QVector>
#include "casilla.h"

class Tablero
{
public:
    Tablero();
    ~Tablero();

    Casilla* obtenerCasilla(int numero);
    void iniciarTablero();
    bool casillaFinal(int posicion) const;

private:
    QVector<Casilla*> casillas;
};

#endif // TABLERO_H
