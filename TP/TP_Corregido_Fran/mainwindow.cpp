#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    juego = new Juego(this);

    connect(juego, &Juego::mensajeActualizado, this, &MainWindow::actualizarMensaje);
    connect(juego, &Juego::juegoTerminado, this, &MainWindow::juegoTerminado);

    // Crear UI
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    // Panel de control
    QWidget *controlPanel = new QWidget();
    controlLayout = new QVBoxLayout(controlPanel);
    controlPanel->setFixedWidth(250);

    controlLayout->addWidget(new QLabel("Número de jugadores:"));
    numJugadoresSpinBox = new QSpinBox();
    numJugadoresSpinBox->setRange(2, 4);
    numJugadoresSpinBox->setValue(2);
    controlLayout->addWidget(numJugadoresSpinBox);

    iniciarJuegoButton = new QPushButton("Iniciar Juego");
    controlLayout->addWidget(iniciarJuegoButton);

    tirarDadoButton = new QPushButton("Tirar Dado");
    tirarDadoButton->setEnabled(false);
    controlLayout->addWidget(tirarDadoButton);

    controlLayout->addWidget(new QLabel("Mensajes:"));
    mensajesTextEdit = new QTextEdit();
    controlLayout->addWidget(mensajesTextEdit);

    mainLayout->addWidget(controlPanel);

    // Crear tablero visual
    crearTableroVisual();

    // Conectar botones
    connect(iniciarJuegoButton, &QPushButton::clicked, this, &MainWindow::on_iniciarJuegoButton_clicked);
    connect(tirarDadoButton, &QPushButton::clicked, this, &MainWindow::on_tirarDadoButton_clicked);

    setWindowTitle("Juego de la Oca");
    resize(1000, 700);
}

MainWindow::~MainWindow()
{
}

void MainWindow::crearTableroVisual()
{
    QWidget *tableroWidget = new QWidget();
    tableroLayout = new QGridLayout(tableroWidget);

    casillasLabels.resize(64); // 0-63

    int x = 0, y = 0;
    for (int i = 1; i <= 63; i++) {
        QLabel* label = new QLabel();
        label->setFixedSize(45, 45);
        label->setText(QString::number(i));
        label->setStyleSheet("border: 1px solid black; background-color: lightgray;");
        label->setAlignment(Qt::AlignCenter);

        casillasLabels[i] = label;
        tableroLayout->addWidget(label, x, y);

        // Lógica serpiente del código original
        if (x % 2 == 0) y++;
        else y--;
        if (y > 20) {
            x++;
            y = 20;
        }
        if (y < 0) {
            x++;
            y = 0;
        }
    }

    mainLayout->addWidget(tableroWidget);
}

void MainWindow::on_iniciarJuegoButton_clicked()
{
    numJugadores = numJugadoresSpinBox->value();
    juego->iniciar(numJugadores);
    tirarDadoButton->setEnabled(true);
    iniciarJuegoButton->setEnabled(false);
    actualizarTablero();
}

void MainWindow::on_tirarDadoButton_clicked()
{
    juego->jugarTurno();
    actualizarTablero();
}

void MainWindow::actualizarMensaje(const QString &mensaje)
{
    mensajesTextEdit->append(mensaje);
}

void MainWindow::juegoTerminado(const QString &ganador)
{
    QMessageBox::information(this, "¡Juego terminado!",
                             QString("¡%1 ha ganado!").arg(ganador));
    tirarDadoButton->setEnabled(false);
    iniciarJuegoButton->setEnabled(true);
}

void MainWindow::actualizarTablero()
{
    // Resetear todas las casillas
    for (int i = 1; i <= 63; i++) {
        if (casillasLabels[i]) {
            casillasLabels[i]->setStyleSheet("border: 1px solid black; background-color: lightgray;");
        }
    }

    // Marcar jugadores
    QVector<Jugador*> jugadores = juego->getJugadores();
    for (int i = 0; i < jugadores.size(); i++) {
        int pos = jugadores[i]->getPosicion();
        if (pos >= 1 && pos <= 63 && casillasLabels[pos]) {
            QString color = (i == 0) ? "red" : (i == 1) ? "blue" : (i == 2) ? "green" : "yellow";
            casillasLabels[pos]->setStyleSheet(QString("border: 3px solid black; background-color: %1;").arg(color));
        }
    }
}
