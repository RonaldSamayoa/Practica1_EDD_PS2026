//
// Created by ronald on 9/2/26.
//

#ifndef UNO_JUEGO_H
#define UNO_JUEGO_H
#include "../estructuras/ListaCircular.h"
#include "../estructuras/Stack.h"
#include "Jugador.h"
#include "Configuracion.h"
#include "../cartas/Carta.h"

class Juego {
private:
    ListaCircular<Jugador*> jugadores;  // Lista circular de jugadores
    Stack<Carta*> mazo; // Mazo principal
    Stack<Carta*> descarte; // Mazo de descarte

    void construirMazo(); //hacer el mazo del jugador

    Configuracion config;               // Reglas activadas

    Nodo<Jugador*>* jugadorActual;      // Nodo actual en la lista circular
    int direccion;                      // 1 = normal, -1 = reversa

public:
    // Constructor
    Juego(const Configuracion& configuracion);

    // Agregar jugadores antes de iniciar
    void agregarJugador(Jugador* jugador);

    // Inicializar partida (crear mazo, repartir, etc.)
    void iniciarPartida();

    // Avanzar turno
    void siguienteTurno();

    // Cambiar dirección
    void cambiarDireccion();

    // Obtener jugador actual
    [[nodiscard]] Jugador* getJugadorActual() const;

};


#endif //UNO_JUEGO_H