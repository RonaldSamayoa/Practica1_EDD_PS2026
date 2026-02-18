//
// Created by ronald on 18/2/26.
//

#ifndef UNO_CONTROLUNO_H
#define UNO_CONTROLUNO_H
#include "Jugador.h"
#include "GestorCartas.h"

class ControlUNO {
private:
    Jugador* jugadorPendiente;
    bool unoDeclarado;

public:
    ControlUNO();

    void verificarCartaUnica(Jugador* jugador);
    void declararUNO(Jugador* jugadorActual);
    void reportarUNO(Jugador* jugadorActual, GestorCartas& gestor);
    void limpiarSiCambiaTurno(Jugador* nuevoJugador);
};


#endif //UNO_CONTROLUNO_H