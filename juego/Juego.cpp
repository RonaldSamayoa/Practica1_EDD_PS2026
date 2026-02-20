//
// Created by ronald on 9/2/26.
//
#include "Juego.h"
#include "MotorReglas.h"
#include "../cartas/CartaComodin.h"
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
      esperandoColor(false),
      roboAcumulado(0),
      saltarSiguiente(false){
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
    if (partidaTerminada)
        return false;

    //Verificar que haya jugador actual
    if (jugadorActual == nullptr)
        return false;

    if (esperandoColor)
        return false;

    // verificar si es carta de robo
    bool esCartaDeRobo = false;

    if (carta->getTipo() == DRAW)
        esCartaDeRobo = true;

    if (carta->getTipo() == COMODIN) {
        CartaComodin* c = dynamic_cast<CartaComodin*>(carta);
        if (c != nullptr && c->getCantidadRobo() > 0)
            esCartaDeRobo = true;
    }
    //manejo de robo acumulado
    if (roboAcumulado > 0 && !esCartaDeRobo) {

        //se roba lo acumulado
        for (int i = 0; i < roboAcumulado; i++) {
            Carta* robada = gestorCartas.robarCarta();
            if (robada != nullptr)
                jugadorActual->dato->agregarCarta(robada);
        }
        roboAcumulado = 0;
        siguienteTurno();
        return true;
    }

    //validar jugada
    if (!MotorReglas::esJugadaValida(carta, gestorCartas.cartaSuperior(), colorActivo))
        return false;

    //Quitar carta
    if (!jugadorActual->dato->quitarCarta(carta))
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
    //aplicar efecto
    MotorReglas::aplicarEfecto(carta, *this);

    // Manejar salto si existe
    if (debeSaltar()) {
        siguienteTurno();
        limpiarSalto();
    }

    // Avance normal
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

int Juego::getRoboAcumulado() const {
          return roboAcumulado;
      }

void Juego::setRoboAcumulado(int cantidad) {
          roboAcumulado = cantidad;
      }

Configuracion& Juego::getConfiguracion() {
          return config;
      }

void Juego::activarSalto() {
    saltarSiguiente = true;
}

bool Juego::debeSaltar() const {
    return saltarSiguiente;
}

void Juego::limpiarSalto() {
    saltarSiguiente = false;
}

Jugador* Juego::obtenerSiguienteJugador() {

    if (jugadorActual == nullptr)
        return nullptr;

    if (direccion == 1)
        return jugadorActual->siguiente->dato;

    Nodo<Jugador*>* anterior = jugadores.buscarAnterior(jugadorActual);
    return anterior->dato;
}




