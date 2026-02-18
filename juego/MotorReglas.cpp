//
// Created by ronald on 17/2/26.
//

#include "MotorReglas.h"
#include "../util/TiposCarta.h"
#include "Juego.h"

bool MotorReglas::esJugadaValida(Carta* carta, Carta* superior) {
    // Si no hay carta superior (inicio de partida)
    if (superior == nullptr)
        return true;

    //comodin siempre es valido
    if (carta->esNegra())
        return true;

    // Coincide en color
    if (carta->getColor() == superior->getColor())
        return true;

    // Coincide en tipo
    if (carta->getTipo() == superior->getTipo())
        return true;

    // Coincide en numero
    if (carta->getValor() != -1 &&
        carta->getValor() == superior->getValor())
        return true;

    return false;
}

void MotorReglas::aplicarEfecto(Carta* carta, Juego& juego) {

    TipoCarta tipo = carta->getTipo();

    switch (tipo) {

        case SKIP:
            // Saltamos al siguiente jugador
            juego.siguienteTurno();
            break;

        case REVERSE:
            juego.cambiarDireccion();
            // Si solo hay 2 jugadores, REVERSE actúa como SKIP
            if (juego.contarJugadoresPublico() == 2) {
                juego.siguienteTurno();
            }
            break;

        case DRAW: {
            // El siguiente jugador roba 2 cartas
            juego.siguienteTurno();

            Jugador* afectado = juego.getJugadorActual();

            for (int i = 0; i < 2; i++) {

                Carta* carta = juego.robarDelMazo();
                if (carta != nullptr)
                    afectado->agregarCarta(carta);
            }
            break;
        }

        case COMODIN:
            break;

        case FLIP:
            break;

        case PERSONALIZADA:
            break;

        case NUMERO:
        default:
            break;
    }
}
