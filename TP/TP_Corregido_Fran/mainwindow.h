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
    void actualizarMensaje(const QString &mensaje);
    void juegoTerminado(const QString &ganador);

private:
    void crearTableroVisual();
    void actualizarTablero();

    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    QVBoxLayout *controlLayout;
    QGridLayout *tableroLayout;

    QSpinBox *numJugadoresSpinBox;
    QPushButton *iniciarJuegoButton;
    QPushButton *tirarDadoButton;
    QTextEdit *mensajesTextEdit;

    QVector<QLabel*> casillasLabels;

    Juego *juego;
    int numJugadores;
};

#endif // MAINWINDOW_H
