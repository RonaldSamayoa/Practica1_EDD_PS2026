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
    // Si el mazo está vacío, no se puede colocar carta inicial
    if (mazo.estaVacio())
        return;

    int intentos = 0;

    // Se obtiene una cantidad límite razonable de intentos
    // Esto evita un posible bucle infinito si todas las cartas restantes son negras
    int limite = 200;

    while (!mazo.estaVacio() && intentos < limite) {

        // Se roba la carta superior del mazo
        Carta* carta = mazo.robar();

        // Si la carta no es comodín negro, se acepta como carta inicial
        if (!carta->esNegra()) {
            descarte.push(carta);
            return;
        }

        // Si es negra, se devuelve al fondo del mazo
        mazo.apilar(carta);

        intentos++;
    }

    // Si no se encontró carta válida después de varios intentos,
    // se coloca la primera disponible para evitar bloqueo del juego
    if (!mazo.estaVacio()) {
        descarte.push(mazo.robar());
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
