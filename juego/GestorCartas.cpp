//
// Created by ronald on 17/2/26.
//

#include "GestorCartas.h"

// Inicializa el mazo para una partida nueva
void GestorCartas::inicializar(int cantidadJugadores, const Configuracion& config) {
    mazo.construir(cantidadJugadores, config);
}

// Reparte cartas iniciales a todos los jugadores
void GestorCartas::repartirInicial(ListaCircular<Jugador*>& jugadores, int cantidad) {

    Nodo<Jugador*>* actual = jugadores.getCabeza();
    if (actual == nullptr)
        return;

    do {
        for (int i = 0; i < cantidad; i++) {
            Carta* carta = robarCarta();
            if (carta != nullptr) {
                actual->dato->agregarCarta(carta);
            }
        }
        actual = actual->siguiente;
    } while (actual != jugadores.getCabeza());
}

// Coloca la primera carta válida (no negra) en el descarte
void GestorCartas::colocarPrimeraCarta() {

    while (!mazo.estaVacio()) {

        Carta* carta = mazo.robar();
        // Si no es comodín negro, se acepta como inicial
        if (!carta->esNegra()) {
            descarte.push(carta);
            break;
        }

        // Si es comodín negro, vuelve al fondo
        mazo.apilar(carta);
    }
}

// Roba una carta con remezcla automática
Carta* GestorCartas::robarCarta() {

    if (mazo.estaVacio()) {
        remezclarDescarte();
    }

    return mazo.robar();
}

// Coloca carta en descarte
void GestorCartas::descartar(Carta* carta) {
    descarte.push(carta);
}

// Devuelve carta superior
Carta* GestorCartas::cartaSuperior() {
    if (descarte.estaVacia())
        return nullptr;

    return descarte.peek();
}

bool GestorCartas::mazoVacio() const {
    return mazo.estaVacio();
}

// Remezcla el descarte en el mazo (excepto la carta superior)
void GestorCartas::remezclarDescarte() {
    // Si el descarte está vacío o solo tiene 1 carta, no se puede remezclar
    if (descarte.estaVacia())
        return;

    // Guardamos la carta superior (no se mezcla)
    Carta* cartaSuperior = descarte.pop();

    ListaSimple<Carta*> bolsa;

    // Pasamos todas las demas cartas del descarte a una lista temporal
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

void GestorCartas::forzarRemezcla() {
    remezclarDescarte();
}
