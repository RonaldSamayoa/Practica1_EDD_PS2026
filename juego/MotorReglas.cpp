//
// Created by ronald on 17/2/26.
//

#include "MotorReglas.h"
#include "../util/TiposCarta.h"
#include "Juego.h"
#include "../cartas/CartaComodin.h"

bool MotorReglas::esJugadaValida(Carta* carta, Carta* superior, Color colorActivo) {
    // Si no hay carta superior (inicio de partida)
    if (superior == nullptr)
        return true;

    //comodin siempre es valido
    if (carta->esNegra())
        return true;

    // Coincide en tipo
    if (carta->getTipo() == superior->getTipo())
        return true;

    // Coincide en color
    if (carta->getColor() == colorActivo)
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

        case COMODIN:{

            // Verificar si es comodín con robo
            CartaComodin* comodin =
                dynamic_cast<CartaComodin*>(carta);

            if (comodin != nullptr &&
                comodin->getCantidadRobo() > 0) {

                juego.siguienteTurno();
                Jugador* afectado = juego.getJugadorActual();

                for (int i = 0;
                     i < comodin->getCantidadRobo();
                     i++) {

                    Carta* robada = juego.robarDelMazo();
                    if (robada != nullptr) {
                        afectado->agregarCarta(robada);
                    }
                     }
                }

            break;
        }

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
