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
      direccion(1),
      partidaTerminada(false),
      ganador(nullptr),
      jugadorPendienteUNO(nullptr),
      unoDeclarado(false)  {
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
    if (jugadorPendienteUNO != nullptr &&
        jugadorPendienteUNO != jugadorActual->dato) {

        jugadorPendienteUNO = nullptr;
        unoDeclarado = false;
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

    //Verificar que haya jugador actual
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

    // Verificar si quedó con una carta
    if (jugadorActual->dato->cantidadCartas() == 1) {
        jugadorPendienteUNO = jugadorActual->dato;
        unoDeclarado = false;
    }

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

    switch (tipo) {

        case SKIP:
            // Saltamos al siguiente jugador
            siguienteTurno();
            break;

        case REVERSE:
            cambiarDireccion();

            // Si solo hay 2 jugadores, REVERSE actúa como SKIP
            if (contarJugadores() == 2) {
                siguienteTurno();
            }
            break;

        case DRAW: {
            // El siguiente jugador roba 2 cartas
            siguienteTurno();

            Jugador* afectado = jugadorActual->dato;

            for (int i = 0; i < 2; i++) {
                if (mazo.estaVacio()) {
                    remezclarDescarteEnMazo();
                }

                if (!mazo.estaVacio()) {
                    afectado->agregarCarta(mazo.robar());
                }
            }
            break;
        }

        case COMODIN:
            // elección de color
            break;

        case FLIP:
            // implementar modo flip
            break;

        case PERSONALIZADA:
            //implementar reglas personalizadas
            break;

        case NUMERO:
        default:
            // No tiene efecto especial
            break;
    }

    // Pasar turno normalmente
    siguienteTurno();

    return true;
}


void Juego::robarCarta() {

    if (partidaTerminada)
        return;

    if (jugadorActual == nullptr)
        return;

    if (mazo.estaVacio()) {
        remezclarDescarteEnMazo();
    }

    if (!mazo.estaVacio()) {

        Carta* carta = mazo.robar();

        if (carta != nullptr) {
            jugadorActual->dato->agregarCarta(carta);
        }
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

void Juego::remezclarDescarteEnMazo() {

    // Si el descarte está vacío o solo tiene 1 carta, no se puede remezclar
    if (descarte.estaVacia())
        return;

    // Guardamos la carta superior (no se mezcla)
    Carta* cartaSuperior = descarte.pop();

    ListaSimple<Carta*> bolsa;

    // Pasamos todas las demás cartas del descarte a una lista temporal
    while (!descarte.estaVacia()) {
        bolsa.insertarFinal(descarte.pop());
    }

    // Volvemos a apilar en el mazo
    while (!bolsa.estaVacia()) {
        mazo.apilar(bolsa.extraerPrimero());
    }

    // Restauramos la carta superior al descarte
    descarte.push(cartaSuperior);
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

    if (jugadorPendienteUNO == jugadorActual->dato) {
        unoDeclarado = true;
    }
}

void Juego::reportarUNO() {

    if (jugadorPendienteUNO == nullptr)
        return;

    // Si no declaró UNO correctamente
    if (!unoDeclarado) {

        for (int i = 0; i < 2; i++) {

            if (mazo.estaVacio())
                remezclarDescarteEnMazo();

            if (!mazo.estaVacio()) {
                jugadorPendienteUNO->agregarCarta(mazo.robar());
            }
        }
    }
    else {
        // Reporte incorrecto → el reportador (jugador actual) roba 2

        for (int i = 0; i < 2; i++) {

            if (mazo.estaVacio())
                remezclarDescarteEnMazo();

            if (!mazo.estaVacio()) {
                jugadorActual->dato->agregarCarta(mazo.robar());
            }
        }
    }

    // Limpiar estado
    jugadorPendienteUNO = nullptr;
    unoDeclarado = false;
}






