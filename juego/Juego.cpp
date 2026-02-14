//
// Created by ronald on 9/2/26.
//

#include "Juego.h"
#include <stdexcept>
#include "../cartas/CartaNumero.h"
#include "../cartas/CartaAccion.h"
#include "../cartas/CartaComodin.h"

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

    ListaSimple<Carta*> bolsa;  // bolsa temporal usando tu estructura

    Color colores[] = { ROJO, AMARILLO, VERDE, AZUL };

    // 1️⃣ Construimos ordenado por color
    for (Color color : colores) {

        // Números 0–9
        for (int i = 0; i <= 9; i++) {
            bolsa.insertarFinal(new CartaNumero(color, i));
        }

        // Acciones
        bolsa.insertarFinal(new CartaAccion(color, SKIP));
        bolsa.insertarFinal(new CartaAccion(color, REVERSE));
        bolsa.insertarFinal(new CartaAccion(color, DRAW));

        if (config.isModoFlip()) {
            bolsa.insertarFinal(new CartaAccion(color, FLIP));
        }
    }

    // Comodines
    bolsa.insertarFinal(new CartaComodin(0));
    bolsa.insertarFinal(new CartaComodin(4));

    // 2️⃣ Barajamos la lista manualmente
    barajarLista(bolsa);

    // 3️⃣ Pasamos la lista al Stack
    while (!bolsa.estaVacia()) {
        mazo.push(bolsa.extraerPrimero());
    }
}

int Juego::contarElementos(ListaSimple<Carta*>& lista) {

    int contador = 0;
    ListaSimple<Carta*> temp;

    while (!lista.estaVacia()) {
        temp.insertarFinal(lista.extraerPrimero());
        contador++;
    }

    while (!temp.estaVacia()) {
        lista.insertarFinal(temp.extraerPrimero());
    }

    return contador;
}

void Juego::barajarLista(ListaSimple<Carta*>& lista) {

    // Se obtiene la cantidad total de elementos en la lista
    int n = contarElementos(lista);

    // Si la lista tiene 0 o 1 elemento, no es necesario barajar
    if (n <= 1)
        return;

    // Se recorre la lista completa realizando reordenamientos progresivos
    for (int i = 0; i < n; i++) {

        // Se extrae el primer elemento de la lista original. Esta carta será reinsertada en una nueva posición calculada
        Carta* primera = lista.extraerPrimero();

        // Se calcula una posición de inserción basada en la iteración actual
        // La fórmula permite variar la posición sin utilizar números aleatorios
        int saltos = (i * 3 + 1) % n;

        // Se crea una lista temporal auxiliar para reconstruir el orden
        ListaSimple<Carta*> temp;

        // Se trasladan los primeros saltos de elementos de la lista original hacia la lista temporal, preservando su orden relativo
        for (int j = 0; j < saltos && !lista.estaVacia(); j++) {
            temp.insertarFinal(lista.extraerPrimero());
        }

        // Se inserta la carta extraída inicialmente en la nueva posición calculada
        temp.insertarFinal(primera);

        // Se trasladan los elementos restantes de la lista original hacia la lista temporal
        while (!lista.estaVacia()) {
            temp.insertarFinal(lista.extraerPrimero());
        }

        // Finalmente, se reconstruye la lista original utilizando el nuevo orden generado en la lista temporal
        while (!temp.estaVacia()) {
            lista.insertarFinal(temp.extraerPrimero());
        }
    }
}


