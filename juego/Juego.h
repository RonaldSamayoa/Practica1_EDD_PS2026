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
#include "GestorCartas.h"
#include "ControlUNO.h"

class Juego {
private:
    ListaCircular<Jugador*> jugadores;  // Lista circular de jugadores
    [[nodiscard]] int contarJugadores() const;

    GestorCartas gestorCartas;
    ControlUNO controlUNO;
    Configuracion config;               // Reglas activadas

    Nodo<Jugador*>* jugadorActual;      // Nodo actual en la lista circular
    int direccion;                      // 1 = normal, -1 = reversa

    bool partidaTerminada;
    Jugador* ganador;

public:
    // Constructor
    Juego(const Configuracion& configuracion);

    // Agregar jugadores antes de iniciar
    void agregarJugador(Jugador* jugador);

    // Inicializar partida (crear mazo, repartir, etc.)
    void iniciarPartida();

    bool jugarCarta(Carta* carta);

    void robarCarta();

    // Avanzar turno
    void siguienteTurno();

    // Cambiar dirección
    void cambiarDireccion();

    // Obtener jugador actual
    [[nodiscard]] Jugador* getJugadorActual() const;

    [[nodiscard]] bool estaTerminada() const;
    [[nodiscard]] Jugador* getGanador() const;

    void declararUNO();
    void reportarUNO();

    [[nodiscard]] int contarJugadoresPublico() const;

    [[nodiscard]] bool mazoVacio() const;

    Carta* robarDelMazo();

    void remezclarMazo();

    Jugador* jugadorActualPtr();
};

#endif //UNO_JUEGO_H