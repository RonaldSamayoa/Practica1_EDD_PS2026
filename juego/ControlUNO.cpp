//
// Created by ronald on 18/2/26.
//

#include "ControlUNO.h"

ControlUNO::ControlUNO()
    : jugadorPendiente(nullptr),
      unoDeclarado(false) {
}

void ControlUNO::verificarCartaUnica(Jugador* jugador) {

    if (jugador->cantidadCartas() == 1) {
        jugadorPendiente = jugador;
        unoDeclarado = false;
    }
}

void ControlUNO::declararUNO(Jugador* jugadorActual) {

    if (jugadorPendiente == jugadorActual) {
        unoDeclarado = true;
    }
}

void ControlUNO::reportarUNO(Jugador* jugadorActual,
                             GestorCartas& gestor) {

    if (jugadorPendiente == nullptr)
        return;

    Jugador* penalizado;

    if (!unoDeclarado) {
        penalizado = jugadorPendiente;
    } else {
        penalizado = jugadorActual;
    }

    for (int i = 0; i < 2; i++) {
        Carta* carta = gestor.robarCarta();
        if (carta != nullptr) {
            penalizado->agregarCarta(carta);
        }
    }

    jugadorPendiente = nullptr;
    unoDeclarado = false;
}

void ControlUNO::limpiarSiCambiaTurno(Jugador* nuevoJugador) {

    if (jugadorPendiente != nullptr &&
        jugadorPendiente != nuevoJugador) {

        jugadorPendiente = nullptr;
        unoDeclarado = false;
        }
}