#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>
#include "juego.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_iniciarJuegoButton_clicked();
    void on_tirarDadoButton_clicked();
    void on_clearButton_clicked(); // Nuevo slot para el botón clear
    void actualizarMensaje(const QString &mensaje);
    void juegoTerminado(const QString &ganador);

private:
    void crearTableroVisual();
    void crearCasilla(int numero, int fila, int columna); // Nuevo método auxiliar
    void actualizarTablero();

    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    QVBoxLayout *controlLayout;
    QGridLayout *tableroLayout;

    QSpinBox *numJugadoresSpinBox;
    QPushButton *iniciarJuegoButton;
    QPushButton *tirarDadoButton;
    QPushButton *clearButton; // Nuevo botón
    QTextEdit *mensajesTextEdit;

    QVector<QLabel*> casillasLabels;

    Juego *juego;
    int numJugadores;
};

#endif // MAINWINDOW_H
