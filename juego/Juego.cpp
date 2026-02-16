//
// Created by ronald on 9/2/26.
//

#include "Juego.h"

// Constructor
Juego::Juego(const Configuracion& configuracion)
    : jugadores(),
      mazo(),
      descarte(),
      config(configuracion),
      jugadorActual(nullptr),
      direccion(1){
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
        return nullptr;
    return jugadorActual->dato;
}

// Cambia el sentido del juego
void Juego::cambiarDireccion() {
    direccion *= -1;
}

// Avanza al siguiente jugador según la dirección
void Juego::siguienteTurno() {
    if (jugadorActual == nullptr)
        return;

    if (direccion == 1) {
        jugadorActual = jugadorActual->siguiente;
    } else {
        jugadorActual = jugadores.buscarAnterior(jugadorActual);
    }
}

void Juego::iniciarPartida() {

    int nJugadores = contarJugadores();

    if (nJugadores < 2) {
        return; // No se puede iniciar con menos de 2 jugadores
    }

    mazo.construir(nJugadores, config);

    repartirCartasIniciales(7);

    colocarPrimeraCarta();
}

void Juego::repartirCartasIniciales(int cantidad) {

    Nodo<Jugador*>* actual = jugadores.getCabeza();

    if (actual == nullptr)
        return;

    do {

        for (int i = 0; i < cantidad; i++) {

            if (!mazo.estaVacio()) {
                Carta* carta = mazo.robar();
                actual->dato->agregarCarta(carta);
            }
        }

        actual = actual->siguiente;

    } while (actual != jugadores.getCabeza());
}

void Juego::colocarPrimeraCarta() {

    while (!mazo.estaVacio()) {

        Carta* carta = mazo.robar();

        // Si no es comodín negro, se acepta como inicial
        if (!carta->esNegra()) {
            descarte.push(carta);
            break;
        }

        // Si es negra, la regresamos al fondo
        mazo.apilar(carta);
    }
}

bool Juego::esJugadaValida(Carta* carta) {

    if (descarte.estaVacia())
        return true;

    Carta* superior = descarte.peek();

    // Comodín siempre válido
    if (carta->esNegra())
        return true;

    // Coincide color
    if (carta->getColor() == superior->getColor())
        return true;

    // Coincide tipo
    if (carta->getTipo() == superior->getTipo())
        return true;

    // Coincide número
    if (carta->getValor() != -1 &&
        carta->getValor() == superior->getValor())
        return true;

    return false;
}

bool Juego::jugarCarta(Carta* carta) {

    if (jugadorActual == nullptr)
        return false;

    //validar jugada
    if (!esJugadaValida(carta))
        return false;

    //Quitar carta de la mano
    bool eliminada = jugadorActual->dato->quitarCarta(carta);

    if (!eliminada)
        return false;

    //Poner carta en descarte
    descarte.push(carta);

    //Verificar victoria básica
    if (jugadorActual->dato->sinCartas()) {
        // pendiente
        return true;
    }

    //Pasar turno
    siguienteTurno();

    return true;
}

void Juego::robarCarta() {

    if (jugadorActual == nullptr)
        return;

    if (!mazo.estaVacio()) {

        Carta* carta = mazo.robar();

        if (carta != nullptr) {
            jugadorActual->dato->agregarCarta(carta);
        }
    }

    // En modo básico: roba 1 y pasa turno
    siguienteTurno();
}

int Juego::contarJugadores() const {

    int contador = 0;
    Nodo<Jugador*>* temp = jugadores.getCabeza();

    if (temp == nullptr)
        return 0;

    do {
        contador++;
        temp = temp->siguiente;
    } while (temp != jugadores.getCabeza());

    return contador;
}





