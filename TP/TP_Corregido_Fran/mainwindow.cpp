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

    // Botón Clear
    clearButton = new QPushButton("Limpiar Mensajes");
    clearButton->setStyleSheet("QPushButton { background-color: #ff6b6b; color: white; font-weight: bold; }");
    controlLayout->addWidget(clearButton);

    controlLayout->addWidget(new QLabel("Mensajes:"));
    mensajesTextEdit = new QTextEdit();
    mensajesTextEdit->setMaximumHeight(300); // Limitar altura para dar más espacio al tablero
    controlLayout->addWidget(mensajesTextEdit);

    mainLayout->addWidget(controlPanel);

    // Crear tablero visual
    crearTableroVisual();

    // Conectar botones
    connect(iniciarJuegoButton, &QPushButton::clicked, this, &MainWindow::on_iniciarJuegoButton_clicked);
    connect(tirarDadoButton, &QPushButton::clicked, this, &MainWindow::on_tirarDadoButton_clicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);

    setWindowTitle("Juego de la Oca");
    resize(1200, 800); // Aumentar el tamaño para acomodar mejor el tablero
}

MainWindow::~MainWindow()
{
}

void MainWindow::crearTableroVisual()
{
    QWidget *tableroWidget = new QWidget();
    tableroLayout = new QGridLayout(tableroWidget);
    tableroLayout->setSpacing(2); // Reducir espacio entre casillas
    tableroLayout->setContentsMargins(10, 10, 10, 10); // Márgenes más pequeños

    casillasLabels.resize(64); // 0-63

    // Crear tablero en forma de serpiente más compacto
    int filas = 7;  // Reducir número de filas
    int columnas = 9; // Ajustar columnas

    int casilla = 1;
    for (int fila = 0; fila < filas && casilla <= 63; fila++) {
        if (fila % 2 == 0) {
            // Fila par: izquierda a derecha
            for (int col = 0; col < columnas && casilla <= 63; col++) {
                crearCasilla(casilla, fila, col);
                casilla++;
            }
        } else {
            // Fila impar: derecha a izquierda
            for (int col = columnas - 1; col >= 0 && casilla <= 63; col--) {
                crearCasilla(casilla, fila, col);
                casilla++;
            }
        }
    }

    mainLayout->addWidget(tableroWidget);
}

void MainWindow::crearCasilla(int numero, int fila, int columna)
{
    QLabel* label = new QLabel();
    label->setFixedSize(55, 55); // Casillas un poco más grandes para mejor visibilidad
    label->setText(QString::number(numero));
    label->setAlignment(Qt::AlignCenter);

    // Estilo base
    QString estiloBase = "border: 2px solid black; background-color: lightgray; font-weight: bold; font-size: 10px;";

    // Colorear casillas especiales
    QString colorFondo = "lightgray";
    if (numero == 6 || numero == 12) colorFondo = "#FFD700"; // Puente - Dorado
    else if (numero == 9 || numero == 18 || numero == 27 || numero == 36 || numero == 45 || numero == 54)
        colorFondo = "#90EE90"; // Oca - Verde claro
    else if (numero == 19) colorFondo = "#FFA07A"; // Posada - Salmón
    else if (numero == 31) colorFondo = "#87CEEB"; // Pozo - Azul cielo
    else if (numero == 42) colorFondo = "#DDA0DD"; // Laberinto - Ciruela
    else if (numero == 56) colorFondo = "#F0E68C"; // Cárcel - Caqui
    else if (numero == 58) colorFondo = "#FF6347"; // Calavera - Tomate
    else if (numero == 63) colorFondo = "#FFD700"; // Meta - Dorado

    label->setStyleSheet(QString("border: 2px solid black; background-color: %1; font-weight: bold; font-size: 10px;").arg(colorFondo));

    casillasLabels[numero] = label;
    tableroLayout->addWidget(label, fila, columna);
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

void MainWindow::on_clearButton_clicked()
{
    mensajesTextEdit->clear();
}

void MainWindow::actualizarMensaje(const QString &mensaje)
{
    mensajesTextEdit->append(mensaje);
    // Auto-scroll hacia abajo
    mensajesTextEdit->verticalScrollBar()->setValue(mensajesTextEdit->verticalScrollBar()->maximum());
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
    // Resetear todas las casillas a su color base
    for (int i = 1; i <= 63; i++) {
        if (casillasLabels[i]) {
            QString colorFondo = "lightgray";

            // Mantener colores de casillas especiales
            if (i == 6 || i == 12) colorFondo = "#FFD700"; // Puente
            else if (i == 9 || i == 18 || i == 27 || i == 36 || i == 45 || i == 54)
                colorFondo = "#90EE90"; // Oca
            else if (i == 19) colorFondo = "#FFA07A"; // Posada
            else if (i == 31) colorFondo = "#87CEEB"; // Pozo
            else if (i == 42) colorFondo = "#DDA0DD"; // Laberinto
            else if (i == 56) colorFondo = "#F0E68C"; // Cárcel
            else if (i == 58) colorFondo = "#FF6347"; // Calavera
            else if (i == 63) colorFondo = "#FFD700"; // Meta

            casillasLabels[i]->setStyleSheet(QString("border: 2px solid black; background-color: %1; font-weight: bold; font-size: 10px;").arg(colorFondo));
        }
    }

    // Marcar jugadores con bordes más gruesos y colores distintivos
    QVector<Jugador*> jugadores = juego->getJugadores();
    QStringList coloresJugadores = {"red", "blue", "green", "orange"};

    for (int i = 0; i < jugadores.size(); i++) {
        int pos = jugadores[i]->getPosicion();
        if (pos >= 1 && pos <= 63 && casillasLabels[pos]) {
            QString colorJugador = coloresJugadores[i % coloresJugadores.size()];

            // Obtener color de fondo actual de la casilla
            QString colorFondo = "lightgray";
            if (pos == 6 || pos == 12) colorFondo = "#FFD700";
            else if (pos == 9 || pos == 18 || pos == 27 || pos == 36 || pos == 45 || pos == 54)
                colorFondo = "#90EE90";
            else if (pos == 19) colorFondo = "#FFA07A";
            else if (pos == 31) colorFondo = "#87CEEB";
            else if (pos == 42) colorFondo = "#DDA0DD";
            else if (pos == 56) colorFondo = "#F0E68C";
            else if (pos == 58) colorFondo = "#FF6347";
            else if (pos == 63) colorFondo = "#FFD700";

            casillasLabels[pos]->setStyleSheet(QString("border: 4px solid %1; background-color: %2; font-weight: bold; font-size: 10px;").arg(colorJugador, colorFondo));
        }
    }
}
