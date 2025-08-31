QT += core widgets

CONFIG += c++17

TARGET = TP_Corregido_Fran
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    casilla.cpp \
    tablero.cpp \
    juego.cpp \
    jugador.cpp

HEADERS += \
    mainwindow.h \
    casilla.h \
    tablero.h \
    juego.h \
    jugador.h

FORMS += \
    mainwindow.ui