//
// Created by ronald on 9/2/26.
//
#include "Juego.h"
#include "MotorReglas.h"

// Constructor
Juego::Juego(const Configuracion& configuracion)
    : jugadores(),
      gestorCartas(),
      controlUNO(),
      config(configuracion),
      jugadorActual(nullptr),
      direccion(1),
      partidaTerminada(false),
      ganador(nullptr),
      esperandoColor(false) {
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

    // Si cambió el turno y nadie reportó, se pierde oportunidad
    controlUNO.limpiarSiCambiaTurno(jugadorActual->dato);
}

void Juego::iniciarPartida() {

    int nJugadores = contarJugadores();

    if (nJugadores < 2) {
        return; // No se puede iniciar con menos de 2 jugadores
    }

    gestorCartas.inicializar(nJugadores, config);
    gestorCartas.repartirInicial(jugadores, 7);
    gestorCartas.colocarPrimeraCarta();

    Carta* superior = gestorCartas.cartaSuperior();
    if (superior != nullptr) {
        colorActivo = superior->getColor();
    }
}

bool Juego::jugarCarta(Carta* carta) {

    //Verificar que haya jugador actual
    if (jugadorActual == nullptr)
        return false;

    if (esperandoColor)
        return false;

    //validar jugada
    if (!MotorReglas::esJugadaValida(carta, gestorCartas.cartaSuperior(), colorActivo))
        return false;

    //Quitar carta de la mano
    bool eliminada = jugadorActual->dato->quitarCarta(carta);

    if (!eliminada)
        return false;

    //Poner carta en descarte
    gestorCartas.descartar(carta);

    if (carta->getTipo() == COMODIN) {

        esperandoColor = true;

    } else {
        colorActivo = carta->getColor();
    }

    // Verificar si quedó con una carta
    controlUNO.verificarCartaUnica(jugadorActual->dato);

    //Verificar si ganó
    if (jugadorActual->dato->sinCartas()) {
        partidaTerminada = true;
        ganador = jugadorActual->dato;
        return true;
    }

    if (partidaTerminada)
        return false;

    //Aplicar efecto según tipo
    TipoCarta tipo = carta->getTipo();

    MotorReglas::aplicarEfecto(carta, *this);

    // Pasar turno normalmente
    if (!esperandoColor) {
        siguienteTurno();
    }
    return true;
}

void Juego::robarCarta() {

    if (partidaTerminada || jugadorActual == nullptr)
        return;

    if (esperandoColor)
        return;

    Carta* carta = gestorCartas.robarCarta();

    if (carta != nullptr) {
        jugadorActual->dato->agregarCarta(carta);
    }

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

bool Juego::estaTerminada() const {
    return partidaTerminada;
}

Jugador* Juego::getGanador() const {
    return ganador;
}

void Juego::declararUNO() {
    if (jugadorActual == nullptr)
        return;
    controlUNO.declararUNO(jugadorActual->dato);
}

void Juego::reportarUNO() {

    if (jugadorActual == nullptr)
        return;

    controlUNO.reportarUNO(jugadorActual->dato,
                           gestorCartas);
}

int Juego::contarJugadoresPublico() const {
    return contarJugadores();
}

bool Juego::mazoVacio() const {
    return gestorCartas.mazoVacio();
}

Carta* Juego::robarDelMazo() {
    return gestorCartas.robarCarta();
}

void Juego::remezclarMazo() {
    gestorCartas.forzarRemezcla();
}

Jugador* Juego::jugadorActualPtr() {
    if (jugadorActual == nullptr)
        return nullptr;

    return jugadorActual->dato;
}

void Juego::elegirColor(Color nuevoColor) {

    if (!esperandoColor)
        return;

    // No permitir NEGRO como color elegido
    if (nuevoColor == NEGRO)
        return;

    colorActivo = nuevoColor;
    esperandoColor = false;

    siguienteTurno();
}

bool Juego::estaEsperandoColor() const {
    return esperandoColor;
}





