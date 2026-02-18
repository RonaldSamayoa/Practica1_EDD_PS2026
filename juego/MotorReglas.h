//
// Created by ronald on 17/2/26.
//

#ifndef UNO_MOTORREGLAS_H
#define UNO_MOTORREGLAS_H

#include "../cartas/Carta.h"

class Juego;
class MotorReglas {
public:
    static bool esJugadaValida(Carta* carta, Carta* cartaSuperior);

    static void aplicarEfecto(Carta* carta, Juego& juego);
};


#endif //UNO_MOTORREGLAS_H