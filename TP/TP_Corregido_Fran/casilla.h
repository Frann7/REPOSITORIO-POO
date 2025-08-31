#ifndef CASILLA_H
#define CASILLA_H

#include <QString>

class Jugador; // Forward declaration

// Clase base
class Casilla
{
public:
    Casilla(int numero);
    virtual ~Casilla() = default;

    int getNumero() const;
    virtual QString getTipo() const = 0;
    virtual void aplicarEfecto(Jugador *jugador) = 0;

protected:
    int numero;
};

// Casillas específicas
class CasillaNormal : public Casilla
{
public:
    CasillaNormal(int numero);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
};

class CasillaOca : public Casilla
{
public:
    CasillaOca(int numero, int destino);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
private:
    int destino;
};

class CasillaPuente : public Casilla
{
public:
    CasillaPuente(int numero, int destino);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
private:
    int destino;
};

class CasillaPosada : public Casilla
{
public:
    CasillaPosada(int numero);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
};

class CasillaPozo : public Casilla
{
public:
    CasillaPozo(int numero);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
};

class CasillaLaberinto : public Casilla
{
public:
    CasillaLaberinto(int numero, int destino);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
private:
    int destino;
};

class CasillaCarcel : public Casilla
{
public:
    CasillaCarcel(int numero);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
};

class CasillaCalavera : public Casilla
{
public:
    CasillaCalavera(int numero);
    QString getTipo() const override;
    void aplicarEfecto(Jugador *jugador) override;
};

#endif // CASILLA_H
