//
// Created by ronald on 9/2/26.
//

#include "Juego.h"
#include <stdexcept>
#include "../cartas/CartaNumero.h"
#include "../cartas/CartaAccion.h"
#include "../cartas/CartaComodin.h"
#include <vector>

// Constructor
Juego::Juego(const Configuracion& configuracion)
    : config(configuracion), direccion(1), jugadorActual(nullptr) {
}

// Agrega un jugador a la lista circular
void Juego::agregarJugador(Jugador* jugador) {
    jugadores.insertar(jugador);

    // Si es el primer jugador agregado, será el inicial
    if (jugadorActual == nullptr) {
        jugadorActual = jugadores.getCabeza();
    }
}

// Devuelve el jugador actual
Jugador* Juego::getJugadorActual() const {
    if (jugadorActual == nullptr)
        throw std::runtime_error("No hay jugadores en la partida");

    return jugadorActual->dato;
}

// Cambia el sentido del juego
void Juego::cambiarDireccion() {
    direccion *= -1;
}

// Avanza al siguiente jugador según la dirección
void Juego::siguienteTurno() {
    if (jugadorActual == nullptr)
        throw std::runtime_error("No hay jugadores en la partida");

    if (direccion == 1) {
        jugadorActual = jugadorActual->siguiente;
    } else {
        jugadorActual = jugadores.buscarAnterior(jugadorActual);
    }
}

void Juego::construirMazo() {

    // Orden de colores definido
    std::vector<Color> colores = {
        Color::ROJO,
        Color::AMARILLO,
        Color::VERDE,
        Color::AZUL
    };

    // Recorremos cada color
    for (Color color : colores) {

        //Cartas número (0 al 9)
        for (int i = 0; i <= 9; i++) {
            mazo.push(new CartaNumero(color, i));
        }

        //Cartas de acción
        mazo.push(new CartaAccion(color, SKIP));
        mazo.push(new CartaAccion(color, REVERSE));

        // DRAW necesita cantidad (ej: +2)
        mazo.push(new CartaAccion(color, DRAW));

        //en modo UNO flip
        if (config.isModoFlip()) {
            mazo.push(new CartaAccion(color, FLIP));
        }
    }

    //Comodines (no tienen color fijo)
    mazo.push(new CartaComodin(0)); // Cambio de color
    mazo.push(new CartaComodin(4)); // +4
}
